#pragma once

#include <aud_decode.h>
#include <dd_window.h>
#include <ddraw.h>
#include <timer.h>
#include <vqa_decode.h>
#include <vqa_file.h>

#include <mmsystem.h>
#include <mmreg.h>
#include <msacm.h>
#include <dsound.h>

class Cvqa_play  
{
public:
	Cvqa_play(LPDIRECTDRAW dd, LPDIRECTSOUND ds);
	int create(Cvqa_file& f, bool set_videomode = true);
	bool run();
	int destroy();
	~Cvqa_play();

	bool fail() const
	{
		return error;
	}
private:
	int set_videomode();
	bool restore_videomode;
	bool use16;
	bool window_created;
	Cdd_window window;
	CSize video_res;
	const LPDIRECTDRAW dd;
	const LPDIRECTSOUND ds;
	LPDIRECTSOUNDBUFFER psb;
	LPDIRECTDRAWSURFACE ps;
	LPDIRECTDRAWSURFACE ts;
	Ctimer timer;
	bool audio_started;
	bool error;
	Cvqa_file* f;
	int i_frame;
	int c_frames;
	int cx;
	int cy;
	Cvqa_decode vqa_d;
	t_palet palet;
	int audio_write;
	byte* vqa_out;
	int m_color_table[256];
	int mcb_d_pixel;
};
