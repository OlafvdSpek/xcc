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
#include "fname.h"
#include "image_file.h"
#include "palet.h"

class Ctmp_ra_file : public Cimage_file<t_tmp_ra_header>
{
public:
	void decode(void*) const;

	bool is_valid() const
	{
		const t_tmp_ra_header& h = header();
		int size = get_size();
		return !(sizeof(t_tmp_ra_header) > size || 
			h.cx != 24 || 
			h.cy != 24 || 
			h.c_tiles > 64 ||
			h.zero1 ||
			h.size != size ||
			h.image_offset > size ||
			h.zero2);
	}

	int cb_pixel() const
	{
		return 1;
	}

	int cx() const
	{
		return 24 * get_cblocks_x();
	}

	int cy() const
	{
		return 24 * (get_cblocks_x() == 1 && get_cblocks_x() == 1 ? get_c_tiles() : get_cblocks_y());
	}

	int get_c_tiles() const
	{
		return header().c_tiles;
	}

	int get_cblocks_x() const
	{
		return header().cblocks_x;
	}

	int get_cblocks_y() const
	{
		return header().cblocks_y;
	}

	const byte* get_image(int i) const
	{
		return data() + header().image_offset + 576 * get_index1()[i];
	}

	const byte* get_index1() const
	{
		return data() + header().index1;
	}
};

int tmp_ra_file_write(const byte* s, byte* d, int cx, int cy);
