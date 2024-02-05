/*
    XCC Utilities and Library
    Copyright (C) 2000  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "stdafx.h"
#include "wav_file.h"

#include "ima_adpcm_wav_encode.h"
#include "wav_structures.h"

/*
int Cwav_file::process()
{
	return Criff_file::process();
}
*/

int Cwav_file::process_chunk(const t_riff_header& header)
{
	if (m_validating)
	{
		if (header.id != riff_id || header.size != get_size() - sizeof(t_riff_header))
			return 1;
	}
	switch (header.id)
	{
	case riff_id:
		{
			t_riff_chunk chunk;
			if (read(&chunk, sizeof(t_riff_chunk)))
				return 1;
			if (m_validating)
				return chunk.id != riff_wave_id;
			int size = header.size - sizeof(t_riff_chunk);
			while (size)
			{
				if (sizeof(t_riff_header) > size)
					return 1;
				t_riff_header header;
				if (read(&header, sizeof(t_riff_header)))
					return 1;
				size -= sizeof(t_riff_header);
				if (header.size > size)
					return 1;
				int error = process_chunk(header);
				if (error)
					return error;
				size -= header.size;
			}
			return 0;
		}
	case riff_wave_format_id:
		if (read(&m_format_chunk, sizeof(t_riff_wave_format_chunk)))
			return 1;
		skip(header.size - sizeof(t_riff_wave_format_chunk));
		return 0;
	case riff_wave_fact_id:
		if (read(&m_fact_chunk, sizeof(t_riff_wave_fact_chunk)))
			return 1;
		skip(header.size - sizeof(t_riff_wave_fact_chunk));
		return 0;
	case riff_wave_data_id:
		m_data_header = header;
		m_data_ofs = get_p();
	}
	skip(header.size);
	return 0;
}

int wav_file_write_header(void* w, int c_samples, int samplerate, int cb_sample, int c_channels)
{
	t_wav_header& header = *reinterpret_cast<t_wav_header*>(w);
	memset(&header, 0, sizeof(t_wav_header));
	header.file_header.id = wav_file_id;
	header.file_header.size = sizeof(header) - sizeof(header.file_header) + cb_sample * c_samples * c_channels;
	header.form_type = wav_form_id;
	header.format_chunk.header.id = wav_format_id;
	header.format_chunk.header.size = sizeof(header.format_chunk) - sizeof(header.format_chunk.header);
	header.format_chunk.formattag = 1;
	header.format_chunk.c_channels = c_channels;
	header.format_chunk.samplerate = samplerate;
	header.format_chunk.byterate =  cb_sample * c_channels * samplerate;
	header.format_chunk.blockalign = cb_sample * c_channels;
	header.format_chunk.cbits_sample = cb_sample << 3;
	header.data_chunk_header.id = wav_data_id;
	header.data_chunk_header.size = cb_sample * c_samples * c_channels;
	return sizeof(t_wav_header);
}

int wav_ima_adpcm_file_write_header(void* w, int cb_audio, int c_samples, int samplerate, int c_channels)
{
	t_wav_ima_adpcm_header& header = *reinterpret_cast<t_wav_ima_adpcm_header*>(w);
	memset(&header, 0, sizeof(t_wav_ima_adpcm_header));
	header.file_header.id = wav_file_id;
	header.file_header.size = sizeof(header) - sizeof(header.file_header) + cb_audio;
	header.form_type = wav_form_id;
	header.format_chunk.header.id = wav_format_id;
	header.format_chunk.header.size = sizeof(header.format_chunk) - sizeof(header.format_chunk.header);
	header.format_chunk.formattag = 0x11;
	header.format_chunk.c_channels = c_channels;
	header.format_chunk.samplerate = samplerate;
	header.format_chunk.byterate =  11100 * c_channels * samplerate / 22050;
	header.format_chunk.blockalign = 512 * c_channels;
	header.format_chunk.cbits_sample = 4;
	header.format_chunk.cb_extra = 2;
	header.format_chunk.cb_block = 1017;
	header.fact_chunk.header.id = wav_fact_id;
	header.fact_chunk.header.size = sizeof(t_wav_fact_chunk) - sizeof(t_wav_chunk_header);
	header.fact_chunk.c_samples = c_samples;
	header.data_chunk_header.id = wav_data_id;
	header.data_chunk_header.size = cb_audio;
	return sizeof(t_wav_ima_adpcm_header);
}

Cvirtual_file wav_ima_adpcm_file_write(const void* s, int cb_s, int c_samples, int samplerate, int c_channels)
{
	Cima_adpcm_wav_encode encode;
	encode.load(reinterpret_cast<const short*>(s), cb_s, c_channels);
	int cb_audio = encode.cb_data();
	Cvirtual_binary d;
	byte* w = d.write_start(sizeof(t_wav_ima_adpcm_header) + cb_audio);
	w += wav_ima_adpcm_file_write_header(w, cb_audio, c_samples, samplerate, c_channels);
	memcpy(w, encode.data(), cb_audio);
	return d;
}

int wav_ima_adpcm_file_write(string fname, const void* s, int cb_s, int c_samples, int samplerate, int c_channels)
{
	return wav_ima_adpcm_file_write(s, cb_s, c_samples, samplerate, c_channels).save(fname);
}

Cvirtual_file wav_pcm_file_write(const void* s, int cb_s, int samplerate, int cb_sample, int c_channels)
{
	Cvirtual_binary d;
	byte* w = d.write_start(sizeof(t_wav_header) + cb_s);
	w += wav_file_write_header(w, cb_s / (cb_sample * c_channels), samplerate, cb_sample, c_channels);
	memcpy(w, s, cb_s);
	return d;
}

int wav_pcm_file_write(string fname, const void* s, int cb_s, int samplerate, int cb_sample, int c_channels)
{
	return wav_pcm_file_write(s, cb_s, samplerate, cb_sample, c_channels).save(fname);
}