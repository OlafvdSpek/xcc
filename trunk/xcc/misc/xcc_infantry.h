#pragma once

#include "mix_file.h"
#include "shp_file.h"
#include "shp_images.h"
#include "xcc_dirs.h"
#include "xcc_level.h"
#include "xcc_mixs.h"
#include "xif_key.h"

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
		char* long_name;
		char* short_name;
		long cx;
		long cy;
		dword flags;
		void* images;
		void* icon;
	};
	
	dword c_infantry();

	long load_data();
	long save_data();

	long load_images(bool load_icons);
	long get_id(const string& s);

	void destroy();
	t_infantry_data_entry infantry_data[];
}
