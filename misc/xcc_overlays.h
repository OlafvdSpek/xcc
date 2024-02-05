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

class Cxcc_overlays  
{
public:
	static bool terrain_blocked(int v);
	static void terrain_switch_blocked(int v);
	static const byte* get_overlay_image(int v, int& x, int& y, int& cx, int& cy);
	static const byte* get_terrain_image(int v, int& x, int& y, int& cx, int& cy);
	static void destroy();
	static int load_data();
	static int save_data();
	static int load_images(t_theater_id theater);

	static const byte* get_terrain_image(int v, int& x, int& y, long& _cx, long& _cy)
	{
		int cx, cy;
		const byte* r = get_terrain_image(v, x, y, cx, cy);
		_cx = cx;
		_cy = cy;
		return r;
	}
};
