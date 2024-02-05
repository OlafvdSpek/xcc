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

#include "shp_file.h"

enum t_theater_id;

namespace shp_images  
{
	struct t_image_index_entry
	{
		byte* data_in;
		byte* data_out;
		int format;
	};

	struct t_image_data
	{
		const byte* get(int f);
		const byte* get(int f, int& cx, int& cy);

		int cx;
		int cy;
		int cf;
		byte* data;
		t_image_index_entry* index;
	};

	int load_shp(const Cshp_file& f, t_image_data*& p);
	int load_shp(const string& name, t_image_data*& p);
	void destroy_shp(t_image_data*& p);
	void set_theater(t_theater_id);
}