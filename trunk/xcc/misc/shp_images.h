#pragma once

#include "shp_file.h"

namespace shp_images  
{
	int load_shp(const Cshp_file& f, void*& p);
	int load_shp(const string& name, Cmix_file& mix, void*& p);
	int load_shp(const string& name, void*& p);
	const byte* get_shp(void* p, int index);
	const byte* get_shp(void* p, int index, int& cx, int& cy);
	int get_shp_c_images(void* p);
	void destroy_shp(void*& p);

	inline const byte* get_shp(void* p, int index, long& _cx, long& _cy)
	{
		int cx, cy;
		const byte* r = get_shp(p, index, cx, cy);
		_cx = cx;
		_cy = cy;
		return r;
	}
}