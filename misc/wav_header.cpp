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
#include "wav_header.h"

void wav_fill_header(t_wav_header& header, int samplesize, int samplerate, int cbits_sample, int c_channels)
{
	header.file_header.id = wav_file_id;
	header.file_header.size = sizeof(header) - sizeof(header.file_header) + samplesize;
	header.form_type = wav_form_id;
	header.format_chunk.header.id = wav_format_id;
	header.format_chunk.header.size = sizeof(header.format_chunk) - sizeof(header.format_chunk.header);
	header.format_chunk.formattag = 1;
	header.format_chunk.c_channels = short(c_channels);
	header.format_chunk.samplerate = samplerate;
	header.format_chunk.byterate = (cbits_sample >> 3) * c_channels * samplerate;
	header.format_chunk.blockalign = short((cbits_sample >> 3) * c_channels);
	header.format_chunk.cbits_sample = short(cbits_sample);
	header.data_chunk_header.id = wav_data_id;
	header.data_chunk_header.size = samplesize;
}