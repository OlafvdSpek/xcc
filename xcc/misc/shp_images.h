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
		int cx;
		int cy;
		int cf;
		byte* data;
		t_image_index_entry* index;
	};

	int load_shp(const Cshp_file& f, t_image_data*& p);
	int load_shp(const string& name, t_image_data*& p);
	const byte* get_shp(t_image_data* p, int index);
	const byte* get_shp(t_image_data* p, int index, int& cx, int& cy);
	void destroy_shp(t_image_data*& p);
	void set_theater(t_theater_id);
}