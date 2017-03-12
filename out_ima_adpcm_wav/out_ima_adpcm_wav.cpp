#include <boost/algorithm/string.hpp>
#include <shlobj.h>
#include <windows.h>
#include "config.h"
#include "file32.h"
#include "ima_adpcm_wav_encode.h"
#include "out.h"
#include "string_conversion.h"
#include "wav_file.h"
#include "wav_structures.h"
#include "xcc_dirs.h"
#include "xcc_registry.h"

#define PI_TITLE "XCC IMA ADPCM WAV Writer Plug-In v1.01 (x86)"

int getwrittentime();

Cfile32 out_f;
int c_channels;
int samplerate;
const int cb_sample = 2;
int last_pause = 0;
int cb_written;
int start_time;
const int cb_audio = 16 << 10;

Out_Module out = 
{
	OUT_VER,
	PI_TITLE,
	0x19ffff,
	0,
	0,
	config,
	about,
	init,
	quit,
	open,
	close,
	write,
	can_write,
	is_playing,
	pause,
	set_volume,
	set_pan,
	flush,
	get_written_time,
	get_written_time
};

static int CALLBACK WINAPI BrowseCallbackProc( HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED)
	{
		char b[MAX_PATH];
		strcpy(b, config_out_dir());
		int l = strlen(b);
		if (l > 3 && b[l - 1] == '\\')
			b[l - 1] = 0;
		SendMessage(hwnd, BFFM_SETSELECTION, (WPARAM)1, (LPARAM)b);
	}
	return 0;
}

BOOL WINAPI _DllMainCRTStartup(HANDLE hInst, ULONG ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) 
		DisableThreadLibraryCalls(static_cast<HMODULE>(hInst));
	return TRUE;
}

extern "C"
{

void config(HWND hwnd)
{
	char name[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST* idlist;
	bi.hwndOwner = hwnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = name;
	bi.lpszTitle = "Select a directory for WAV file output:";
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = 0;
	idlist = SHBrowseForFolder(&bi);
	if (idlist) 
	{
		char b[MAX_PATH];
		SHGetPathFromIDList(idlist, b);
		config_out_dir(b);
		config_write();
	}
}

void about(HWND hwnd)
{
	MessageBox(hwnd, PI_TITLE "\n"
		"Copyright (C) Olaf van der Spek 2000\n"
		"OlafvdSpek@GMail.Com", "About", MB_OK);
}

void init()
{
	xcc_dirs::load_from_registry();
	config_read();
}

void quit()
{
}

int open(int _samplerate, int _c_channels, int _cbits_sample, int bufferlenms, int prebufferms)
{
	if (_c_channels != 1 && _c_channels != 2 ||
		_cbits_sample != 16)
		return -1;
	char title[MAX_PATH];
	GetWindowText(out.hMainWindow, title, MAX_PATH);
	string name = title;
	int p = name.rfind('-');
	if (p != string::npos)
		name.erase(p, string::npos);
	p = name.find('.');
	if (p != string::npos && atoi(name.substr(0, p).c_str()))
		name.erase(0, p + 1);
	boost::trim(name);
	for (int i = 0; i < name.length(); i++)
	{
		switch (name[i])
		{
		case '\\':
		case '/':
		case ':':
		case '*':
		case '?':
		case '\"':
		case '<':
		case '>':
		case '|':
			name[i] = '_';
		}
	}
	if (!config_out_dir()[0])
		config(out.hMainWindow);
	name = config_out_dir() + name + ".wav";
	if (out_f.open_edit(name)) 
		return -1;
	if (out_f.set_eof())
	{
		out_f.close();
		return -1;
	}
	c_channels = _c_channels;
	samplerate = _samplerate;
	cb_written = 0;
	start_time = 0;
	return 0;
}

void close()
{
	out_f.seek(0);
	byte* s = new byte[cb_written];
	int error = out_f.read(s, cb_written);
	if (!error)
	{
		Cima_adpcm_wav_encode encode;
		encode.load(reinterpret_cast<const short*>(s), cb_written, c_channels);
		t_wav_ima_adpcm_header header;
		wav_ima_adpcm_file_write_header(&header, encode.cb_data(), cb_written / (cb_sample * c_channels), samplerate, c_channels);
		out_f.seek(0);
		error = out_f.write(&header, sizeof(t_wav_ima_adpcm_header));
		if (!error)
			error = out_f.write(encode.data(), encode.cb_data());
	}
	delete[] s;
	if (error)
		out_f.seek(0);
	error = out_f.set_eof();
	out_f.close();
}

int write(const __int16* s, int cb_s)
{
	cb_written += cb_s;
	return out_f.write(s, cb_s);
}

int can_write()
{
	return last_pause ? 0: cb_audio;
}

int is_playing()
{
	return 0;
}

int pause(int pause)
{
	int t = last_pause;
	last_pause = pause;
	return t;
}

void set_volume(int volume)
{
}

void set_pan(int pan)
{
}

void flush(int t)
{
	start_time = 0;
	start_time = t - get_written_time();
}

int get_written_time()
{
	return start_time + static_cast<float>(cb_written) * 1000 / (cb_sample * c_channels * samplerate);
}

__declspec(dllexport) Out_Module* winampGetOutModule()
{
	return &out;
}

}