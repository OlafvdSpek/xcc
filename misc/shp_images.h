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