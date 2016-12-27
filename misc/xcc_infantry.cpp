#include "stdafx.h"
#include "xcc_infantry.h"

#include "cc_file.h"
#include "shp_file.h"
#include "shp_images.h"
#include "xcc_dirs.h"
#include "xcc_mixs.h"
#include "xif_key.h"

xcc_infantry::t_infantry_data_entry xcc_infantry::infantry_data[256];

static const char* infantry_xif_fname = "infantry.xif";

enum
{
	vi_id_long_name,
	vi_id_short_name,
	vi_id_cx,
	vi_id_cy,
	vi_id_flags,
};

int xcc_infantry::load_data()
{
	Cxif_key infantry_key;
	if (infantry_key.load_key(Cvirtual_binary(xcc_dirs::get_data_dir() + infantry_xif_fname)))
		return 1;
	int infantry_i = 0;
	for (auto& i : infantry_key.m_keys)
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
	map<string, t_infantry_data_entry*> list;	
	for (auto& id : infantry_data)
	{
		if (id.flags & id_flags_in_use)
			list[id.short_name] = &id;
	}
	Cxif_key infantry_key;
	int infantry_i = 0;
	for (auto& i : list)
	{
		t_infantry_data_entry& id = *i.second;
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

int xcc_infantry::load_images()
{
	static bool loaded = false;
	if (loaded)
		return 0;
	for (auto& id : infantry_data)
	{
		if (~id.flags & id_flags_in_use)
			continue;
		if (shp_images::load_shp(id.short_name, id.images))
			return 1;
		if (id.flags & id_flags_icon && shp_images::load_shp(id.short_name + "icon", id.icon))
			return 1;
	}
	loaded = true;
	return 0;
}

xcc_infantry::t_infantry_data_entry* xcc_infantry::get_id(const string& s)
{
	for (auto& id : infantry_data)
	{
		if (id.flags & id_flags_in_use && iequals(id.short_name, s))
			return &id;
	}
	assert(false);
	return NULL;
}