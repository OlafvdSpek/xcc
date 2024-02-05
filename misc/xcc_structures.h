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

enum t_theater_id;

enum
{
	sd_flags_in_use = 1,
	sd_flags_icon = 2,
	sd_flags_civilian = 4,
	sd_flags_images2 = 8,
	sd_flags_desert = 0x10,
	sd_flags_temperate = 0x20,
	sd_flags_winter = 0x40,
	sd_flags_bib = 0x80,
	sd_flags_wall = 0x100,
	sd_flags_theater_specific = sd_flags_desert | sd_flags_temperate | sd_flags_winter
};

namespace xcc_structures
{
	struct t_structure_data_entry
	{
		string long_name;
		string short_name;
		int cx;
		int cy;
		int flags;
		shp_images::t_image_data* images;
		shp_images::t_image_data* images2;
		shp_images::t_image_data* icon;
		unsigned int blocked;
		unsigned int ground;
		int power_in;
		int power_out;
	};
	
	int load_data();
	int save_data();

	int load_images(t_theater_id);
	t_structure_data_entry* get_id(const string&);

	t_structure_data_entry structure_data[];
}
