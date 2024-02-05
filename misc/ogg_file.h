/*
    XCC Utilities and Library
    Copyright (C) 2001  Olaf van der Spek  <olafvdspek@gmail.com>

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
#include "virtual_audio.h"

class Cogg_file : public Ccc_file_sh<t_ogg_header>
{
public:
	bool is_valid() const
	{
		return !(get_size() < sizeof(t_ogg_header) || memcmp(header().id, ogg_id, 4));
	}

	int decode(Cvirtual_audio& audio);
	int get_c_channels();
	int get_c_samples();
	int get_samplerate();
};
