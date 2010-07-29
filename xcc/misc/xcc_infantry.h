#pragma once

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
		void* images;
		void* icon;
	};
	
	int c_infantry();

	int load_data();
	int save_data();

	int load_images(bool load_icons);
	int get_id(const string& s);

	void destroy();
	t_infantry_data_entry infantry_data[];
}
