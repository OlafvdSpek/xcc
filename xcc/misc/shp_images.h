#pragma once

#include "shp_file.h"
#include "xcc_level.h"

namespace shp_images  
{
	int load_shp(const Cshp_file& f, void*& p);
	int load_shp(const string& name, void*& p);
	const byte* get_shp(void* p, int index);
	const byte* get_shp(void* p, int index, int& cx, int& cy);
	int get_shp_c_images(void* p);
	void destroy_shp(void*& p);
	void set_theater(t_theater_id);

	inline const byte* get_shp(void* p, int index, long& _cx, long& _cy)
	{
		int cx, cy;
		const byte* r = get_shp(p, index, cx, cy);
		_cx = cx;
		_cy = cy;
		return r;
	}
}