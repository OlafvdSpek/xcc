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
		long cx;
		long cy;
		dword flags;
		void* images;
		void* images2;
		void* icon;
		dword blocked;
		dword ground;
		long power_in;
		long power_out;
	};
	
	dword c_structures();

	long load_data();
	long save_data();

	long load_images(t_theater_id theater, bool load_icons);
	long get_id(const string& s);

	void destroy();
	t_structure_data_entry structure_data[];
}
