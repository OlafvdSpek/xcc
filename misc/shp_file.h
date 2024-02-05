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
#include "fname.h"
#include "palet.h"
#include "video_file.h"
#include "virtual_image.h"

const int shp_o_mask = 0x0fffffff;

class Cshp_file : public Cvideo_file<t_shp_header>  
{
public:
	void decode(void* d) const;
	Cvideo_decoder* decoder(const t_palet_entry*);
	bool is_valid() const;
	Cvirtual_image vimage() const;

	int cb_pixel() const
	{
		return 1;
	}

	int cf() const
	{
		return header().c_images;
	}

	int cx() const
	{
		return header().cx;
	}

	int cy() const
	{
		return header().cy;
	}

    int get_format(int i) const
	{
        return static_cast<unsigned int>(get_index()[i << 1]) >> 28;
	}

	const byte* get_image(int i) const
	{
		return data() + get_offset(i);
	}

	const int* get_index() const
    {
        return reinterpret_cast<const int*>(data() + sizeof(t_shp_header));
    }

    int get_offset(int i) const
    {
        return get_index()[i << 1] & shp_o_mask;
    }

    int get_ref_offset(int i) const
    {
        return get_index()[(i << 1) + 1] & shp_o_mask;
    }
};

Cvirtual_binary shp_file_write(const byte* s, int cx, int cy, int c_images);
