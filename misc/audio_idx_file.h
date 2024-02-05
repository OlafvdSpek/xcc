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

#include "cc_file_sh.h"
#include "cc_structures.h"

class Caudio_idx_file : public Ccc_file_sh<t_audio_idx_header>
{
public:
	bool is_valid() const
	{
		const t_audio_idx_header& h = header();
		int size = get_size();
		return !(sizeof(t_audio_idx_header) > size || 
			h.id != audio_idx_id ||
			h.two != 2 ||
			sizeof(t_audio_idx_header) + sizeof(t_audio_idx_entry) * h.c_sounds != size);
	}

	int c_sounds() const
	{
		return header().c_sounds;
	}

	const t_audio_idx_entry& sound_entry(int i) const
	{
		return reinterpret_cast<const t_audio_idx_entry*>(data() + sizeof(t_audio_idx_header))[i];
	}
};

int audio_idx_file_get_write_size(int c_sounds);
int audio_idx_file_write_header(void* w, int c_sounds);
int audio_idx_file_write_entry(void* w, string fname, int offset, int size, int samplerate, int flags, int chunk_size);
