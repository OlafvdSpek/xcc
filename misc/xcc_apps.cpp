#include "stdafx.h"
#include "xcc_apps.h"

#include "fname.h"
#include "fs_ini_file.h"

Cxcc_apps::Cxcc_apps()
{
	init();
}

bool Cxcc_apps::is_available(t_app app) const
{
	auto i = find_ptr(m_map, app);
	return i  && Cfname(*i).exists();
}

string Cxcc_apps::get_exe(t_app app) const
{
	return find_ref(m_map, app);
}

void Cxcc_apps::set_exe(t_app app, string exe)
{
	if (exe.size())
		m_map[app] = exe;
}

static string find_fs_exe()
{
	CIniFile f;
	char win_dir[256];
	if (!GetWindowsDirectory(win_dir, 256))
		return "";
	if (f.LoadFile((static_cast<string>(win_dir) + "\\finalsun.ini").c_str()))
		return "";
	return f.sections["FinalSun"].values["Path"] + "finalsun.exe";
}

static string find_fa_exe()
{
	CIniFile f;
	char win_dir[256];
	if (!GetWindowsDirectory(win_dir, 256))
		return "";
	if (f.LoadFile((static_cast<string>(win_dir) + "\\finalalert.ini").c_str()))
		return "";
	return f.sections["FinalAlert"].values["Path"] + "finalalert.exe";
}

static void find_se_exe(string& se_exe, string& semm_exe)
{
	HKEY kh_base;
	char s[256];
	DWORD size;
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software", 0, KEY_QUERY_VALUE, &kh_base))
	{
		HKEY kh_cps;
		if (ERROR_SUCCESS == RegOpenKeyEx(kh_base, "Childs Play Software", 0, KEY_QUERY_VALUE, &kh_cps))
		{
			if (ERROR_SUCCESS == RegOpenKeyEx(kh_cps, "SunEdit2K", 0, KEY_QUERY_VALUE, &kh_base) &&
				ERROR_SUCCESS == RegQueryValueEx(kh_base, "AppPath", 0, 0, (BYTE*)s, &(size = 256)))
			{
				se_exe = s;
				se_exe += "se2k.exe";
			}
			if (ERROR_SUCCESS == RegOpenKeyEx(kh_cps, "SunEdit 2K ModMan", 0, KEY_QUERY_VALUE, &kh_base) &&
				ERROR_SUCCESS == RegQueryValueEx(kh_base, "AppPath", 0, 0, (BYTE*)s, &(size = 256)))
			{
				semm_exe = s;
				semm_exe += "se2kmm.exe";
			}
			RegCloseKey(kh_cps);
		}
		RegCloseKey(kh_base);
	}
}

void Cxcc_apps::init()
{
	string xcc_path = GetModuleFileName().get_path();
	set_exe(app_xap, xcc_path + "XCC AV Player.exe");
	set_exe(app_xcr, xcc_path + "XCC Cheat Reporter.exe");
	set_exe(app_xed, xcc_path + "XCC Editor.exe");
	set_exe(app_xgs, xcc_path + "XCC Game Spy.exe");
	set_exe(app_xgsp, xcc_path + "XCC Game Spy Player.exe");
	set_exe(app_xmr, xcc_path + "XCC Mixer.exe");
	set_exe(app_xme, xcc_path + "XCC Mix Editor.exe");
	set_exe(app_xmc, xcc_path + "XCC Mod Creator.exe");
	set_exe(app_xml, xcc_path + "XCC Mod Launcher.exe");
	set_exe(app_xrc, xcc_path + "XCC Radar Customizer.exe");	
	set_exe(app_xrmu, xcc_path + "XCC RA2 Map Updater.exe");	
	set_exe(app_fs, find_fs_exe());
	set_exe(app_fa, find_fa_exe());
	string se_exe, semm_exe;
	find_se_exe(se_exe, semm_exe);
	set_exe(app_se, se_exe);
	set_exe(app_semm, semm_exe);
}
