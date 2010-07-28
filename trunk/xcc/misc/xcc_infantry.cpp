#include "stdafx.h"
#include "cc_file.h"
#include "xcc_infantry.h"

namespace xcc_infantry
{
	t_infantry_data_entry infantry_data[256];
}

static const char* infantry_xif_fname = "infantry.xif";

enum
{
	vi_id_long_name,
	vi_id_short_name,
	vi_id_cx,
	vi_id_cy,
	vi_id_flags,
};

int xcc_infantry::c_infantry()
{
	for (int i = 0; i < 256; i++)
	{
		if (~infantry_data[i].flags & id_flags_in_use)
			return i;
	}
	return 0;
}

int xcc_infantry::load_data()
{
	Cxif_key infantry_key;
	if (infantry_key.load_key(Cvirtual_binary(xcc_dirs::get_data_dir() + infantry_xif_fname)))
		return 1;
	int infantry_i = 0;
	BOOST_FOREACH(auto& i, infantry_key.m_keys)
	{
		t_infantry_data_entry& id = infantry_data[infantry_i];
		Cxif_key& ik = i.second;
		id.long_name = ik.get_value_string(vi_id_long_name);
		id.short_name = ik.get_value_string(vi_id_short_name);
		id.cx = ik.get_value_int(vi_id_cx);
		id.cy = ik.get_value_int(vi_id_cy);
		id.flags = ik.get_value_int(vi_id_flags);
		infantry_i++;
	}
	return 0;
}

int xcc_infantry::save_data()
{
	typedef map<string, int> t_list;
	t_list list;	
	{
		for (int i = 0; i < 256; i++)
		{
			t_infantry_data_entry& id = infantry_data[i];
			if (~id.flags & id_flags_in_use)
				// don't save if not in use
				continue;
			list[id.short_name] = i;
		}
	}
	Cxif_key infantry_key;
	int infantry_i = 0;
	BOOST_FOREACH(auto& i, list)
	{
		t_infantry_data_entry& id = infantry_data[i.second];
		Cxif_key& ik = infantry_key.set_key(infantry_i);
		ik.set_value_string(vi_id_long_name, id.long_name);
		ik.set_value_string(vi_id_short_name, id.short_name);
		ik.set_value_int(vi_id_cx, id.cx);
		ik.set_value_int(vi_id_cy, id.cy);
		ik.set_value_int(vi_id_flags, id.flags);
		infantry_i++;
	}
	return infantry_key.vdata().save(xcc_dirs::get_data_dir() + infantry_xif_fname);
}

int xcc_infantry::load_images(bool load_icons)
{
	int error = 0;
	static bool loaded = false;
	if (loaded)
		return 0;
	Cmix_file& conquer_mix = Cxcc_mixs::get_conquer_mix();
	for (int i = 0; i < 256; i++)
	{
		t_infantry_data_entry& id = infantry_data[i];
		if (~id.flags & id_flags_in_use)
			continue;
		Cshp_file f;
		// images
		f.open(static_cast<string>(id.short_name) + ".shp", conquer_mix);
		if (!f.is_open())
		{
			error = 1;
			continue;
		}
		if (shp_images::load_shp(f, id.images))
			error = 1;
		f.close();
		if (load_icons && id.flags & id_flags_icon)
		{
			// icon
			f.open(static_cast<string>(id.short_name) + "icon.shp", conquer_mix);
			if (!f.is_open())
			{
				error = 1;
				continue;
			}
			if (shp_images::load_shp(f, id.icon))
				error = 1;
			f.close();
		}
	}
	if (!error)
		loaded = true;
	return error;
}

void xcc_infantry::destroy()
{
	for (int i = 0; i < 256; i++)
	{
		t_infantry_data_entry& id = infantry_data[i];
	}
}

int xcc_infantry::get_id(const string& s)
{
	for (int i = 0; i < 256; i++)
	{
		t_infantry_data_entry& id = infantry_data[i];
		if (id.flags & id_flags_in_use && id.short_name == s)
			return i;
	}
	return -1;
}