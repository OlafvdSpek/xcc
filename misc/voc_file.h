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

class Cvoc_file : public Ccc_file_sh<t_voc_header>  
{
public:
	int extract_as_wav(const string& name);

	bool is_valid()
	{
		const t_voc_header& h = header();
		return !(sizeof(t_voc_header) > get_size() ||
			strncmp(h.id, voc_id, strlen(voc_id)) ||
			h.offset + 4 + sizeof(t_voc_sound_data_header) > get_size() ||
			// header.version != 0x1129010a ||
			get_sound_data_header()->compression);
	}

	const t_voc_sound_data_header* get_sound_data_header() const
	{
		return reinterpret_cast<const t_voc_sound_data_header*>(data() + header().offset + 4);
	}

	const byte* get_sound_data() const
	{
		return reinterpret_cast<const byte*>(get_sound_data_header() + 1);
	}

	int get_c_samples() const
	{
		const byte* r = data() + header().offset + 1;
		return (r[0] | r[1] << 8 | r[2] << 16) - sizeof(t_voc_sound_data_header);
	}

	int get_samplerate() const
	{
		return 1000000 / (256 - get_sound_data_header()->samplerate);
	}
};
