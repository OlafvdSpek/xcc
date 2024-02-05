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

#include <cc_file_sh.h>
#include <cc_structures.h>

class Cfnt_file : public Ccc_file_sh<t_fnt_header>
{
public:
	bool is_valid() const
	{
		const t_fnt_header& h = header();
		int size = get_size();
		if (sizeof(t_fnt_header) > size || 
			h.size != size ||
			h.id2 != 0x000e ||
			h.id3 != 0x0014 ||
			h.zero)
			return false;
		return get_version() == game_td ? 
			h.id1 == 0x0500 && h.id4 == 0x1012 : 
			h.id1 == 0x0002 && !h.id4;
	}

	t_game get_version() const
	{
		return header().id1 == 0x0500 ? game_td : game_ts;
	}

	int get_c_chars() const
	{
		return header().c_chars + 1;
	}

	int get_cmax_x() const
	{
		return header().cmax_x;
	}

	int get_cy() const
	{
		return header().cy;
	}

	int get_y(int i) const
	{
		return reinterpret_cast<const unsigned short*>(data() + header().cy_ofs)[i] & 0xff;
	}

	int get_cx(int i) const
	{
		return (data() + header().cx_ofs)[i];
	}

	int get_cy(int i) const
	{
		return reinterpret_cast<const unsigned short*>(data() + header().cy_ofs)[i] >> 8;
	}

	const byte* get_image(int i) const
	{
		return data() + reinterpret_cast<const unsigned short*>(data() + sizeof(t_fnt_header))[i];
	}
};
