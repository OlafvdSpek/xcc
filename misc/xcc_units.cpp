#include "stdafx.h"
#include "xcc_units.h"

#include "mix_file.h"
#include "shp_file.h"
#include "shp_images.h"
#include "xcc_dirs.h"
#include "xcc_level.h"
#include "xcc_mixs.h"
#include "xif_key.h"

xcc_units::t_unit_data_entry xcc_units::unit_data[256];

static const char* units_xif_fname = "units.xif";

enum
{
	vi_ud_long_name,
	vi_ud_short_name,
	vi_ud_cx,
	vi_ud_cy,
	vi_ud_flags,
	vi_ud_base_ox,
	vi_ud_base_oy,
	vi_ud_c_rotations
};

int xcc_units::load_data()
{
	Cxif_key units_key;
	if (units_key.load_key(Cvirtual_binary(xcc_dirs::get_data_dir() + units_xif_fname)))
		return 1;
	int unit_i = 0;
	for (t_xif_key_map::iterator i = units_key.m_keys.begin(); i != units_key.m_keys.end(); i++)
	{
		t_unit_data_entry& ud = unit_data[unit_i];
		Cxif_key& uk = i->second;
		ud.long_name = uk.get_value_string(vi_ud_long_name);
		ud.short_name = uk.get_value_string(vi_ud_short_name);
		ud.cx = uk.get_value_int(vi_ud_cx);
		ud.cy = uk.get_value_int(vi_ud_cy);
		ud.base_ox = 0;
		ud.base_oy = 0;
		ud.flags = uk.get_value_int(vi_ud_flags);
		ud.c_rotations = uk.get_value_int(vi_ud_c_rotations);
		for (t_xif_value_map::const_iterator i = uk.m_values.begin(); i != uk.m_values.end(); i++)
		{
			switch (i->first)
			{
			case vi_ud_base_ox:
				ud.base_ox = i->second.get_int();
				break;
			case vi_ud_base_oy:
				ud.base_oy = i->second.get_int();
				break;
			}
		}
		unit_i++;
	}
	return 0;
}

int xcc_units::save_data()
{
	map<string, t_unit_data_entry*> list;	
	for (auto& ud : unit_data)
	{
		if (ud.flags & ud_flags_in_use)
			list[ud.short_name] = &ud;
	}
	Cxif_key units_key;
	int unit_i = 0;
	for (auto& i : list)
	{
		t_unit_data_entry& ud = *i.second;
		Cxif_key& uk = units_key.set_key(unit_i);
		uk.set_value_string(vi_ud_long_name, ud.long_name);
		uk.set_value_string(vi_ud_short_name, ud.short_name);
		uk.set_value_int(vi_ud_cx, ud.cx);
		uk.set_value_int(vi_ud_cy, ud.cy);
		if (ud.base_ox)
			uk.set_value_int(vi_ud_base_ox, ud.base_ox);
		if (ud.base_oy)
			uk.set_value_int(vi_ud_base_oy, ud.base_oy);
		uk.set_value_int(vi_ud_flags, ud.flags);
		uk.set_value_int(vi_ud_c_rotations, ud.c_rotations);
		unit_i++;
	}
	return units_key.vdata().save(xcc_dirs::get_data_dir() + units_xif_fname);
}

int xcc_units::load_images()
{
	static bool loaded = false;
	if (loaded)
		return 0;
	for (auto& ud : unit_data)
	{
		if (~ud.flags & ud_flags_in_use)
			continue;
		if (shp_images::load_shp(ud.short_name, ud.images))
			return 1;
		if (ud.flags & ud_flags_icon && shp_images::load_shp(ud.short_name + "icon", ud.icon))
			return 1;
	}
	loaded = true;
	return 0;
}

xcc_units::t_unit_data_entry* xcc_units::get_id(const string& s)
{
	for (auto& ud : unit_data)
	{
		if (ud.flags & ud_flags_in_use && iequals(ud.short_name, s))
			return &ud;
	}
	assert(false);
	return NULL;
}