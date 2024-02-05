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

#pragma once

#include "riff_file.h"
#include "virtual_file.h"

class Cwav_file : public Criff_file  
{
public:
	// virtual int process();
	int process_chunk(const t_riff_header& header);

	const t_riff_wave_format_chunk& get_format_chunk() const
	{
		return m_format_chunk;
	}

	const t_riff_wave_fact_chunk& get_fact_chunk() const
	{
		return m_fact_chunk;
	}

	const t_riff_header& get_data_header() const
	{
		return m_data_header;
	}

	int get_data_ofs() const
	{
		return m_data_ofs;
	}

	int get_data_size() const
	{
		return get_data_header().size;
	}
private:
	t_riff_header				m_data_header;
	int							m_data_ofs;
	t_riff_wave_format_chunk	m_format_chunk;
	t_riff_wave_fact_chunk		m_fact_chunk;
};

int wav_file_write_header(void* w, int c_samples, int samplerate, int cb_sample, int c_channels);
int wav_ima_adpcm_file_write_header(void* w, int cb_audio, int c_samples, int samplerate, int c_channels);
Cvirtual_file wav_ima_adpcm_file_write(const void* s, int cb_s, int c_samples, int samplerate, int c_channels);
int wav_ima_adpcm_file_write(string fname, const void* s, int cb_s, int c_samples, int samplerate, int c_channels);
Cvirtual_file wav_pcm_file_write(const void* s, int cb_s, int samplerate, int cb_sample, int c_channels);
int wav_pcm_file_write(string fname, const void* s, int cb_s, int samplerate, int cb_sample, int c_channels);
