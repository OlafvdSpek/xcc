// xcc_mod.h: interface for the Cxcc_mod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCC_MOD_H__C6F3F601_D0FC_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_XCC_MOD_H__C6F3F601_D0FC_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_structures.h"
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
		bool custom_button_text;
		bool exit_button;
		bool manual_button;
		bool site_button;
		bool update_button;
		bool xhp_button;
		bool confirm_deactivate;
		string mod_version;
		string mod_ucf;
	};

	enum t_category_type {ct_cameo, ct_hva, ct_ini, ct_map, ct_mix, ct_screen, ct_shp, ct_sound, ct_speech, ct_st, ct_theme, ct_video, ct_vxl, ct_launcher, ct_manual, ct_interface, ct_unknown};
	typedef set<string> t_category_file_list;

	t_category_file_list category_file_list(t_category_type category) const;
	void clear();
	void clear_game_dir() const;
	bool contains(t_category_type category) const;
	bool contains(t_category_type category, string fname, bool strip_path = false) const;
	int insert(t_category_type category, string fname);
	static int activate(const Cxif_key& key, bool external_data);
	int activate() const;
	int deactivate(bool remove_themes) const;
	int launch_game(bool wait) const;
	static int launch_manual(const Cxif_key& key, string dir, HWND hWnd);
	int load(const Cxif_key& key, string dir = "");
	static int load_banner(const Cxif_key& key, Cvirtual_image& image);
	t_options options() const;
	void options(t_options options);
	void remove(t_category_type category, string fname);
	void report(string fname) const;
	Cxif_key save(bool export) const;

	Cxcc_mod();
	~Cxcc_mod();

	static const char* ct_name[];
private:
	typedef map<t_category_type, t_category_file_list> t_file_list;
	t_file_list m_file_list;
	t_options m_options;
};

#endif // !defined(AFX_XCC_MOD_H__C6F3F601_D0FC_11D4_A95D_0050042229FC__INCLUDED_)
