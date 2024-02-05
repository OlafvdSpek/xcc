/*
    XCC Utilities and Library
    Copyright (C) 2001  Olaf van der Spek  <olafvdspek@gmail.com>

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
#include "xcc_mod.h"

#include <fstream>
#include <strstream>
#include "aud_file_write.h"
#include "csf_file.h"
#include "jpeg_file.h"
#include "html.h"
#include "map_ts_encoder.h"
#include "multi_line.h"
#include "mix_file.h"
#include "mix_file_write.h"
#include "neat_ini_reader.h"
#include "ogg_file.h"
#include "pcx_file.h"
#include "shp_ts_file.h"
#include "shp_ts_file_write.h"
#include "string_conversion.h"
#include "vxl_file.h"
#include "web_tools.h"
#include "win_handle.h"
#include "xcc_dirs.h"
#include "xcc_log.h"
#include "xse.h"
#include "xste.h"

#include "cc_file.h"

const char* Cxcc_mod::ct_name[] = {"cameo", "hva", "ini", "map", "mix", "screen", "shp", "sound", "speech", "string table", "theme", "video", "vxl", "launcher", "manual", "interface", "tmp", "side 1", "side 2", "side 3", "unknown"};
static const int mf_version = 2;

Cxcc_mod::Cxcc_mod()
{
	m_options.name = "Anonymous";
	m_options.link = "http://";
	m_options.mod_name = "XCC Mod";
	m_options.game = game_ra2;
	m_options.csf_diff_compression = true;
	m_options.ini_diff_compression = true;
	m_options.shp_compression = true;
	m_options.vxl_compression = true;
	m_options.custom_button_text = false;
	m_options.exit_button = true;
	m_options.manual_button = true;
	m_options.site_button = true;
	m_options.update_button = true;
	m_options.xhp_button = true;
	m_options.mod_version = "1.00";
	m_options.mod_ucf = "http://";
	m_options.deactivate = 2;
	m_options.mf_version = 0;
	m_options.mod_mfs = "98";

	m_mode_map[-1] = "Base";
	m_module_map[-1] = "Base";
}

Cxcc_mod::t_category_file_list Cxcc_mod::category_file_list(t_category_type category) const
{
	t_file_list::const_iterator i = m_file_list.find(category);
	return i != m_file_list.end() ? i->second : t_category_file_list();
}

void Cxcc_mod::clear()
{
	m_file_list.clear();
}

bool Cxcc_mod::contains(t_category_type category) const
{
	t_file_list::const_iterator i = m_file_list.find(category);
	return i != m_file_list.end() && i->second.size();
}

bool Cxcc_mod::contains(t_category_type category, string fname, bool strip_path) const
{
	if (strip_path)
	{
		t_file_list::const_iterator i = m_file_list.find(category);
		if (i != m_file_list.end())
		{
			for (t_category_file_list::const_iterator j = i->second.begin(); j != i->second.end(); j++)
			{
				if (Cfname(j->first).get_fname() == fname)
					return true;
			}
		}
		return false;
	}
	else
	{
		t_file_list::const_iterator i = m_file_list.find(category);
		return i != m_file_list.end() && i->second.find(fname) != i->second.end();
	}
}

Cxcc_mod::t_file_properties Cxcc_mod::file_properties(t_category_type category, string fname) const
{
	return m_file_list.find(category)->second.find(fname)->second;
}

void Cxcc_mod::file_properties(t_category_type category, string fname, Cxcc_mod::t_file_properties v)
{
	m_file_list.find(category)->second.find(fname)->second = v;
}

int Cxcc_mod::insert(t_category_type category, string fname)
{
	m_file_list[category][fname];
	return 0;
}

void Cxcc_mod::remove(t_category_type category, string fname)
{
	m_file_list[category].erase(fname);
}

static void delete_files(string fname)
{
	WIN32_FIND_DATA finddata;
	HANDLE findhandle = FindFirstFile(fname.c_str(), &finddata);
	if (findhandle != INVALID_HANDLE_VALUE)
	{
		do
		{
			delete_file(Cfname(fname).get_path() + finddata.cFileName);
		}
		while (FindNextFile(findhandle, &finddata));
		FindClose(findhandle);
	}
}

enum
{
	vi_cx,
	vi_cy,
	vi_c_frames,
	vi_fname,
	vi_ft,
	vi_fdata,
	vi_encoding,
	vi_name,
	vi_mail,
	vi_link_title,
	vi_link,
	vi_game,
	vi_mod_name,
	vi_csf_diff_compression,
	vi_ini_diff_compression,
	vi_custom_button_text,
	vi_exit_button,
	vi_manual_button,
	vi_site_button,
	vi_update_button,
	vi_xhp_button,
	vi_mod_version,
	vi_mod_ucf,
	vi_confirm_deactivate,
	vi_mf_version,
	vi_shp_compression,
	vi_vxl_compression,
	vi_cb_d,
	vi_mode,
	vi_module,
	vi_mod_mfs,
	ki_modes = 0x100,
	ki_modules
};

enum t_encoding
{
	enc_none,
	enc_diff,
	enc_jpeg,
	enc_mng,
	enc_mpeg,
	enc_ogg,
	enc_png,
	enc_shp,
	enc_vxl
};

int Cxcc_mod::load(const Cxif_key& key, string dir)
{
	int error = 0;
	m_options.name = key.get_value_string(vi_name);
	m_options.mail = key.get_value_string(vi_mail);
	m_options.link_title = key.get_value_string(vi_link_title);
	m_options.link = key.get_value_string(vi_link);
	m_options.mod_name = key.get_value_string(vi_mod_name);
	m_options.game = static_cast<t_game>(key.get_value_int(vi_game));
	for (t_xif_value_map::const_iterator value = key.m_values.begin(); value != key.m_values.end(); value++)
	{
		switch (value->first)
		{
		case vi_csf_diff_compression:
			m_options.csf_diff_compression = value->second.get_int();
			break;
		case vi_ini_diff_compression:
			m_options.ini_diff_compression = value->second.get_int();
			break;
		case vi_shp_compression:
			m_options.shp_compression = value->second.get_int();
			break;
		case vi_vxl_compression:
			m_options.vxl_compression = value->second.get_int();
			break;
		case vi_custom_button_text:
			m_options.custom_button_text = value->second.get_int();
			break;
		case vi_exit_button:
			m_options.exit_button = value->second.get_int();
			break;
		case vi_manual_button:
			m_options.manual_button = value->second.get_int();
			break;
		case vi_site_button:
			m_options.site_button = value->second.get_int();
			break;
		case vi_update_button:
			m_options.update_button = value->second.get_int();
			break;
		case vi_xhp_button:
			m_options.xhp_button = value->second.get_int();
			break;
		case vi_mod_version:
			m_options.mod_version = value->second.get_string();
			break;
		case vi_mod_ucf:
			m_options.mod_ucf = value->second.get_string();
			break;
		case vi_confirm_deactivate:
			m_options.deactivate = value->second.get_int();
			break;
		case vi_mf_version:
			m_options.mf_version = value->second.get_int();
			break;
		case vi_mod_mfs:
			m_options.mod_mfs = value->second.get_string();
			break;
			/*
		case vi_@:
			m_options.@ = value->second.get_int();
			break;
			*/
		}
	}
	{
		m_mode_map.clear();
		m_mode_map[-1] = "Base";
		const Cxif_key& modes_key = key.get_key(ki_modes);
		for (t_xif_value_map::const_iterator i = modes_key.m_values.begin(); i != modes_key.m_values.end(); i++)
			m_mode_map[i->first] = i->second.get_string();
	}
	{
		m_module_map.clear();
		m_module_map[-1] = "Base";
		const Cxif_key& modules_key = key.get_key(ki_modules);
		for (t_xif_value_map::const_iterator i = modules_key.m_values.begin(); i != modules_key.m_values.end(); i++)
			m_module_map[i->first] = i->second.get_string();
	}
	for (t_xif_key_map::const_iterator category = key.m_keys.begin(); category != key.m_keys.end(); category++)
	{
		t_category_file_list& list = m_file_list[static_cast<t_category_type>(category->first)];
		for (t_xif_key_map::const_iterator i = category->second.m_keys.begin(); i != category->second.m_keys.end(); i++)
		{
			if (error)
				break;
			if (dir.size() && i->second.exists_value(vi_fdata))
			{
				const Cxif_value& fdata = i->second.get_value(vi_fdata);
				Cfname fname = dir + ct_name[category->first] + '\\' + i->second.get_value_string(vi_fname);
				if (!fname.exists())
				{
					create_dir(dir);
					create_dir(fname.get_path());
					error = file32_write(fname, fdata.get_data(), fdata.get_size());
				}
			}
			t_file_properties properties;
			properties.mode = i->second.get_value_int(vi_mode, -1);
			properties.module = i->second.get_value_int(vi_module, -1);
			list[i->second.get_value_string(vi_fname)] = properties;
		}
	}
	return error;
}

Cxcc_mod::t_options Cxcc_mod::options() const
{
	return m_options;
}

void Cxcc_mod::options(t_options options)
{
	m_options = options;
}

Cxif_key Cxcc_mod::save(bool save, int module) const
{
	assert(module >= -1 && module < 100);
	Cxif_key key;
	Cmix_file language_mix, main_mix;
	Cmix_file local_mix;
	if (save)
	{
		const t_game game = m_options.game;
		const string dir = xcc_dirs::get_dir(game);
		language_mix.open(xcc_dirs::get_language_mix(game));
		if (!main_mix.open(xcc_dirs::get_main_mix(game)))
			local_mix.open(xcc_dirs::get_local_mix(game), main_mix);
	}
	for (int category = 0; category < ct_unknown; category++)
	{
		if (!contains(static_cast<t_category_type>(category)))
			continue;
		Cxif_key& k = key.open_key_edit(category);
		t_category_file_list list = category_file_list(static_cast<t_category_type>(category));
		int id = 0;
		for (t_category_file_list::const_iterator i = list.begin(); i != list.end(); i++)
		{
			if (save)
			{
				if (i->second.module != module)
					continue;
				Ccc_file f(true);
				if (!f.open(i->first))
				{
					t_file_type ft = f.get_file_type();
					Cxif_key& l = k.open_key_edit(id++);
					l.set_value_string(vi_fname, Cfname(i->first).get_fname());
					l.set_value_int(vi_ft, ft);
					if (i->second.mode != -1)
						l.set_value_int(vi_mode, i->second.mode);
					/*
					if (i->second.module != -1)
						l.set_value_int(vi_module, i->second.module);
					*/
					switch (category)
					{
					case ct_ini:
						l.set_value_binary(vi_fdata, f.get_vdata());
						if (m_options.ini_diff_compression && local_mix.is_open())
						{
							Ccc_file g(true);
							string fname = Cfname(i->first).get_fname();
							if (!g.open(fname, local_mix))
							{
								Cneat_ini_reader ir1, ir2;
								ir1.process(f.get_data(), f.get_size());
								ir2.process(g.get_data(), g.get_size());
								g.close();
								const Cneat_ini_reader::t_section_list& sl1 = ir1.get_section_list();
								const Cneat_ini_reader::t_section_list& sl2 = ir2.get_section_list();
								const Cneat_ini_reader::t_section_map& sm1 = ir1.get_section_map();
								const Cneat_ini_reader::t_section_map& sm2 = ir2.get_section_map();
								Cneat_ini_reader::t_section_list::const_iterator i;
								for (i = sl1.begin(); i != sl1.end(); i++)
								{
									string section_name = (*i)->first;
									Cneat_ini_reader::t_section_map::const_iterator j = sm2.find(section_name);
									ir1.sub_section(section_name, j == sm2.end() ? Cneat_key_list() : j->second);
								}
								for (i = sl2.begin(); i != sl2.end(); i++)
								{
									string section_name = (*i)->first;
									if (sm1.find(section_name) == sm1.end())
										ir1.sub_section(section_name, (*i)->second);
								}
								strstream s;
								ir1.write(s);
								// ir1.write("c:/temp/" + fname);
								l.set_value_binary(vi_fdata, Cvirtual_binary(s.str(), s.pcount()));
								l.set_value_int(vi_encoding, enc_diff);
							}
						}
						break;
					case ct_st:
						l.set_value_binary(vi_fdata, f.get_vdata());
						if (m_options.csf_diff_compression && language_mix.is_open())
						{
							Ccsf_file e, g, h;
							string fname = Cfname(i->first).get_fname();
							if (!g.open(fname, language_mix))
							{
								Ccsf_file h;
								h.load(f);
								const Ccsf_file::t_map& map = h.get_map();
								for (Ccsf_file::t_map::const_iterator i = map.begin(); i != map.end(); i++)
								{
									if (!g.has_name(i->first) || g.get_value(i->first) != i->second.value)
										e.set_value(i->first, i->second.value, i->second.extra_value);
								}
								g.close();
								l.set_value_binary(vi_fdata, e.write());
								l.set_value_int(vi_encoding, enc_diff);
							}
						}
						break;
					default:
						if (ft == ft_shp_ts && m_options.shp_compression && Cfname(i->first).get_fname() != "mouse.sha" && Cfname(i->first).get_fname() != "mouse.shp")
						{
							Cshp_ts_file g;
							g.load(f);
							Cvirtual_binary d;
							d.size(shp_encode4(g, d.write_start(f.get_size() << 1)));
							if (d.size())
							{
								// xcc_log::write_line(Cfname(*i).get_fname() + ": " + n(d.size()) + '/' + n(f.get_size()));
								l.set_value_binary(vi_fdata, d);
								l.set_value_int(vi_encoding, enc_shp);
								l.set_value_int(vi_cb_d, shp_decode4_size(d.data()));
								// assert(l.get_value_int(vi_cb_d) == shp_decode4(d.data(), 0).size());
								// shp_decode4(d.data(), 0).save("c:/temp/shp_decode4.shp");
							}
							else
								l.set_value_binary(vi_fdata, f.get_vdata());
						}
						else if (ft == ft_vxl && m_options.vxl_compression)
						{
							Cvxl_file g;
							g.load(f);
							Cvirtual_binary d;
							d.size(vxl_encode4(g, d.write_start(f.get_size() << 1)));
							l.set_value_binary(vi_fdata, d);
							l.set_value_int(vi_encoding, enc_vxl);
							l.set_value_int(vi_cb_d, vxl_decode4(d.data(), 0).size());
							// assert(l.get_value_int(vi_cb_d) == vxl_decode4(d.data(), 0).size());
						}
						else if (ft == ft_bink || ft == ft_jpeg || ft == ft_ogg || ft == ft_png)
							l.set_value_binary(vi_fdata, f.get_vdata(), true);
						else
							l.set_value_binary(vi_fdata, f.get_vdata());
					}
					f.close();
				}
			}
			else
			{
				Cxif_key& l = k.open_key_edit(id++);
				l.set_value_string(vi_fname, i->first);
				if (i->second.mode != -1)
					l.set_value_int(vi_mode, i->second.mode);
				if (i->second.module != -1)
					l.set_value_int(vi_module, i->second.module);
			}
		}
	}
	if (save)
	{
		if (local_mix.is_open())
			local_mix.close();
		if (main_mix.is_open())
			main_mix.close();
		if (language_mix.is_open())
			language_mix.close();
	}
	if (module == -1)
	{
		key.set_value_string(vi_name, m_options.name);
		key.set_value_string(vi_mail, m_options.mail);
		key.set_value_string(vi_link_title, m_options.link_title);
		key.set_value_string(vi_link, m_options.link);
		key.set_value_string(vi_mod_name, m_options.mod_name);
		key.set_value_int(vi_game, m_options.game);
		key.set_value_int(vi_csf_diff_compression, m_options.csf_diff_compression);
		key.set_value_int(vi_ini_diff_compression, m_options.ini_diff_compression);
		key.set_value_int(vi_shp_compression, m_options.shp_compression);
		key.set_value_int(vi_vxl_compression, m_options.vxl_compression);
		key.set_value_int(vi_custom_button_text, m_options.custom_button_text);
		key.set_value_int(vi_exit_button, m_options.exit_button);
		key.set_value_int(vi_manual_button, m_options.manual_button);
		key.set_value_int(vi_site_button, m_options.site_button);
		key.set_value_int(vi_update_button, m_options.update_button);
		key.set_value_int(vi_xhp_button, m_options.xhp_button);
		key.set_value_string(vi_mod_version, m_options.mod_version);
		key.set_value_string(vi_mod_ucf, m_options.mod_ucf);
		key.set_value_int(vi_confirm_deactivate, m_options.deactivate);
		key.set_value_int(vi_mf_version, mf_version);
		key.set_value_string(vi_mod_mfs, m_options.mod_mfs);
		{
			Cxif_key& modes_key = key.open_key_write(ki_modes);
			for (t_mode_map::const_iterator i = mode_map().begin(); i != mode_map().end(); i++)
			{
				if (i->first != -1)
					modes_key.set_value_string(i->first, i->second);
			}
		}
		if (!save)
		{
			Cxif_key& modules_key = key.open_key_write(ki_modules);
			for (t_module_map::const_iterator i = module_map().begin(); i != module_map().end(); i++)
			{
				if (i->first != -1)
					modules_key.set_value_string(i->first, i->second);
			}
		}
	}
	return key;
}

int Cxcc_mod::save_modules(Cfname fname)
{
	int error = 0;
	string base_name = fname.get_ftitle();
	fname.set_ext(".xmlf");
	for (t_module_map::const_iterator i = module_map().begin(); i != module_map().end(); i++)
	{
		if (i->first == -1)
			continue;
		fname.set_title(base_name + ' ' + nwzl(2, i->first));
		error = save(true, i->first).vdata().save(fname);
		if (error)
			break;
	}
	return error;
}

__int64 get_last_write_time(string fname)
{
	FILETIME r;
	memset(&r, 0, sizeof(FILETIME));
	Cfile32 f;
	if (!f.open_read(fname))
	{
		r = f.get_last_write_time();
		f.close();
	}
	return *reinterpret_cast<__int64*>(&r);
}

int Cxcc_mod::activate(Cxif_key key, bool external_data, int mode)
{
	const string mod_name = key.get_value_string(vi_mod_name);
	const t_game game = static_cast<t_game>(key.get_value_int(vi_game));
	const string dir = xcc_dirs::get_dir(game);
	const string temp_dir = get_temp_path() + mod_name + " Cache/";
	Cmix_file_write expand_mix(game);
	Cmix_file_write ecache_mix(game);
	Cmix_file main_mix;
	Cmix_file local_mix;
	Cmix_file language_mix;
	if (!xcc_dirs::is_available(game))
		return 2;
	if (external_data)
		CreateDirectory(temp_dir.c_str(), NULL);
	int error = main_mix.open(xcc_dirs::get_main_mix(game));
	if (error)
		xcc_log::write_line("Unable to open " + xcc_dirs::get_main_mix(game));
	else
	{
		if (game != game_ts)
			error = language_mix.open(xcc_dirs::get_language_mix(game));
		if (error)
			xcc_log::write_line("Unable to open " + xcc_dirs::get_language_mix(game));
		else
		{
			error = local_mix.open(xcc_dirs::get_local_mix(game), main_mix);
			if (error)
				xcc_log::write_line("Unable to open " + xcc_dirs::get_local_mix(game));
			else
			{
				{
					for (t_module_list::const_iterator i = m_module_list.begin(); i != m_module_list.end(); i++)
					{
						Cvirtual_binary s;
						Cxif_key k;
						if (s.load(*i) || k.load_key(s))
							continue;
						for (t_xif_key_map::const_iterator category = k.m_keys.begin(); category != k.m_keys.end(); category++)
						{
							t_category_file_list& list = m_file_list[static_cast<t_category_type>(category->first)];
							for (t_xif_key_map::const_iterator i = category->second.m_keys.begin(); i != category->second.m_keys.end(); i++)
							{
								key.open_key_edit(category->first).open_key_write() = i->second;
								list[i->second.get_value_string(vi_fname)];
							}
						}
					}
				}
				for (t_xif_key_map::const_iterator category = key.m_keys.begin(); category != key.m_keys.end(); category++)
				{
					if (error)
						break;
					if (category->second.m_keys.empty())
						continue;
					xcc_log::write_line(ct_name[category->first]);
					Cmix_file_write side_mix(game);
					Cxse xse;
					switch (category->first)
					{
					case ct_launcher:
					case ct_manual:
						continue;
					case ct_side_1:
					case ct_side_2:
					case ct_side_3:
						{
							side_mix.clear();
							Cmix_file h;
							bool use_h = category->first != ct_side_3 || game != game_ra2_yr;
							if (use_h)
								error = h.open(xcc_dirs::get_main_mix(game_ra2));
							if (!error)
							{
								Cmix_file f;
								if (use_h)
									error = f.open("sidec0" + n(category->first - ct_side_1 + 1) + ".mix", h);
								else
									error = f.open("sidec02md.mix", main_mix);
								if (!error)
								{
									for (int i = 0; i < f.get_c_files(); i++)
									{
										int id = f.get_id(i);
										Ccc_file g(true);
										error = g.open(id, f);
										if (error)
											break;
										side_mix.add_file(id, g.get_vdata());
										g.close();
									}
									f.close();
								}
								if (use_h)
									h.close();
							}
						}
						break;
					case ct_sound:
						if (game != game_ts && xse.open())
						{
							error = 1;
							continue;
						}
						break;
					}
					for (t_xif_key_map::const_iterator i = category->second.m_keys.begin(); i != category->second.m_keys.end(); i++)
					{
						if (error)
							break;
						const Cfname external_fname = i->second.get_value_string(vi_fname);
						Cfname fname = external_fname.get_fname();
						xcc_log::write_line(fname);
						int file_mode = i->second.get_value_int(vi_mode, -1);
						if (file_mode != -1 && file_mode != mode)
							continue;
						t_file_type ft;
						Cvirtual_binary data;
						t_encoding encoding;
						__int64 last_write_time;
						if (external_data)
						{
							error = data.load(external_fname);
							if (!error)
							{
								Ccc_file f(true);
								f.load(data);
								ft = f.get_file_type();
							}
							encoding = enc_none;
							last_write_time = get_last_write_time(external_fname);
						}
						else
						{
							ft = static_cast<t_file_type>(i->second.get_value_int(vi_ft));
							data = i->second.get_value(vi_fdata).get_vdata();
							encoding = static_cast<t_encoding>(i->second.get_value_int(vi_encoding, enc_none));
							last_write_time = 0;
						}
						Cvirtual_file h;
						bool ignore = false;
						switch (ft)
						{
						case ft_jpeg:
							fname.set_ext(".pcx");
							if (get_last_write_time(temp_dir + fname) < last_write_time || h.load(temp_dir + fname))
							{
								Cjpeg_file g;
								g.load(data);
								Cvirtual_image image;
								if (!g.decode(image))
								{
									image.save_as_pcx(h);
									if (external_data)
									{
										string temp_fname = temp_dir + fname;
										h.save(temp_fname);
									}
									data = h.read();
								}
							}
							else
								data = h.read();
							break;
						case ft_ogg:
							fname.set_ext(game == game_ts ? ".aud" : ".wav");
							if (Cfname(dir + fname).exists())
								ignore = true;
							else if (get_last_write_time(temp_dir + fname) < last_write_time || h.load(temp_dir + fname))
							{
								Cogg_file g;
								g.load(data);
								Cvirtual_audio audio;
								if (!g.decode(audio))
								{
									if (game == game_ts)
									{
										if (audio.c_channels() != 1)
											error = 1;
										else
											h = audio.save_as_aud();
									}
									else
										h = audio.save_as_wav_ima_adpcm(); // audio.save_as_wav_pcm();
									if (!error)
									{
										if (external_data)
										{
											string temp_fname = temp_dir + fname;
											h.save(temp_fname);
										}
										data = h.read();
									}
								}
							}
							else
								data = h.read();
							break;
						case ft_pcx:
							if ((category->first == ct_cameo || (category->first == ct_screen && game == game_ra2)))
							{
								Cpcx_file g;
								g.load(data);
								if (g.cb_pixel() == 1)
								{
									fname.set_ext(".shp");
									Cvirtual_image image = g.vimage();
									h = shp_ts_file_write(image.image(), image.cx(), image.cy(), 1, true);
									data = h.read();
								}
							}
							break;
						case ft_shp_ts:
							if (encoding == enc_shp)
								data = shp_decode4(data.data(), i->second.get_value_int(vi_cb_d, 0));
							break;
						case ft_vxl:
							if (encoding == enc_vxl)
								data = vxl_decode4(data.data(), i->second.get_value_int(vi_cb_d, 0));
							break;
						case ft_xif:
							if (category->first == ct_map)
							{
								Cxif_key k;
								int error = k.load_key(data.data(), data.size());
								if (!error)
								{
									if (Cmap_ts_encoder::wrong_version(k))
										error = 1;
									else
									{
										fname.set_ext(".map");
										strstream s;
										Cmap_ts_encoder::write_map(s, k, Cvirtual_binary());
										data = Cvirtual_binary(s.str(), s.pcount());
									}
								}
							}
							break;
						}
						if (!error && !ignore)
						{
							switch (category->first)
							{
							case ct_cameo:
							case ct_shp:
							case ct_speech:
							case ct_tmp:
								ecache_mix.add_file(fname, data);
								break;
							case ct_ini:
								if (encoding == enc_diff)
								{
									Ccc_file g(true);
									if (g.open(fname, local_mix))
										error = 1;
									else
									{
										Cneat_ini_reader ir;
										ir.process(g.get_data(), g.get_size());
										ir.process(data.data(), data.size());
										g.close();
										Cvirtual_binary d(NULL, g.get_size() + data.size());
										strstream s(reinterpret_cast<char*>(d.data_edit()), d.size());
										ir.write(s);
										error = s.pcount() == d.size();
										d.size(s.pcount());
										data = d;
									}
								}
								if (!error)
								{
									if (fname.get_fname() == "missionsmd.pkt")
										error = data.save(dir + fname);
									else
										expand_mix.add_file(fname, data);
								}
								break;
							case ct_screen:
								if (fname.get_fname() == "glsmd.pal" || fname.get_fname() == "glslmd.shp")
									error = data.save(dir + fname);
								else
									expand_mix.add_file(fname, data);
								break;
							case ct_side_1:
							case ct_side_2:
							case ct_side_3:
								side_mix.add_file(fname, data);
								break;
							case ct_sound:
								if (game == game_ts)
									ecache_mix.add_file(fname, data);
								else
								{
									Cwav_file f;
									f.load(data);
									xse.insert(fname.get_ftitle(), f);
								}
								break;
							case ct_st:
								if (encoding == enc_diff)
								{
									Ccc_file g(true);
									if (!language_mix.is_open() || g.open(fname, language_mix))
										error = 1;
									else
									{
										Ccsf_file e, h;
										e.load(g);
										g.close();
										h.load(data);
										const Ccsf_file::t_map& map = h.get_map();
										for (Ccsf_file::t_map::const_iterator i = map.begin(); i != map.end(); i++)
											e.set_value(i->first, i->second.value, i->second.extra_value);
										error = e.write().save(dir + fname);
									}
								}
								else if (ft == ft_text)
								{
									Ccc_file g(true);
									if (!language_mix.is_open() || g.open(xcc_dirs::get_csf_fname(game), language_mix))
										error = 1;
									else
									{
										Ccsf_file e;
										e.load(g);
										g.close();
										Cmulti_line p = string(reinterpret_cast<const char*>(data.data()), data.size());
										while (!p.empty())
										{
											string name, value;
											split_key(p.get_next_line('\n'), name, value);
											if (!name.empty() || !value.empty())
												e.set_value(name, Ccsf_file::convert2wstring(value), "");
										}
										error = e.write().save(dir + xcc_dirs::get_csf_fname(game));
									}
								}
								else
									error = data.save(dir + fname);
								break;
							case ct_theme:
							case ct_video:
								error = data.save(dir + fname);
								break;
							default:
								expand_mix.add_file(fname, data);
							}
						}
					}
					switch (category->first)
					{
					case ct_side_1:
					case ct_side_2:
					case ct_side_3:
						if (category->first == ct_side_3 && game == game_ra2_yr)
							expand_mix.add_file("sidec02md.mix", side_mix.write());
						else
							expand_mix.add_file("sidec0" + n(category->first - ct_side_1 + 1) + ".mix", side_mix.write());
						break;
					case ct_sound:
						if (game != game_ts)
						{
							if (!error)
								xse.write_idx_file();
							xse.close();
						}
						break;
					}
				}
				local_mix.close();
			}
			if (language_mix.is_open())
				language_mix.close();
		}
		main_mix.close();
	}
	if (!error)
	{
		if (game == game_ts)
			expand_mix.add_file(xcc_dirs::get_ecache_mix(game, false, 98), ecache_mix.write());
		else
			error = ecache_mix.write().save(xcc_dirs::get_ecache_mix(game, true, m_options.mod_mfs));
		if (!error)
			error = expand_mix.write().save(xcc_dirs::get_expand_mix(game, m_options.mod_mfs));
	}
	return error;
}

int Cxcc_mod::activate()
{
	return activate(save(false, -1), true, 0);
}

int Cxcc_mod::deactivate(bool remove_themes) const
{
	const t_game game = m_options.game;
	string dir = xcc_dirs::get_dir(game);
	for (t_file_list::const_iterator category = m_file_list.begin(); category != m_file_list.end(); category++)
	{
		const t_category_file_list& list = category->second;
		if (category->first == ct_theme && !remove_themes)
			continue;
		for (t_category_file_list::const_iterator i = list.begin(); i != list.end(); i++)
		{
			Cfname fname = Cfname(i->first).get_fname();
			if (category->first == ct_theme)
				fname.set_ext(game == game_ts ? ".aud" : ".wav");
			switch (category->first)
			{
			// case ct_map:
			case ct_st:
			case ct_theme:
			case ct_video:
				delete_file(dir + fname);
				break;
			}
		}
	}
	delete_file(dir + "audio.bag");
	delete_file(dir + "audio.idx");
	delete_file(dir + "glsmd.pal");
	delete_file(dir + "glslmd.shp");
	delete_file(dir + xcc_dirs::get_csf_fname(game));
	delete_file(xcc_dirs::get_ecache_mix(game, true, m_options.mod_mfs));
	delete_file(xcc_dirs::get_expand_mix(game, m_options.mod_mfs));
	return 0;
}

int Cxcc_mod::launch_game(bool wait) const
{
	return create_process(xcc_dirs::get_exe(options().game), "", wait);
}

void Cxcc_mod::clear_game_dir() const
{
	string dir = xcc_dirs::get_dir(m_options.game);
	delete_file(dir + "ai.ini");
	delete_file(dir + "aimd.ini");
	delete_file(dir + "art.ini");
	delete_file(dir + "artmd.ini");
	delete_file(dir + "audio.bag");
	delete_file(dir + "audio.idx");
	delete_files(dir + "ecache*.mix");
	delete_files(dir + "elocal*.mix");
	for (int i = 2; i < 100; i++)
	{
		delete_files(dir + "expand" + nwzl(2, i) + ".mix");
		delete_files(dir + "expandmd" + nwzl(2, i) + ".mix");
	}
	delete_file(dir + "missionsmd.pkt");
	delete_file(dir + "ra2.csf");
	delete_file(dir + "ra2md.csf");
	delete_file(dir + "rules.ini");
	delete_file(dir + "rulesmd.ini");
	delete_file(dir + "sound.ini");
	delete_file(dir + "soundmd.ini");
	delete_file(dir + "ui.ini");
	delete_file(dir + "uimd.ini");
}

int Cxcc_mod::load_launcher_audio(const Cxif_key& key, string fname, Cvirtual_binary& audio)
{
	if (!key.exists_key(ct_launcher))
		return 1;
	const Cxif_key& category = key.open_key_read(ct_launcher);
	for (t_xif_key_map::const_iterator i = category.m_keys.begin(); i != category.m_keys.end(); i++)
	{
		if (i->second.get_value_string(vi_fname) != fname)
			continue;
		Cogg_file f;
		f.load(i->second.get_value(vi_fdata).get_vdata());
		if (!f.is_valid())
			break;
		audio = f.get_vdata();
		return 0;
	}
	return 1;
}

int Cxcc_mod::load_launcher_image(const Cxif_key& key, string fname, Cvirtual_image& image)
{
	if (!key.exists_key(ct_launcher))
		return 1;
	const Cxif_key& category = key.open_key_read(ct_launcher);
	for (t_xif_key_map::const_iterator i = category.m_keys.begin(); i != category.m_keys.end(); i++)
	{
		if (i->second.get_value_string(vi_fname) != fname)
			continue;
		Cjpeg_file f;
		f.load(i->second.get_value(vi_fdata).get_vdata());
		if (!f.is_valid() || f.decode(image))
			break;
		return 0;
	}
	return 1;
}

int Cxcc_mod::launch_manual(const Cxif_key& key, string dir, HWND hWnd)
{
	if (!key.exists_key(ct_manual))
		return 1;
	int error = 0;
	string index;
	const Cxif_key& category = key.open_key_read(ct_manual);
	for (t_xif_key_map::const_iterator i = category.m_keys.begin(); i != category.m_keys.end(); i++)
	{
		if (error)
			break;
		string fname = i->second.get_value_string(vi_fname);
		if (Cfname(fname).get_ftitle() == "index")
			index = fname;
		error = i->second.get_value(vi_fdata).get_vdata().save(dir + fname);
	}
	if (!error)
	{
		if (index.empty())
			dir.erase(dir.length() - 1);
		ShellExecute(hWnd, "open", (dir + index).c_str(), NULL, NULL, SW_SHOW);
	}
	return error;
}

void Cxcc_mod::report(string fname) const
{
	string page;
	const t_game game = m_options.game;
	t_file_type ft_audio = game == game_ts ? ft_aud : ft_wav;
	for (int category = 0; category < ct_unknown; category++)
	{
		if (!contains(static_cast<t_category_type>(category)))
			continue;
		page +=	tr(th(ct_name[category], "colspan=4"));
		t_category_file_list list = category_file_list(static_cast<t_category_type>(category));
		for (t_category_file_list::const_iterator i = list.begin(); i != list.end(); i++)
		{
			Cfname fname = Cfname(i->first).get_fname();
			string row = td(static_cast<string>(fname));
			Ccc_file f(false);
			if (f.open(i->first))
				row += td("not found", "colspan=3");
			else
			{
				t_file_type ft = f.get_file_type();
				row += td(ft_name[ft]) + td(n(f.get_size()), "align=right");
				switch (ft)
				{
				case ft_jpeg:
					ft = ft_pcx;
					break;
				case ft_ogg:
					ft = ft_audio;
					break;
				case ft_pcx:
					if ((category == ct_cameo || (category == ct_screen && game == game_ra2)))
						ft = ft_shp_ts;
					break;
				}
				string error = "&nbsp;";
				switch (category)
				{
				case ct_cameo:
				case ct_shp:
					if (ft != ft_shp_ts)
						error = "Wrong file type";
					break;
				case ct_hva:
					fname.set_ext(".vxl");
					if (ft != ft_hva)
						error = "Wrong file type";
					else if (!contains(ct_vxl, fname, true))
						error = "Missing VXL";
					break;
				case ct_sound:
				case ct_speech:
				case ct_theme:
					if (ft != ft_audio)
						error = "Wrong file type";
					break;
				case ct_tmp:
					if (ft != ft_tmp_ts)
						error = "Wrong file type";
					break;
				case ct_vxl:
					fname.set_ext(".hva");
					if (ft != ft_vxl)
						error = "Wrong file type";
					else if (!contains(ct_hva, fname, true))
						error = "Missing HVA";
					break;
				}
				row += td(error);
				f.close();
			}
			page += tr(row);
		}
	}
	page +=	tr(th("options", "colspan=4"))
		+ tr(td("name") + td(m_options.name, "colspan=3"))
		+ tr(td("mod_name") + td(m_options.mod_name, "colspan=3"))
		+ tr(td("mod_ucf") + td(m_options.mod_ucf, "colspan=3"))
		+ tr(td("mod_version") + td(m_options.mod_version, "colspan=3"))
		+ tr(td("game") + td(game_name[m_options.game], "colspan=3"))
		+ tr(td("csf_diff_compression") + td(btoa(m_options.csf_diff_compression), "colspan=3"))
		+ tr(td("ini_diff_compression") + td(btoa(m_options.ini_diff_compression), "colspan=3"))
		+ tr(td("shp_compression") + td(btoa(m_options.shp_compression), "colspan=3"))
		+ tr(td("vxl_compression") + td(btoa(m_options.vxl_compression), "colspan=3"));
	ofstream(fname.c_str()) << head_xcc(m_options.mod_name) + body(table(page, "border=1 width=100%"));
}

bool Cxcc_mod::future_version()
{
	return options().mf_version > mf_version;
}

void Cxcc_mod::load_modules(Cxif_key& key, Cfname fname)
{
	string base_name = fname.get_ftitle();
	fname.set_ext(".xmlf");
	for (int i = 0; i < 100; i++)
	{
		fname.set_title(base_name + ' ' + nwzl(2, i));
		if (fname.exists())
			m_module_list.push_back(fname);
	}
}

int Cxcc_mod::add_mode(string name)
{
	for (t_mode_map::const_iterator i = mode_map().begin(); i != mode_map().end(); i++)
	{
		if (i->second == name)
			return i->first;
	}
	int id = mode_map().empty() ? 0 : mode_map().rbegin()->first + 1;
	m_mode_map[id] = name;
	return id;
}

int Cxcc_mod::add_module(string name)
{
	for (t_module_map::const_iterator i = module_map().begin(); i != module_map().end(); i++)
	{
		if (i->second == name)
			return i->first;
	}
	int id = module_map().empty() ? 0 : module_map().rbegin()->first + 1;
	m_module_map[id] = name;
	return id;
}

string Cxcc_mod::get_mode(int id) const
{
	return mode_map().find(id)->second;
}

string Cxcc_mod::get_module(int id) const
{
	return module_map().find(id)->second;
}

void Cxcc_mod::compact()
{
	typedef set<int> t_int_set;

	t_int_set modes, modules;
	for (int category = 0; category < ct_unknown; category++)
	{
		t_category_file_list list = category_file_list(static_cast<t_category_type>(category));
		int id = 0;
		for (t_category_file_list::const_iterator i = list.begin(); i != list.end(); i++)
		{
			modes.insert(i->second.mode);
			modules.insert(i->second.module);
		}
	}
	{
		for (t_mode_map::iterator i = m_mode_map.begin(); i != m_mode_map.end(); )
		{
			if (i->first != -1 && modes.find(i->first) == modes.end())
				i = m_mode_map.erase(i);
			else
				i++;
		}
	}
	{
		for (t_module_map::iterator i = m_module_map.begin(); i != m_module_map.end(); )
		{
			if (i->first != -1 && modules.find(i->first) == modules.end())
				i = m_module_map.erase(i);
			else
				i++;
		}
	}
}