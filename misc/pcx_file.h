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

#include "cc_structures.h"
#include "image_file.h"
#include "palet.h"
#include "pcx_decode.h"
#include "virtual_image.h"

class Cpcx_file : public Cimage_file<t_pcx_header>
{
public:
	void decode(void*) const;
	bool is_valid() const;
	Cvirtual_image vimage() const;

	int cb_pixel() const
	{
		return header().c_planes;
	}

	int cx() const
	{
		return header().xmax - header().xmin + 1;
	}

	int cy() const
	{
		return header().ymax - header().ymin + 1;
	}

	void decode(byte* d) const
	{
		pcx_decode(get_image(), d, header());
	}

	const byte* get_image() const
	{
		return data() + sizeof(t_pcx_header);
	}

	const t_palet* get_palet() const
	{
		return reinterpret_cast<const t_palet*>(data() + size() - sizeof(t_palet));
	}
};
