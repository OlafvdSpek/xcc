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
#include "audio_idx_file.h"

int audio_idx_file_get_write_size(int c_sounds)
{
	return sizeof(t_audio_idx_header) + sizeof(t_audio_idx_entry) * c_sounds;
}

int audio_idx_file_write_header(void* w, int c_sounds)
{
	t_audio_idx_header& header = *reinterpret_cast<t_audio_idx_header*>(w);
	header.id = audio_idx_id;
	header.two = 2;
	header.c_sounds = c_sounds;
	return sizeof(t_audio_idx_header);
}

int audio_idx_file_write_entry(void* w, string fname, int offset, int size, int samplerate, int flags, int chunk_size)
{
	t_audio_idx_entry& entry = *reinterpret_cast<t_audio_idx_entry*>(w);
	assert(fname.length() < 16);
	strcpy(entry.fname, fname.c_str());
	entry.offset = offset;
	entry.size = size;
	entry.samplerate = samplerate;
	entry.flags = flags;
	entry.chunk_size = chunk_size;
	return sizeof(t_audio_idx_entry);
}
