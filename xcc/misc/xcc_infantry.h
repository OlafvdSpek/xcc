#pragma once

#include "shp_images.h"

enum
{
	id_flags_in_use = 1,
	id_flags_icon = 2,
	id_flags_civilian = 4,
};

namespace xcc_infantry
{
	struct t_infantry_data_entry
	{
		string long_name;
		string short_name;
		int cx;
		int cy;
		int flags;
		shp_images::t_image_data* images;
		shp_images::t_image_data* icon;
	};
	
	int load_data();
	int save_data();

	int load_images();
	t_infantry_data_entry* get_id(const string&);

	t_infantry_data_entry infantry_data[];
}
