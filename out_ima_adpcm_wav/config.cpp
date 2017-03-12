#include <windows.h>
#include "config.h"
#include "fname.h"
#include "xcc_dirs.h"

const char* app_name = "XCC IMA ADPCM WAV Writer Plug-In";
string ini_fname;
string out_dir;

void GetPrivateProfileString(const char* name, char* value, int cb_value)
{
	GetPrivateProfileString(app_name, name, NULL, value, cb_value, ini_fname.c_str());
}

void WritePrivateProfileString(const char* name, const char* value)
{
	WritePrivateProfileString(app_name, name, value, ini_fname.c_str());
}

static void config_init()
{
	Cfname fname = GetModuleFileName();
	fname.set_ext(".ini");
	ini_fname = fname;
}

void config_read()
{
	config_init();
	char b[MAX_PATH] = "";
	GetPrivateProfileString("out_dir", b, MAX_PATH);
	out_dir = strlen(b) ? b : xcc_dirs::get_dir(game_ra2);
}

void config_write()
{
	WritePrivateProfileString("out_dir", out_dir.c_str());
}

const char* config_out_dir()
{
	return out_dir.c_str();
}

void config_out_dir(const char* dir)
{
	out_dir = dir;
	int l = out_dir.length();
	if (l && out_dir[l - 1] != '\\')
		out_dir += '\\';
}