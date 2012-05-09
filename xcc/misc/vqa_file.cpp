#include "stdafx.h"
#include "vqa_file.h"

#include <vfw.h>
#include "image_file.h"
#include "pcx_decode.h"
#include "string_conversion.h"
#include "vqa_decode.h"
#include "wav_structures.h"
#include "xcc_log.h"

class Cvqa_decoder: public Cvideo_decoder
{
public:
	int cb_pixel() const
	{
		return m_f.get_cbits_pixel() == 8 ? 1 : 3;
	}

	int cf() const
	{
		return m_f.get_c_frames();
	}

	int cx() const
	{
		return m_f.get_cx();
	}

	int cy() const
	{
		return m_f.get_cy();
	}

	int decode(void* d)
	{
		if (m_frame_i >= cf())
			return 1;
		if (cb_pixel() == 1)
		{
			while (!m_f.is_video_chunk())
				m_f.skip_chunk();
			m_vqa_d.decode_vqfr_chunk(m_f.read_chunk().data(), m_frame.write_start(cb_image()), m_palet);
		}
		else
		{
			if (m_f.get_chunk_id() == vqa_vqfl_id)
				m_vqa_d.decode_vqfl_chunk(m_f.read_chunk());
			while (!m_f.is_video_chunk())
				m_f.skip_chunk();
			m_vqa_d.decode_vqfr_chunk(m_f.read_chunk().data(), m_frame.write_start(cb_image()), NULL);
		}
		if (d)
			m_frame.read(d);
		m_frame_i++;
		return 0;
	}

	const t_palet_entry* palet() const
	{
		return m_palet;
	}

	int seek(int f)
	{
		if (f == m_frame_i)
			return 0;
		if (f < m_frame_i || m_frame_i == -1)
		{
			m_f.seek(sizeof(t_vqa_header));
			m_f.read_chunk_header();
			m_vqa_d.start_decode(m_f.header());
			if (cb_pixel() != 1)
			{
				DDPIXELFORMAT pf;
				pf.dwRGBAlphaBitMask = 0;
				pf.dwRBitMask = 0x0000ff;
				pf.dwGBitMask = 0x00ff00;
				pf.dwBBitMask = 0xff0000;
				m_vqa_d.set_pf(pf, 3);
			}
			m_frame_i = 0;
		}
		while (m_frame_i < f && !decode(NULL))
			;
		return 0;
	}

	Cvqa_decoder(const Cvqa_file& f)
	{
		m_f.load(f);
		m_frame_i = -1;
		seek(0);
	}
private:
	Cvqa_decode m_vqa_d;
	Cvqa_file m_f;
	Cvirtual_binary m_frame;
	int m_frame_i;
	t_palet m_palet;
};

Cvideo_decoder* Cvqa_file::decoder()
{
	return new Cvqa_decoder(*this);
}

int Cvqa_file::post_open()
{
	int error = read(&m_header, sizeof(t_vqa_header));
	return error ? error : read_chunk_header();
}

static void flip_frame(const byte* s, byte* d, int cx, int cy, int cb_pixel)
{
	int cb_line = cx * cb_pixel;
	const byte* r = s;
	byte* w = d + cb_line * cy;
	while (cy--)
	{
		w -= cb_line;
		memcpy(w, r, cb_line);
		r += cb_line;
	}
}

static int process_audio_chunk_for_avi(Cvqa_file& f, Cvqa_decode& vqa_d, int& audio_i, PAVISTREAM a)
{
	int error = 0;
	short* aud_out;
	int size = f.get_chunk_size();
	if (f.get_chunk_id() >> 24 == '0')
	{
		aud_out = new short[size / 2];
		f.read_chunk(aud_out);
		size /= 4;
	}
	else
	{
		aud_out = new short[2 * size];
		vqa_d.decode_snd2_chunk(f.read_chunk().data(), size, aud_out);
	}
	if (AVIStreamWrite(a, audio_i, 2 * size, aud_out, 4 * size, 0, NULL, NULL))
		error = 1;
	else
		audio_i += 2 * size;
	delete[] aud_out;
	return error;
}

int Cvqa_file::extract_as_avi(const string& name, HWND hwnd)
{
	int error = 0;
	Cvqa_decode vqa_d;
	vqa_d.start_decode(header());
	int cx = get_cx();
	int cy = get_cy();
	AVIFileInit();
	PAVIFILE f = NULL;
	PAVISTREAM v = NULL;
	PAVISTREAM a = NULL;
	PAVISTREAM vc = NULL;
	if (AVIFileOpen(&f, name.c_str(), OF_CREATE | OF_WRITE, NULL))
		error = 1;
	else
	{
		AVISTREAMINFO vi;
		memset(&vi, 0, sizeof(AVISTREAMINFO));
		vi.fccType = streamtypeVIDEO; 
		vi.fccHandler = 0; 
		vi.dwFlags = get_cbits_pixel() == 8 ? AVISTREAMINFO_FORMATCHANGES : 0; 
		vi.dwScale = 1; 
		vi.dwRate = 15;
		vi.dwLength = get_c_frames();
		SetRect(&vi.rcFrame, 0, 0, cx, cy);
		if (AVIFileCreateStream(f, &v, &vi))
			error = 2;
		else
		{	
			AVISTREAMINFO ai;
			memset(&ai, 0, sizeof(AVISTREAMINFO));
			ai.fccType = streamtypeAUDIO; 
			ai.dwFlags = 0;
			ai.dwScale = 1;
			ai.dwRate = get_samplerate();
			ai.dwSampleSize = 2 * get_c_channels();
			if (get_c_channels() && AVIFileCreateStream(f, &a, &ai))
				error = 3;
			else
			{	
				AVICOMPRESSOPTIONS* vco = new AVICOMPRESSOPTIONS;
				if (!AVISaveOptions(hwnd, 0, 1, &v, &vco))
					error = 4;
				else 
				{
					if (AVIMakeCompressedStream(&vc, v, vco, NULL))
						error = 5;
					else				
					{
						int audio_i = 0;
						PCMWAVEFORMAT af;
						memset(&af, 0, sizeof(PCMWAVEFORMAT));
						af.wf.wFormatTag = WAVE_FORMAT_PCM;
						af.wf.nChannels = get_c_channels();
						af.wf.nSamplesPerSec = get_samplerate();
						af.wf.nAvgBytesPerSec = 2 * get_c_channels() * get_samplerate();
						af.wf.nBlockAlign = 2 * get_c_channels();
						af.wBitsPerSample = 16;
						if (get_c_channels() && AVIStreamSetFormat(a, 0, &af, sizeof(PCMWAVEFORMAT)))
							error = 6;
						else
						{
							const int cb_vf = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
							BITMAPINFO* vf = reinterpret_cast<BITMAPINFO*>(new byte[cb_vf]);
							memset(vf, 0, sizeof(BITMAPINFOHEADER));
							vf->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
							vf->bmiHeader.biWidth = cx; 
							vf->bmiHeader.biHeight = cy; 
							vf->bmiHeader.biPlanes = 1;
							vf->bmiHeader.biBitCount = get_cbits_pixel() == 8 ? 8 : 24;
							vf->bmiHeader.biCompression = BI_RGB ;
							vf->bmiHeader.biSizeImage = 0; 
							if (get_cbits_pixel() == 8)
							{
								t_palet palet;
								byte* frame = new byte[cx * cy];
								byte* frame_flipped = new byte[cx * cy];
								for (int i = 0; i < get_c_frames(); i++)
								{
									while (!is_video_chunk())
									{
										if (is_audio_chunk())
										{
											if (process_audio_chunk_for_avi(*this, vqa_d, audio_i, a))
											{
												error = 7;
												break;
											}
										}
										else
											skip_chunk();
									}
									if (error)
										break;
									vqa_d.decode_vqfr_chunk(read_chunk().data(), frame, palet);
									flip_frame(frame, frame_flipped, cx, cy, 1);
									for (int j = 0; j < 256; j++)
									{
										vf->bmiColors[j].rgbRed = palet[j].r;
										vf->bmiColors[j].rgbGreen = palet[j].g;
										vf->bmiColors[j].rgbBlue = palet[j].b;
									}
									// xcc_log::write_line("Writing frame " + n(i));
									if (!i && AVIStreamSetFormat(vc, 0, vf, cb_vf))
									{
										error = 8;
										break;
									}
									if (AVIStreamWrite(vc, i, 1, frame_flipped, cx * cy, 0, NULL, NULL))
									{
										error = 9;
										break;
									}
								}
								delete[] frame_flipped;
								delete[] frame;
							}
							else
							{
								if (AVIStreamSetFormat(vc, 0, vf, sizeof(BITMAPINFOHEADER)))
									error = 10;
								else
								{								
									DDPIXELFORMAT pf;
									pf.dwRGBAlphaBitMask = 0;
									pf.dwRBitMask = 0xff0000;
									pf.dwGBitMask = 0x00ff00;
									pf.dwBBitMask = 0x0000ff;
									vqa_d.set_pf(pf, 3);
									byte* frame = new byte[3 * cx * cy];
									byte* frame_flipped = new byte[3 * cx * cy];
									for (int i = 0; i < get_c_frames(); i++)
									{
										if (get_chunk_id() == vqa_vqfl_id)
											vqa_d.decode_vqfl_chunk(read_chunk());
										while (!is_video_chunk())
										{
											if (is_audio_chunk())
											{
												if (process_audio_chunk_for_avi(*this, vqa_d, audio_i, a))
												{
													error = 11;
													break;
												}
											}
											else
												skip_chunk();
										}
										vqa_d.decode_vqfr_chunk(read_chunk().data(), frame, NULL);
										flip_frame(frame, frame_flipped, cx, cy, 3);
										// xcc_log::write_line("Writing frame " + n(i));
										if (AVIStreamWrite(vc, i, 1, frame_flipped, 3 * cx * cy, 0, NULL, NULL))
										{
											error = 12;
											break;
										}
									}
									delete[] frame_flipped;
									delete[] frame;
								}
							}
							delete vf;
						}
					}
					AVISaveOptionsFree(1, &vco);
				}
			}
		}
	}
	if (vc)
		AVIStreamRelease(vc);
	if (a)
		AVIStreamRelease(a);
	if (v)
		AVIStreamRelease(v);
	if (f)
		AVIFileRelease(f);
	AVIFileExit();
	return error;
}

int Cvqa_file::extract_as_pcx(const Cfname& name, t_file_type ft)
{
	int error = 0;
	Cvqa_decode vqa_d;
	vqa_d.start_decode(header());
	int cx = get_cx();
	int cy = get_cy();
	if (get_cbits_pixel() == 8)
	{
		t_palet palet;
		byte* frame = new byte[cx * cy];
		for (int i = 0; i < get_c_frames(); i++)
		{
			while (!is_video_chunk())
				skip_chunk();
			vqa_d.decode_vqfr_chunk(read_chunk().data(), frame, palet);
			Cfname t = name;
			t.set_title(name.get_ftitle() + " " + nwzl(4, i));
			error = image_file_write(t, ft, frame, palet, cx, cy);
			if (error)
				break;
		}
		delete[] frame;
	}
	else
	{
		DDPIXELFORMAT pf;
		pf.dwRGBAlphaBitMask = 0;
		pf.dwRBitMask = 0x0000ff;
		pf.dwGBitMask = 0x00ff00;
		pf.dwBBitMask = 0xff0000;
		vqa_d.set_pf(pf, 3);
		byte* frame = new byte[3 * cx * cy];
		for (int i = 0; i < get_c_frames(); i++)
		{
			if (get_chunk_id() == vqa_vqfl_id)
				vqa_d.decode_vqfl_chunk(read_chunk());
			while (!is_video_chunk())
				skip_chunk();
			vqa_d.decode_vqfr_chunk(read_chunk().data(), frame, NULL);
			Cfname t = name;
			t.set_title(name.get_ftitle() + " " + nwzl(4, i));
			error = image_file_write(t, ft, frame, NULL, cx, cy);
			if (error)
				break;
		}
		delete[] frame;
	}
	return error;
}

struct t_list_entry
{
	int c_samples;
	short* audio;
};

int Cvqa_file::extract_as_wav(const string& name)
{
	int error = 0;
	typedef vector<t_list_entry> t_list;
	t_list list;
	int cs_remaining = 0;	
	Cvqa_decode vqa_d;
	vqa_d.start_decode(header());
	for (int i = 0; i < get_c_frames(); i++)
	{
		while (1)
		{
			if (is_audio_chunk())
			{
				t_list_entry e;
				int size = get_chunk_size();
				if (get_chunk_id() >> 24 == '0')
				{
					e.c_samples = size >> 1;
					e.audio = new short[size / 2];
					read_chunk(e.audio);
					size /= 4;
				}
				else
				{
					e.c_samples = size << 1;
					e.audio = new short[2 * size];
					vqa_d.decode_snd2_chunk(read_chunk().data(), size, e.audio);
				}
				cs_remaining += e.c_samples;
				list.push_back(e);				
			}
			else if (is_video_chunk())
				break;				
			else
				skip_chunk();
		}
		skip_chunk();
	}
	Cfile32 f;
	error = f.open(name, GENERIC_WRITE);
	if (!error)
	{
		t_wav_header header;
		memset(&header, 0, sizeof(t_wav_header));
		header.file_header.id = wav_file_id;
		header.file_header.size = sizeof(header) - sizeof(header.file_header) + cs_remaining;
		header.form_type = wav_form_id;
		header.format_chunk.header.id = wav_format_id;
		header.format_chunk.header.size = sizeof(header.format_chunk) - sizeof(header.format_chunk.header);
		header.format_chunk.formattag = 1;
		header.format_chunk.c_channels = get_c_channels();
		header.format_chunk.samplerate = get_samplerate();
		header.format_chunk.byterate = 2 * get_c_channels() * get_samplerate();
		header.format_chunk.blockalign = 2 * get_c_channels();
		header.format_chunk.cbits_sample = 16;
		header.data_chunk_header.id = wav_data_id;
		header.data_chunk_header.size = cs_remaining << 1;
		error = f.write(&header, sizeof(t_wav_header));
		if (!error)
		{
			BOOST_FOREACH(auto& i, list)
			{
				f.write(i.audio, 2 * i.c_samples);
				delete[] i.audio;
			}
		}
		f.close();
	}
	return error;
}

int Cvqa_file::read_chunk_header()
{
	if (get_p() & 1)
		skip(1);
	int error = read(&m_chunk_header, sizeof(t_vqa_chunk_header));
	m_chunk_header.size = reverse(m_chunk_header.size);
	return error;
}

int Cvqa_file::read_chunk(void* data)
{
	int error = read(data, get_chunk_size());
	return error ? error : read_chunk_header();
}

Cvirtual_binary Cvqa_file::read_chunk()
{
	Cvirtual_binary d;
	return read_chunk(d.write_start(get_chunk_size())) ? Cvirtual_binary() : d;
}

void Cvqa_file::set_empty_chunk()
{
	m_chunk_header.size = 0;
}

int Cvqa_file::skip_chunk()
{
	skip(get_chunk_size());
	return read_chunk_header();	
}