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

#include "shp_images.h"

enum
{
	ud_flags_in_use = 1,
	ud_flags_icon = 2,
	ud_flags_red = 4,
	ud_flags_dino = 8,
	ud_flags_top = 0x10
};

namespace xcc_units
{
	struct t_unit_data_entry
	{
		string long_name;
		string short_name;
		int cx;
		int cy;
		int base_ox;
		int base_oy;
		int flags;
		shp_images::t_image_data* images;
		shp_images::t_image_data* icon;
		int c_rotations;
	};
	
	int load_data();
	int save_data();

	int load_images();
	t_unit_data_entry* get_id(const string&);

	t_unit_data_entry unit_data[];
}
