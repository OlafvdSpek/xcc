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
	ud_flags_in_use = 1,
	ud_flags_icon = 2,
	ud_flags_red = 4,
	ud_flags_dino = 8,
	ud_flags_top = 0x10
};

namespace xcc_units
{
	struct t_unit_data_entry
	{
		char* long_name;
		char* short_name;
		int cx;
		int cy;
		int base_ox;
		int base_oy;
		dword flags;
		void* images;
		void* icon;
		int c_images;
		int c_rotations;
	};
	
	dword c_units();

	int load_data();
	int save_data();

	int load_images(bool load_icons);
	int get_id(const string& s);

	void destroy();
	t_unit_data_entry unit_data[];
}
