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

#pragma once

#include "cc_structures.h"
#include "fname.h"
#include "virtual_audio.h"
#include "virtual_image.h"
#include "xif_key.h"

class Cxcc_mod  
{
public:
	struct t_options
	{
		string name;
		string mail;
		string link_title;
		string link;
		string mod_name;
		t_game game;
		bool csf_diff_compression;
		bool ini_diff_compression;
		bool shp_compression;
		bool vxl_compression;
		bool custom_button_text;
		bool exit_button;
		bool manual_button;
		bool site_button;
		bool update_button;
		bool xhp_button;
		int deactivate;
		string mod_version;
		string mod_mfs;
		string mod_ucf;
		int mf_version;
	};

	struct t_file_entry
	{
		t_file_entry()
		{
			mode = module = -1;
		}

		int mode;
		int module;
	};

	enum t_category_type {ct_cameo, ct_hva, ct_ini, ct_map, ct_mix, ct_screen, ct_shp, ct_sound, ct_speech, ct_st, ct_theme, ct_video, ct_vxl, ct_launcher, ct_manual, ct_interface, ct_tmp, ct_side_1, ct_side_2, ct_side_3, ct_unknown};
	typedef map<string, t_file_entry> t_category_file_list;
	typedef t_file_entry t_file_properties;
	typedef map<int, string> t_mode_map;
	typedef map<int, string> t_module_map;

	int add_mode(string name);
	int add_module(string name);
	void compact();
	string get_module(int id) const;
	string get_mode(int id) const;
	t_category_file_list category_file_list(t_category_type category) const;
	void clear();
	void clear_game_dir() const;
	bool contains(t_category_type category) const;
	bool contains(t_category_type category, string fname, bool strip_path = false) const;
	t_file_properties file_properties(t_category_type category, string fname) const;
	void file_properties(t_category_type category, string fname, t_file_properties v);
	bool future_version();
	int insert(t_category_type category, string fname);
	int activate(Cxif_key key, bool external_data, int mode);
	int activate();
	int deactivate(bool remove_themes) const;
	int launch_game(bool wait) const;
	static int launch_manual(const Cxif_key& key, string dir, HWND hWnd);
	int load(const Cxif_key& key, string dir = "");
	void load_modules(Cxif_key& key, Cfname fname);
	static int load_launcher_audio(const Cxif_key& key, string fname, Cvirtual_binary& audio);
	static int load_launcher_image(const Cxif_key& key, string fname, Cvirtual_image& image);
	t_options options() const;
	void options(t_options options);
	void remove(t_category_type category, string fname);
	void report(string fname) const;
	Cxif_key save(bool export, int module) const;
	int save_modules(Cfname fname);
	Cxcc_mod();

	const t_mode_map& mode_map() const
	{
		return m_mode_map;
	}

	const t_module_map& module_map() const
	{
		return m_module_map;
	}

	static const char* ct_name[];
private:
	typedef map<t_category_type, t_category_file_list> t_file_list;
	typedef list<string> t_module_list;

	t_file_list m_file_list;
	t_mode_map m_mode_map;
	t_module_map m_module_map;
	t_module_list m_module_list;
	t_options m_options;
};
