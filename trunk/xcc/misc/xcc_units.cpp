#include "stdafx.h"
#include "xcc_units.h"

namespace xcc_units
{
	t_unit_data_entry unit_data[256];
}

static const char* units_xif_fname = "units.xif";
Cxif_key units_key;

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

dword xcc_units::c_units()
{
	for (int i = 0; i < 256; i++)
	{
		if (~unit_data[i].flags & ud_flags_in_use)
			return i;
	}
	return 0;
}

int xcc_units::load_data()
{
	Ccc_file f(false);
	f.open(xcc_dirs::get_data_dir() + units_xif_fname);
	if (!f.is_open())
		return 1;
	const dword size = f.get_size();
	byte* data = new byte[size];
	f.read(data, size);
	f.close();
	units_key.load_key(data, size);
	delete[] data;
	int unit_i = 0;
	for (t_xif_key_map::iterator i = units_key.m_keys.begin(); i != units_key.m_keys.end(); i++)
	{
		t_unit_data_entry& ud = unit_data[unit_i];
		Cxif_key& uk = i->second;
		ud.long_name = uk.get_value_c_str(vi_ud_long_name);
		ud.short_name = uk.get_value_c_str(vi_ud_short_name);
		ud.cx = uk.get_value_dword(vi_ud_cx);
		ud.cy = uk.get_value_dword(vi_ud_cy);
		ud.base_ox = 0;
		ud.base_oy = 0;
		ud.flags = uk.get_value_dword(vi_ud_flags);
		ud.c_rotations = uk.get_value_dword(vi_ud_c_rotations);
		for (t_xif_value_map::const_iterator i = uk.m_values.begin(); i != uk.m_values.end(); i++)
		{
			switch (i->first)
			{
			case vi_ud_base_ox:
				ud.base_ox = i->second.get_data_dword();
				break;
			case vi_ud_base_oy:
				ud.base_oy = i->second.get_data_dword();
				break;
			}
		}
		unit_i++;
	}
	return 0;
}

int xcc_units::save_data()
{
	typedef map<string, int> t_list;
	t_list list;	
	{
		for (int i = 0; i < 256; i++)
		{
			t_unit_data_entry& ud = unit_data[i];
			if (~ud.flags & ud_flags_in_use)
				// don't save if not in use
				continue;
			list[static_cast<string>(ud.short_name)] = i;
		}
	}
	units_key.delete_all_keys();
	int unit_i = 0;
	for (t_list::const_iterator i = list.begin(); i != list.end(); i++)
	{
		t_unit_data_entry& ud = unit_data[i->second];
		Cxif_key& uk = units_key.set_key(unit_i);
		uk.set_value(vi_ud_long_name, ud.long_name);
		uk.set_value(vi_ud_short_name, ud.short_name);
		uk.set_value(vi_ud_cx, static_cast<dword>(ud.cx));
		uk.set_value(vi_ud_cy, static_cast<dword>(ud.cy));
		if (ud.base_ox)
			uk.set_value(vi_ud_base_ox, static_cast<dword>(ud.base_ox));
		if (ud.base_oy)
			uk.set_value(vi_ud_base_oy, static_cast<dword>(ud.base_oy));
		uk.set_value(vi_ud_flags, ud.flags);
		uk.set_value(vi_ud_c_rotations, static_cast<dword>(ud.c_rotations));
		unit_i++;
	}
	Cfile32 f;
	if (f.open_write(xcc_dirs::get_data_dir() + units_xif_fname))
		return 1;
	dword size = units_key.key_size();
	byte* data = new byte[size];
	units_key.save_key(data);
	f.write(data, size);
	delete[] data;
	f.close();
	return 0;
}

int xcc_units::load_images(bool load_icons)
{
	int error = 0;
	static bool loaded = false;
	if (loaded)
		return 0;
	Cmix_file& conquer_mix = Cxcc_mixs::get_conquer_mix();
	for (int i = 0; i < 256; i++)
	{
		t_unit_data_entry& ud = unit_data[i];
		if (~ud.flags & ud_flags_in_use)
			continue;
		Cshp_file f;
		// images
		f.open(static_cast<string>(ud.short_name) + ".shp", conquer_mix);
		if (!f.is_open())
		{
			error = 1;
			continue;
		}
		if (shp_images::load_shp(f, ud.images))
			error = 1;
		f.close();
		// shp_images::get_shp(ud.images, 0, ud.cx, ud.cy);
		ud.c_images = shp_images::get_shp_c_images(ud.images);
		if (load_icons && ud.flags & ud_flags_icon)
		{
			// icon
			f.open(static_cast<string>(ud.short_name) + "icon.shp", conquer_mix);
			if (!f.is_open())
			{
				error = 1;
				continue;
			}
			if (shp_images::load_shp(f, ud.icon))
				error = 1;
			f.close();
		}
	}
	if (!error)
		loaded = true;
	return error;
}

void xcc_units::destroy()
{
	for (int i = 0; i < 256; i++)
	{
		t_unit_data_entry& ud = unit_data[i];
		delete[] ud.long_name;
		delete[] ud.short_name;;
	}
}

int xcc_units::get_id(const string& s)
{
	for (int i = 0; i < 256; i++)
	{
		t_unit_data_entry& ud = unit_data[i];
		if (ud.flags & ud_flags_in_use && (ud.short_name == s))
			return i;
	}
	return -1;
}