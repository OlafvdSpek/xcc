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
#include "voc_file.h"

#include "wav_structures.h"

int Cvoc_file::extract_as_wav(const string& name)
{
	int error = 0;
	Cfile32 f;
	error = f.open(name, GENERIC_WRITE);
	if (!error)
	{
		int cs_remaining = get_c_samples();	
		t_wav_header header;
		memset(&header, 0, sizeof(t_wav_header));
		header.file_header.id = wav_file_id;
		header.file_header.size = sizeof(header) - sizeof(header.file_header) + (cs_remaining << 1);
		header.form_type = wav_form_id;
		header.format_chunk.header.id = wav_format_id;
		header.format_chunk.header.size = sizeof(header.format_chunk) - sizeof(header.format_chunk.header);
		header.format_chunk.formattag = 1;
		header.format_chunk.c_channels = 1;
		header.format_chunk.samplerate = get_samplerate();
		header.format_chunk.byterate =  get_samplerate();
		header.format_chunk.blockalign = 1;
		header.format_chunk.cbits_sample = 8;
		header.data_chunk_header.id = wav_data_id;
		header.data_chunk_header.size = cs_remaining;
		error = f.write(&header, sizeof(t_wav_header));
		if (!error)
			error = f.write(get_sound_data(), cs_remaining);
		f.close();
	}
	return error;
}