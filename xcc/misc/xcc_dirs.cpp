// xcc_dirs.cpp: implementation of the xcc_dirs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <windows.h>
#include "string_conversion.h"
#include "xcc_dirs.h"
#include "xcc_registry.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

bool g_enable_log = false;
bool xcc_dirs::m_use_external_files = true;
static string dune2_dir;
string xcc_dirs::td_primary_dir;
string xcc_dirs::td_secondary_dir;
string xcc_dirs::cd_dir;
string xcc_dirs::data_dir;
string xcc_dirs::ra_dir;
static string dune2000_dir;
string xcc_dirs::ts_dir;
static string ra2_dir;
static string rg_dir;
static string gr_dir;

bool xcc_dirs::enable_log()
{
	return g_enable_log;
}

string xcc_dirs::get_dune2_dir()
{
	return dune2_dir;
}

string xcc_dirs::get_dune2000_dir()
{
	return dune2000_dir;
}

string xcc_dirs::get_ra2_dir()
{
	return ra2_dir;
}

string xcc_dirs::get_dir(t_game game)
{
	switch (game)
	{
	case game_td:
		return td_primary_dir;
	case game_ra:
		return ra_dir;
	case game_ts:
		return ts_dir;
	case game_dune2:
		return dune2_dir;
	case game_dune2000:
		return dune2000_dir;
	case game_ra2:
	case game_ra2_yr:
		return ra2_dir;
	case game_rg:
		return rg_dir;
	case game_gr:
		return gr_dir;
	}
	assert(false);
	return "";
}

string xcc_dirs::get_exe(t_game game)
{
	switch (game)
	{
	case game_td:
		return td_primary_dir + "c&c95.exe";
	case game_ra:
		return ra_dir + "ra95.exe";
	case game_ts:
		return ts_dir + "sun.exe";
	case game_dune2:
		return dune2_dir + "dune2.exe";
	case game_dune2000:
		return dune2000_dir + "dune2000.exe";
	case game_ra2:
		return ra2_dir + "ra2.exe";
	case game_ra2_yr:
		return ra2_dir + "ra2md.exe";
	case game_gr:
		return gr_dir + "generals.exe";
	}
	assert(false);
	return "";
}

string xcc_dirs::get_audio_mix(t_game game)
{
	switch (game)
	{
	case game_ra2:
		return "audio.mix";
	case game_ra2_yr:
		return "audiomd.mix";
	}
	assert(false);
	return "";
}

string xcc_dirs::get_csf_fname(t_game game)
{
	switch (game)
	{
	case game_ra2:
		return "ra2.csf";
	case game_ra2_yr:
		return "ra2md.csf";
	case game_gr:
		return "data/english/generals.csf";
	case game_gr_zh:
		return "data/englishzh/generals.csf";
	}
	assert(false);
	return "";
}

static string get_suffix(t_game game)
{
	return game == game_ra2_yr ? "md" : "";
}

string xcc_dirs::get_ecache_mix(t_game game, bool dir, int i)
{
	return get_ecache_mix(game, dir, nwzl(2, i));
}

string xcc_dirs::get_ecache_mix(t_game game, bool dir, const string& s)
{
	string r = "ecache" + get_suffix(game) + s + ".mix";
	if (dir)
		r = get_dir(game) + r;
	return r;
}

string xcc_dirs::get_expand_mix(t_game game, int i)
{
	return get_expand_mix(game, nwzl(2, i));
}

string xcc_dirs::get_expand_mix(t_game game, const string& s)
{
	return get_dir(game) + "expand" + get_suffix(game) + s + ".mix";
}

string xcc_dirs::get_language_mix(t_game game)
{
	switch (game)
	{
	case game_ra2:
		return ra2_dir + "language.mix";
	case game_ra2_yr:
		return ra2_dir + "langmd.mix";
	case game_gr:
		return gr_dir + "english.big";
	case game_gr_zh:
		return gr_dir + "englishzh.big";
	}
	assert(false);
	return "";
}

string xcc_dirs::get_local_mix(t_game game)
{
	switch (game)
	{
	case game_ts:
	case game_ra2:
		return "local.mix";
	case game_ra2_yr:
		return "localmd.mix";
	}
	assert(false);
	return "";
}

string xcc_dirs::get_main_mix(t_game game)
{
	switch (game)
	{
	case game_ra:
		return ra_dir + "redalert.mix";
	case game_ts:
		return ts_dir + "tibsun.mix";
	case game_ra2:
		return ra2_dir + "ra2.mix";
	case game_ra2_yr:
		return ra2_dir + "ra2md.mix";
	}
	assert(false);
	return "";
}

static void set_path(string s, string& path)
{
	s = to_lower(s);
	if (!s.empty() && s[s.length() - 1] != '\\')
		s += '\\';	
	path = s;
}

void xcc_dirs::set_dir(t_game game, const string &s)
{
	switch (game)
	{
	case game_td:
		set_path(s, td_primary_dir);
		break;
	case game_ra:
		set_path(s, ra_dir);
		break;
	case game_ts:
		set_path(s, ts_dir);
		break;
	case game_dune2:
		set_path(s, dune2_dir);
		break;
	case game_dune2000:
		set_path(s, dune2000_dir);
		break;
	case game_ra2:
		set_path(s, ra2_dir);
		break;
	case game_rg:
		set_path(s, rg_dir);
		break;
	case game_gr:
		set_path(s, gr_dir);
		break;
	}
}

void xcc_dirs::set_dune2_dir(const string& s)
{
	set_path(s, dune2_dir);
}

void xcc_dirs::set_td_primary_dir(const string& s)
{
	set_path(s, td_primary_dir);
}

void xcc_dirs::set_td_secondary_dir(const string& s)
{
	set_path(s, td_secondary_dir);
}

void xcc_dirs::set_cd_dir(const string& s)
{
	set_path(s, cd_dir);
}

void xcc_dirs::set_data_dir(const string& s)
{
	set_path(s, data_dir);
}

void xcc_dirs::set_ra_dir(const string& s)
{
	set_path(s, ra_dir);
}

void xcc_dirs::set_dune2000_dir(const string& s)
{
	set_path(s, dune2000_dir);
}

void xcc_dirs::set_ts_dir(const string& s)
{
	set_path(s, ts_dir);
}

void xcc_dirs::set_ra2_dir(const string& s)
{
	set_path(s, ra2_dir);
}

void xcc_dirs::reset_cd_dir()
{
	int drive_map = GetLogicalDrives();
	char drive_root[] = "a:\\";
	for (int i = 0; i < 26; i++)
	{		
		if (drive_map >> i & 1 && GetDriveType(drive_root) == DRIVE_CDROM)
		{
			set_cd_dir(drive_root);
			break;
		}
		drive_root[0]++;
	}
}

void xcc_dirs::reset_data_dir()
{
	set_data_dir(GetModuleFileName().get_path());
}

void xcc_dirs::load_from_registry()
{
	HKEY kh_base;
	char s[256];
	dword size;
	if (!Cxcc_registry::get_base_key(kh_base))
	{
		if (ERROR_SUCCESS == RegQueryValueEx(kh_base, "dune2_dir", 0, 0, (byte*)s, &(size = 256)))
			set_dune2_dir(s);
		if (ERROR_SUCCESS == RegQueryValueEx(kh_base, "dir1", 0, 0, (byte*)s, &(size = 256)))
			set_td_primary_dir(s);
		if (ERROR_SUCCESS == RegQueryValueEx(kh_base, "dir2", 0, 0, (byte*)s, &(size = 256)))
			set_td_secondary_dir(s);
		if (ERROR_SUCCESS == RegQueryValueEx(kh_base, "ra_dir", 0, 0, (byte*)s, &(size = 256)))
			set_ra_dir(s);
		if (ERROR_SUCCESS == RegQueryValueEx(kh_base, "cddir", 0, 0, (byte*)s, &(size = 256)))
			set_cd_dir(s);
		if (ERROR_SUCCESS == RegQueryValueEx(kh_base, "datadir", 0, 0, (byte*)s, &(size = 256)))
			set_data_dir(s);
		if (ERROR_SUCCESS == RegQueryValueEx(kh_base, "enable_log", 0, 0, (byte*)s, &(size = 256)))
			g_enable_log = true;
	}
	if (cd_dir.empty())
		reset_cd_dir();
	if (data_dir.empty())
		reset_data_dir();
	HKEY kh_westwood;
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Westwood", 0, KEY_QUERY_VALUE, &kh_westwood))
	{
		if (td_primary_dir.empty() &&		
			ERROR_SUCCESS == RegOpenKeyEx(kh_westwood, "Command & Conquer Windows 95 Edition", 0, KEY_QUERY_VALUE, &kh_base) &&
			ERROR_SUCCESS == RegQueryValueEx(kh_base, "InstallPath", 0, 0, (byte*)s, &(size = 256)))
		{
			set_td_primary_dir(static_cast<Cfname>(s).get_path());
		}
		if (ra_dir.empty() &&		
			ERROR_SUCCESS == RegOpenKeyEx(kh_westwood, "Red Alert Windows 95 Edition", 0, KEY_QUERY_VALUE, &kh_base) &&
			ERROR_SUCCESS == RegQueryValueEx(kh_base, "InstallPath", 0, 0, (byte*)s, &(size = 256)))
		{
			set_ra_dir(static_cast<Cfname>(s).get_path());
		}
		if (dune2000_dir.empty() &&		
			ERROR_SUCCESS == RegOpenKeyEx(kh_westwood, "Dune 2000", 0, KEY_QUERY_VALUE, &kh_base) &&
			ERROR_SUCCESS == RegQueryValueEx(kh_base, "InstallPath", 0, 0, (byte*)s, &(size = 256)))
		{
			set_dune2000_dir(static_cast<Cfname>(s).get_path());
		}
		if (ts_dir.empty() &&		
			ERROR_SUCCESS == RegOpenKeyEx(kh_westwood, "Tiberian Sun", 0, KEY_QUERY_VALUE, &kh_base) &&
			ERROR_SUCCESS == RegQueryValueEx(kh_base, "InstallPath", 0, 0, (byte*)s, &(size = 256)))
		{
			set_ts_dir(static_cast<Cfname>(s).get_path());
		}
		if (ra2_dir.empty() &&		
			ERROR_SUCCESS == RegOpenKeyEx(kh_westwood, "Red Alert 2", 0, KEY_QUERY_VALUE, &kh_base) &&
			ERROR_SUCCESS == RegQueryValueEx(kh_base, "InstallPath", 0, 0, (byte*)s, &(size = 256)))
		{
			set_ra2_dir(static_cast<Cfname>(s).get_path());
		}
		if (rg_dir.empty() &&		
			ERROR_SUCCESS == RegOpenKeyEx(kh_westwood, "Renegade", 0, KEY_QUERY_VALUE, &kh_base) &&
			ERROR_SUCCESS == RegQueryValueEx(kh_base, "InstallPath", 0, 0, (byte*)s, &(size = 256)))
		{
			set_dir(game_rg, static_cast<Cfname>(s).get_path());
		}
	}
	HKEY kh_gr;
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA Games\\Generals", 0, KEY_QUERY_VALUE, &kh_gr))
	{
		if (gr_dir.empty() &&
			ERROR_SUCCESS == RegQueryValueEx(kh_gr, "InstallPath", 0, 0, (byte*)s, &(size = 256)))
			set_dir(game_gr, static_cast<Cfname>(s).get_path());
		RegCloseKey(kh_gr);
	}
}

static int RegSetValueEx(HKEY hKey, LPCTSTR lpValueName, string data)
{
	return RegSetValueEx(hKey, lpValueName, 0, REG_SZ, (byte*)data.c_str(), data.length() + 1);
};

void xcc_dirs::save_to_registry()
{
	HKEY kh_base;
	if (Cxcc_registry::get_base_key(kh_base))
		return;
	RegSetValueEx(kh_base, "dune2_dir", dune2_dir);
	RegSetValueEx(kh_base, "dir1", 0, REG_SZ, (byte*)td_primary_dir.c_str(), td_primary_dir.length() + 1);
	RegSetValueEx(kh_base, "dir2", 0, REG_SZ, (byte*)td_secondary_dir.c_str(), td_secondary_dir.length() + 1);
	RegSetValueEx(kh_base, "ra_dir", ra_dir);
	RegSetValueEx(kh_base, "cddir", 0, REG_SZ, (byte*)cd_dir.c_str(), cd_dir.length() + 1);
	RegSetValueEx(kh_base, "datadir", 0, REG_SZ, (byte*)data_dir.c_str(), data_dir.length() + 1);
};

string xcc_dirs::find_file(Cfname s)
{
	if (!s.get_path().empty() || s.exists())
		return s;
	s.set_path(td_primary_dir);
	if (s.exists())
		return s;
	s.set_path(td_secondary_dir);
	if (s.exists())
		return s;
	s.set_path(ra_dir);
	if (s.exists())
		return s;
	s.set_path(ts_dir);
	if (s.exists())
		return s;
	s.set_path(ra2_dir);
	if (s.exists())
		return s;
	s.set_path(cd_dir);
	return s;
}

bool xcc_dirs::is_available(t_game game)
{
	return Cfname(get_exe(game)).exists();
}