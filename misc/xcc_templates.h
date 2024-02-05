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

#include "xcc_level.h"

enum
{
	td_flags_ridge = 1,
	td_flags_river = 2,
	td_flags_road = 4,
	td_flags_shore = 8,
	td_flags_type_specific = td_flags_ridge | td_flags_river | td_flags_road | td_flags_shore
};

struct t_template_data_entry
{
	int cx;
	int cy;
	long long buildable;
	long long moveable;
	int flags;
	byte* images;
};

class Cxcc_templates  
{
private:
	static array<shp_images::t_image_data*, 3> bib;
	static t_palet palet;
	static byte shade_rp[256];
	static t_template_data_entry template_data[0xd8];
	static byte template_list[256][64];
public:
	static int load_data();
	static int save_data();
	static int load_images(t_theater_id theater);

	static const byte* get_image(int v)
	{
		return template_data[v >> 8].images + 576 * (v & 0xff);
	}

	static const t_palet& get_palet()
	{
		return palet;
	}

	static const t_template_data_entry& get_template_data(int i)
	{
		return template_data[i];
	}

	static const byte* get_shade_rp()
	{
		return shade_rp;
	}

	static int convert_bin_data(int v)
	{
		return (v & 0xff) << 8 | template_list[v & 0xff][v >> 8];
	}

	static int deconvert_bin_data(int v)
	{
		int a = v >> 8;
		int b = 0;
		while (template_list[a][b] != (v & 0xff))
			b++;
		return b << 8 | a;
	}

	static bool moveable(int v)
	{
		return template_data[v >> 8].moveable >> (v & 0xff) & 1;
	}

	static void moveable(int v, bool w)
	{
		if (moveable(v) != w)
			template_data[v >> 8].moveable ^= static_cast<long long>(1) << (v & 0xff);
	}

	static shp_images::t_image_data* get_bib(int v)
	{
		return bib[v];
	}
};
