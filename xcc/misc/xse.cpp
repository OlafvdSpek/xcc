#include "stdafx.h"
#include "xse.h"

#include "ima_adpcm_wav_decode.h"
#include "mix_file.h"
#include "wav_structures.h"
#include "xcc_dirs.h"

int Cxse::open()
{
	t_game game = Cfname(xcc_dirs::get_main_mix(game_ra2_yr)).exists() ? game_ra2_yr : game_ra2;
	int error = m_bag_f.open_edit(xcc_dirs::get_dir(game) + "audio.bag");
	if (!error)
	{
		error = m_idx_f.open_edit(xcc_dirs::get_dir(game) + "audio.idx");
		if (!error)
		{
			if (m_bag_f.size() && m_idx_f.size())
			{
				int cb_s = m_idx_f.size();
				Cvirtual_binary s;
				error = m_idx_f.read(s.write_start(cb_s), cb_s);
				if (!error)
				{
					Caudio_idx_file g;
					g.load(s, cb_s);
					read_idx_file(g);
				}
			}
			else
			{
				Cmix_file language;
				error = language.open(xcc_dirs::get_language_mix(game));
				if (!error)
				{
					language.set_game(game_ra2);
					Cmix_file audio;
					error = audio.open(xcc_dirs::get_audio_mix(game), language);
					if (!error)
					{
						audio.set_game(game_ra2);
						Ccc_file f(true);
						error = f.open("audio.bag", audio);
						if (!error)
						{
							error = m_bag_f.write(f.get_data(), f.get_size());
							f.close();
							if (!error)
							{
								Caudio_idx_file g;
								error = g.open("audio.idx", audio);
								if (!error)
								{
									read_idx_file(g);
									g.close();
									if (!error)
										error = write_idx_file();
								}
							}
						}
						audio.close();
					}
					language.close();
				}
			}
			if (error)
				m_idx_f.close();
		}
		if (error)
			m_bag_f.close();
	}
	return error;
}

void Cxse::read_idx_file(const Caudio_idx_file& f)
{
	for (int i = 0; i < f.c_sounds(); i++)
	{
		const t_audio_idx_entry& s  = f.sound_entry(i);
		t_map_entry& e = m_map[s.fname];
		e.offset = s.offset;
		e.size = s.size;
		e.samplerate = s.samplerate;
		e.flags = s.flags;
		e.chunk_size = s.chunk_size;
	}
}

int Cxse::write_idx_file()
{
	int cb_d = audio_idx_file_get_write_size(m_map.size());
	byte* d = new byte[cb_d];
	byte* w = d;
	w += audio_idx_file_write_header(w, m_map.size());
	for (t_map::const_iterator i = m_map.begin(); i != m_map.end(); i++)
	{
		const t_map_entry& e = i->second;
		w += audio_idx_file_write_entry(w, i->first, e.offset, e.size, e.samplerate, e.flags, e.chunk_size);
	}
	assert(w - d == cb_d);
	m_idx_f.seek(0);
	int error = m_idx_f.write(d, cb_d);
	if (!error)
		error = m_idx_f.set_eof();
	delete[] d;
	return error;
}

int Cxse::write()
{
	int error = 0;
	return error;
}

void Cxse::close()
{
	m_idx_f.close();
	m_bag_f.close();
}

int Cxse::extract(string fname, Cvirtual_file& f)
{
	int error = 0;
	const t_map_entry& e = *find_ptr(m_map, fname);
	int c_channels = e.flags & 1 ? 2 : 1;
	m_bag_f.seek(e.offset);
	if (e.flags & 2)
	{
		assert(!e.chunk_size);
		int cb_d = sizeof(t_wav_header) + e.size;
		byte* d = new byte[cb_d];
		byte* w = d;
		int c_channels = e.flags & 1 ? 2 : 1;
		int c_samples = e.size / c_channels >> 1;
		w += wav_file_write_header(w, c_samples, e.samplerate, 2, c_channels);
		error = m_bag_f.read(w, e.size);
		if (!error)
			f.write(d, cb_d);
		delete[] d;
	}
	else 
	{
		assert(e.flags & 8);
		int cb_s = e.size;
		byte* s = new byte[cb_s];
		error = m_bag_f.read(s, e.size);
		if (!error)
		{
			Cima_adpcm_wav_decode decode;
			decode.load(s, cb_s, c_channels, e.chunk_size);
			int c_samples = decode.c_samples() / c_channels;
			int cb_d = sizeof(t_wav_header) + (c_channels * c_samples << 1);
			byte* d = new byte[cb_d];
			byte* w = d;
			w += wav_file_write_header(w, c_samples, e.samplerate, 2, c_channels);
			memcpy(w, decode.data(), c_channels * c_samples << 1);
			f.write(d, cb_d);
			delete[] d;
		}
		delete[] s;
	}
	return error;
}

int Cxse::insert(string fname, Cwav_file& f)
{
	int error = 0;
	if (f.is_valid() && !f.process())
	{
		const t_riff_wave_format_chunk& format_chunk = f.get_format_chunk();
		if ((format_chunk.tag == 1 || format_chunk.tag == 0x11)
			&& (format_chunk.c_channels == 1 || format_chunk.c_channels == 2)
			&& format_chunk.cbits_sample == (format_chunk.tag == 1 ? 16 : 4))
		{
			int cb_s = f.get_data_header().size;
			byte* s = new byte[cb_s];
			f.seek(f.get_data_ofs());
			error = f.read(s, cb_s);
			if (!error)
			{
				t_map_entry e;
				e.offset = m_bag_f.size();
				e.size = cb_s;
				e.samplerate = format_chunk.samplerate;
				e.flags = 4 | format_chunk.c_channels == 2;
				if (format_chunk.tag == 1)
				{
					e.flags |= 2;
					e.chunk_size = 0;
				}
				else
				{
					e.flags |= 8;
					e.chunk_size = 512 * format_chunk.c_channels;
				}
				m_bag_f.seek(e.offset);
				error = m_bag_f.write(s, cb_s);
				if (!error)
					m_map[fname] = e;
			}
			delete[] s;
		}
		else
			error = 0x100;
	}
	return error;
}

int Cxse::get_bag_size() const
{
	int r = 0;
	for (t_map::const_iterator i = m_map.begin(); i != m_map.end(); i++)
		r += i->second.size;
	return r;
}

int Cxse::compact()
{
	int error = 0;
	int cb_d = get_bag_size();
	byte* d = new byte[cb_d];
	byte* w = d;
	for (t_map::iterator i = m_map.begin(); i != m_map.end(); i++)
	{
		t_map_entry& e = i->second;
		m_bag_f.seek(e.offset);
		if (error = m_bag_f.read(w, e.size))
			break;
		e.offset = w - d;
		w += e.size;
	}
	if (!error)
	{
		m_bag_f.seek(0);
		error = m_bag_f.write(d, cb_d);
		if (!error)
			error = m_bag_f.set_eof();
	}
	delete[] d;
	write_idx_file();
	return error;
}
