/*
    XCC Utilities and Library
    Copyright (C) 2000  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "stdafx.h"
#include "xcc_structures.h"

#include "mix_file.h"
#include "shp_file.h"
#include "shp_images.h"
#include "xcc_dirs.h"
#include "xcc_mixs.h"
#include "xif_key.h"

xcc_structures::t_structure_data_entry xcc_structures::structure_data[256];

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

int xcc_structures::load_data()
{
	Cxif_key structures_key;
	if (structures_key.load_key(Cvirtual_binary(xcc_dirs::get_data_dir() + structures_xif_fname)))
		return 1;
	int structure_i = 0;
	for (auto& i : structures_key.m_keys)
	{
		t_structure_data_entry& sd = structure_data[structure_i];
		Cxif_key& sk = i.second;
		sd.long_name = sk.get_value_string(vi_sd_long_name);
		sd.short_name = sk.get_value_string(vi_sd_short_name);
		sd.cx = sk.get_value_int(vi_sd_cx);
		sd.cy = sk.get_value_int(vi_sd_cy);
		sd.flags = sk.get_value_int(vi_sd_flags);
		sd.blocked = sk.get_value_int(vi_sd_blocked);
		sd.ground = 0;
		sd.power_in = 0;
		sd.power_out = 0;
		for (auto& i : sk.m_values)
		{
			switch (i.first)
			{
			case vi_sd_ground:
				sd.ground = i.second.get_int();
				break;
			case vi_sd_power_in:
				sd.power_in = i.second.get_int();
				break;
			case vi_sd_power_out:
				sd.power_out = i.second.get_int();
				break;
			}
		}
		structure_i++;
	}
	return 0;
}

int xcc_structures::save_data()
{
	map<string, t_structure_data_entry*> list;	
	for (auto& sd : structure_data)
	{
		if (sd.flags & sd_flags_in_use)
			list[sd.short_name] = &sd;
	}
	Cxif_key structures_key;
	int structure_i = 0;
	for (auto& i : list)
	{
		t_structure_data_entry& sd = *i.second;
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
	return structures_key.vdata().save(xcc_dirs::get_data_dir() + structures_xif_fname);
}

int xcc_structures::load_images(t_theater_id theater)
{
	static t_theater_id loaded_theater = static_cast<t_theater_id>(-1);
	if (theater == loaded_theater)
		return 0;
	for (auto& sd : structure_data)
	{
		if (~sd.flags & sd_flags_in_use)
			continue;
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
		}
		if (shp_images::load_shp(sd.short_name, sd.images))
			return 1;
		/*
		shp_images::get_shp(sd.images, 0, sd.cx, sd.cy);
		sd.cx /= 24;
		sd.cy /= 24;
		*/
		if (sd.flags & sd_flags_icon && shp_images::load_shp(sd.short_name + "icon", sd.icon))
			return 1;
		if (sd.flags & sd_flags_images2 && shp_images::load_shp(sd.short_name + "2", sd.images2))
			return 1;
	}
	loaded_theater = theater;
	return 0;
}

xcc_structures::t_structure_data_entry* xcc_structures::get_id(const string& s)
{
	for (auto& sd : structure_data)
	{
		if (sd.flags & sd_flags_in_use && iequals(sd.short_name, s))
			return &sd;
	}
	assert(false);
	return NULL;
}