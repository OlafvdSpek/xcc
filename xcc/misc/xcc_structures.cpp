#include "stdafx.h"
#include "xcc_structures.h"

namespace xcc_structures
{
	t_structure_data_entry structure_data[256];
}

static const char* structures_xif_fname = "structures.xif";

enum
{
	vi_sd_long_name,
	vi_sd_short_name,
	vi_sd_cx,
	vi_sd_cy,
	vi_sd_flags,
	vi_sd_blocked,
	vi_sd_ground,
	vi_sd_power_in,
	vi_sd_power_out
};

dword xcc_structures::c_structures()
{
	for (int i = 0; i < 256; i++)
	{
		if (~structure_data[i].flags & sd_flags_in_use)
			return i;
	}
	return 0;
}

int xcc_structures::load_data()
{
	Ccc_file f(true);
	f.open(xcc_dirs::get_data_dir() + structures_xif_fname);
	if (!f.is_open())
		return 1;
	Cxif_key structures_key;
	structures_key.load_key(f.get_vdata());
	f.close();
	int structure_i = 0;
	for (t_xif_key_map::iterator i = structures_key.m_keys.begin(); i != structures_key.m_keys.end(); i++)
	{
		t_structure_data_entry& sd = structure_data[structure_i];
		Cxif_key& sk = i->second;
		sd.long_name = sk.get_value_string(vi_sd_long_name);
		sd.short_name = sk.get_value_string(vi_sd_short_name);
		sd.cx = sk.get_value_int(vi_sd_cx);
		sd.cy = sk.get_value_int(vi_sd_cy);
		sd.flags = sk.get_value_int(vi_sd_flags);
		sd.blocked = sk.get_value_int(vi_sd_blocked);
		sd.ground = 0;
		sd.power_in = 0;
		sd.power_out = 0;
		for (t_xif_value_map::const_iterator i = sk.m_values.begin(); i != sk.m_values.end(); i++)
		{
			switch (i->first)
			{
			case vi_sd_ground:
				sd.ground = i->second.get_int();
				break;
			case vi_sd_power_in:
				sd.power_in = i->second.get_int();
				break;
			case vi_sd_power_out:
				sd.power_out = i->second.get_int();
				break;
			}
		}
		structure_i++;
	}
	return 0;
}

int xcc_structures::save_data()
{
	typedef map<string, int> t_list;
	t_list list;	
	{
		for (int i = 0; i < 256; i++)
		{
			t_structure_data_entry& sd = structure_data[i];
			if (~sd.flags & sd_flags_in_use)
				// don't save if not in use
				continue;
			list[sd.short_name] = i;
		}
	}
	Cxif_key structures_key;
	int structure_i = 0;
	for (t_list::const_iterator i = list.begin(); i != list.end(); i++)
	{
		t_structure_data_entry& sd = structure_data[i->second];
		Cxif_key& sk = structures_key.set_key(structure_i);
		sk.set_value_string(vi_sd_long_name, sd.long_name);
		sk.set_value_string(vi_sd_short_name, sd.short_name);
		sk.set_value_int(vi_sd_cx, sd.cx);
		sk.set_value_int(vi_sd_cy, sd.cy);
		sk.set_value_int(vi_sd_flags, sd.flags);
		sk.set_value_int(vi_sd_blocked, sd.blocked);
		if (sd.ground)
			sk.set_value_int(vi_sd_ground, sd.ground);
		if (sd.power_in)
			sk.set_value_int(vi_sd_power_in, sd.power_in);
		if (sd.power_out)
			sk.set_value_int(vi_sd_power_out, sd.power_out);
		structure_i++;
	}
	return structures_key.vdata().export(xcc_dirs::get_data_dir() + structures_xif_fname);
}

int xcc_structures::load_images(t_theater_id theater, bool load_icons)
{
	static t_theater_id loaded_theater = static_cast<t_theater_id>(-1);
	int error = 0;
	if (theater == loaded_theater)
		return 0;
	Cmix_file& conquer_mix = Cxcc_mixs::get_conquer_mix();
	Cmix_file& theater_mix = Cxcc_mixs::get_theater_mix(theater);
	const string ext = "." + Cxcc_mixs::get_theater_fname(theater).substr(0, 3);
	for (int i = 0; i < 256; i++)
	{
		t_structure_data_entry& sd = structure_data[i];
		if (~sd.flags & sd_flags_in_use)
			continue;
		Cshp_file f;
		/*
		sd.flags &= ~sd_flags_bib;
		if (~sd.flags & sd_flags_civilian && sd.cx > 1 && strcmp(sd.short_name, "sam"))
			sd.flags |= sd_flags_bib;
		*/
		// images
		if (sd.flags & sd_flags_theater_specific)
		{
			if (~sd.flags >> theater & sd_flags_desert)
				continue;
			f.open(sd.short_name + ext, theater_mix);
		}
		else
			f.open(sd.short_name + ".shp", conquer_mix);
		if (!f.is_open())
		{
			error = 1;
			continue;
		}
		if (shp_images::load_shp(f, sd.images))
			error = 1;
		f.close();
		/*
		shp_images::get_shp(sd.images, 0, sd.cx, sd.cy);
		sd.cx /= 24;
		sd.cy /= 24;
		*/
		if (load_icons && sd.flags & sd_flags_icon)
		{
			// icon
			f.open(sd.short_name + "icon.shp", conquer_mix);
			if (!f.is_open())
			{
				error = 1;
				continue;
			}
			if (shp_images::load_shp(f, sd.icon))
				error = 1;
			f.close();
		}
		if (sd.flags & sd_flags_images2)
		{
			// images2 (weapons factory)
			f.open(sd.short_name + "2.shp", conquer_mix);
			if (!f.is_open())
			{
				error = 1;
				continue;
			}
			if (shp_images::load_shp(f, sd.images2))
				error = 1;
			f.close();
		}
	}
	if (!error)
		loaded_theater = theater;
	return error;
}

void xcc_structures::destroy()
{
	for (int i = 0; i < 256; i++)
	{
		t_structure_data_entry& sd = structure_data[i];
	}
}

int xcc_structures::get_id(const string& s)
{
	for (int i = 0; i < 256; i++)
	{
		t_structure_data_entry& sd = structure_data[i];
		if (sd.flags & sd_flags_in_use && sd.short_name == s)
			return i;
	}
	return -1;
}