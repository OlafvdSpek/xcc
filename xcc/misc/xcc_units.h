#pragma once

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
		string long_name;
		string short_name;
		int cx;
		int cy;
		int base_ox;
		int base_oy;
		int flags;
		void* images;
		void* icon;
		int c_images;
		int c_rotations;
	};
	
	int load_data();
	int save_data();

	int load_images();
	t_unit_data_entry* get_id(const string&);

	t_unit_data_entry unit_data[];
}
