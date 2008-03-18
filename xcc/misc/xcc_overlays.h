#pragma once

#include "shp_images.h"
#include "xcc_level.h"
#include "xcc_mixs.h"
#include "xif_key.h"

class Cxcc_overlays  
{
public:
	static bool terrain_blocked(int v);
	static void terrain_switch_blocked(int v);
	static const byte* get_overlay_image(int v, int& x, int& y, int& cx, int& cy);
	static const byte* get_terrain_image(int v, int& x, int& y, int& cx, int& cy);
	static bool terrain_in(int v, t_theater_id theater);
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
