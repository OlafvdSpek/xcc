#include <shlobj.h>
#include <windows.h>
#include "aud_decode.h"
#include "aud_file_write.h"
#include "config.h"
#include "out.h"
#include "string_conversion.h"
#include "xcc_dirs.h"
#include "xcc_registry.h"

#define PI_TITLE "XCC AUD Writer Plug-In v1.01 (x86)"

int getwrittentime();

aud_decode aud_d;
Caud_file_write out_f;
int c_channels;
int samplerate;
const int cbits_sample = 16;
int last_pause = 0;
int cb_written;
int cs_written;
int start_time;
const int cb_audio = 16 << 10;
__int16* audio;
__int16* audio_w;

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
	bi.lpszTitle = "Select a directory for AUD file output:";
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
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
		"XCC@XCC.TMFWeb.NL", "About", MB_OK);
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
	if (_samplerate != 22050 && _samplerate != 44100 ||
		_c_channels != 1 && _c_channels != 2 ||
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
	trim(name);
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
	name = config_out_dir() + name + ".aud";
	if (out_f.open_write(name)) 
		return -1;
	aud_d.init();
	out_f.write_header();
	c_channels = _c_channels;
	samplerate = _samplerate;
	cb_written = 0;
	cs_written = 0;
	start_time = 0;
	audio = new __int16[cb_audio];
	audio_w = audio;
	return 0;
}

int write_audio(bool flush)
{
	__int16* r = audio;
	int cs_chunk = 1024 * samplerate / 22050 * c_channels;
	while (audio_w != r)
	{
		int cs_r = min(audio_w - r, cs_chunk);
		if (cs_r < cs_chunk && !flush)
			break;
		__int16* r_next = r + cs_r;
		if (c_channels == 2)
		{
			audio_combine_channels(r, cs_r);
			cs_r >>= 1;
		}
		if (samplerate == 44100)
		{
			audio_combine_channels(r, cs_r);
			cs_r >>= 1;
		}
		byte chunk[512];
		aud_d.encode_chunk(reinterpret_cast<short*>(r), chunk, cs_r);
		out_f.write_chunk(chunk, cs_r);
		cs_written += cs_r;
		r = r_next;
	}
	if (audio != r)
	{
		int cs = audio_w - r;
		memcpy(audio, r, cs << 1);
		audio_w = audio + cs;
	}
	return 0;
}

void close()
{
	write_audio(true);
	delete[] audio;
	out_f.seek(0);
	out_f.set_c_samples(cs_written);
	out_f.set_samplerate(22050);
	out_f.write_header();
	out_f.close();
}

int write(const __int16* s, int cb_s)
{
	memcpy(audio_w, s, cb_s);
	audio_w += cb_s >> 1;
	int error = write_audio(false);
	cb_written += cb_s;
	return error;
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
	return start_time + static_cast<float>(cb_written) * 1000 / (cbits_sample / 8 * c_channels * samplerate);
}

__declspec(dllexport) Out_Module* winampGetOutModule()
{
	return &out;
}

}