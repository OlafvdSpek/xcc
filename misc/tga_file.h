/*
    XCC Utilities and Library
    Copyright (C) 2002  Olaf van der Spek  <olafvdspek@gmail.com>

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
#include "virtual_image.h"

class Ctga_file : public Ccc_file_sh<t_tga_header>
{
public:
	int decode(Cvirtual_image& d) const;
	bool is_valid() const;

	int cx() const
	{
		return header().cx;
	}

	int cy() const
	{
		return header().cy;
	}

	int cb_pixel() const
	{
		return header().cb_pixel >> 3;
	}

	const byte* image() const
	{
		return data() + sizeof(t_tga_header) + header().id_size;
	}
};

Cvirtual_file tga_file_write(const byte* image, int cx, int cy, int cb_pixel);
Cvirtual_file tga_file_write(const byte* image, int cx, int cy, const t_palet_entry* palet);
