// vqa_play.cpp: implementation of the Cvqa_play class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ddpf_conversion.h"
#include "vqa_play.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cvqa_play::Cvqa_play(LPDIRECTDRAW dd, LPDIRECTSOUND ds):
	dd(dd), ds(ds), f(f),
	video_res(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN))
{
	audio_started = error = restore_videomode = window_created = use16 = false;
	ps = ts = 0;
	psb = 0;
	vqa_out = NULL;
}

Cvqa_play::~Cvqa_play()
{
}

int Cvqa_play::set_videomode()
{
	HRESULT result;
#ifndef _DEBUG
	video_res = CSize(640, 480);
#endif
	for (int j = 0; j < 2; j++)
	{
		result = dd->SetDisplayMode(video_res.cx, video_res.cy, j ? 16 : 32);
		if (result == DD_OK)
		{
			use16 = j;
			break;
		}
	}
	if (result != DD_OK)
	{
		AfxMessageBox("Unable to set proper video mode");
		return 1;
	}
	return 0;
}

int Cvqa_play::create(Cvqa_file& _f, bool _set_videomode)
{
	if (error)
		return 1;
	error = true;
	f = &_f;
	vqa_d.start_decode(*f->get_header());
	cx = f->get_cx();
	cy = f->get_cy();
	c_frames = f->get_c_frames();
	audio_write = 0 ;
	i_frame = 0;

	if (_set_videomode)
	{
		if (set_videomode())
			return 2;
		restore_videomode = true;
	}
	{
		DDSURFACEDESC ddsdesc;
		ddsdesc.dwSize = sizeof(DDSURFACEDESC);

		// create primary surface
		ddsdesc.dwFlags = DDSD_CAPS; 
		ddsdesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		if (DD_OK != dd->CreateSurface(&ddsdesc, &ps, 0))
			return 3;

		// create temperory surface
		ddsdesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH; 
		ddsdesc.dwWidth = cx;
		ddsdesc.dwHeight = cy;
		ddsdesc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		if (DD_OK != dd->CreateSurface(&ddsdesc, &ts, 0))
			return 4;
		if (f->get_cbits_pixel() == 16)
		{
			DDPIXELFORMAT pf;
			pf.dwSize = sizeof(DDPIXELFORMAT);
			if (DD_OK != ts->GetPixelFormat(&pf))
				return 8;
			mcb_d_pixel = 4 >> use16;
			vqa_d.set_pf(pf, mcb_d_pixel);
		}
	}
	if (f->get_c_channels())
	{
		// create sound buffer		
		WAVEFORMATEX wfdesc;
		wfdesc.wFormatTag = WAVE_FORMAT_PCM;    
		wfdesc.nChannels = f->get_c_channels();
		wfdesc.nSamplesPerSec = f->get_samplerate();
		wfdesc.wBitsPerSample = 16;			
		wfdesc.nBlockAlign = wfdesc.nChannels * wfdesc.wBitsPerSample >> 3;
		wfdesc.nAvgBytesPerSec = wfdesc.nSamplesPerSec * wfdesc.nBlockAlign;
		wfdesc.cbSize = 0;
		
		DSBUFFERDESC dsbdesc;
		dsbdesc.dwSize = sizeof(DSBUFFERDESC);
		dsbdesc.dwFlags = 0;
		dsbdesc.dwBufferBytes = wfdesc.nAvgBytesPerSec;
		dsbdesc.dwReserved = 0;
		dsbdesc.lpwfxFormat = (LPWAVEFORMATEX)&wfdesc;
		if (DS_OK != ds->CreateSoundBuffer(&dsbdesc, &psb, 0))
			return 5;
	}
	// create window
	if (window.create())
		return 6;
	window_created = true;

	if (f->get_cbits_pixel() == 8)
		vqa_out = new byte[cx * cy];
	else
		vqa_out = new byte[cx * cy * mcb_d_pixel];
	error = false;
	return 0;
}

int Cvqa_play::destroy()
{
	if (ps)
	{
		// destroy primary surface
		ps->Release();
		ps = NULL;
	}
	if (ts)
	{
		// destroy temperory surface
		ts->Release();
		ts = NULL;
	}
	if (psb)
	{
		if (audio_started)
		{
			psb->Stop();
			audio_started = false;
		}
		
		// destroy sound buffer
		psb->Release();
		psb = NULL;
	}
	if (window_created)
	{
		// destroy window
		window.destroy();
		window_created = false;
	}
	delete[] vqa_out;
	vqa_out = NULL;
	if (restore_videomode)
	{
		dd->RestoreDisplayMode();
		restore_videomode = false;
	}	
	return 0;
}

bool Cvqa_play::run()
{
	if (error)
		return false;
	error = true;
	const cb_sb = 2 * f->get_c_channels() * f->get_samplerate();
	while (1)
	{
		if (f->get_chunk_id() == vqa_vqfl_id)
		{
			Cvirtual_binary data = f->read_chunk();
			vqa_d.decode_vqfl_chunk(data, data.size());
		}
		else if (f->is_audio_chunk())
		{
			short* aud_out;
			dword size = f->get_chunk_size();
			if (f->get_chunk_id() >> 24 == '0')
			{
				aud_out = new short[size / 2];
				f->read_chunk(aud_out);
				size /= 4;
			}
			else
			{
				aud_out = new short[2 * size];
				vqa_d.decode_snd2_chunk(f->read_chunk(), size, aud_out);
			}			
			void* p1;
			void* p2;
			dword s1, s2;
			HRESULT result;
			if (DS_OK != (result = psb->Lock(audio_write, size << 2, &p1, &s1, &p2, &s2, 0)))
			{
				delete[] aud_out;
				AfxMessageBox("DS Lock failed", MB_ICONINFORMATION);
				return false;
			}
			memcpy(p1, aud_out, s1);
			if (s2)
				memcpy(p2, aud_out + s1 / 2, s2);
			psb->Unlock(p1, s1, p2, s2);
			delete[] aud_out;
			audio_write += size << 2;
			if (audio_write >= cb_sb)
				audio_write -= cb_sb;
		}
		else if (f->is_video_chunk())
			break;
		else			
			f->skip_chunk();
	}
	vqa_d.decode_vqfr_chunk(f->read_chunk(), vqa_out, palet);
	DDSURFACEDESC ddsdesc;
	ddsdesc.dwSize = sizeof(DDSURFACEDESC);
	if (DD_OK != ts->Lock(0, &ddsdesc, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, 0))
	{
		AfxMessageBox("DD Lock failed", MB_ICONINFORMATION);
		return false;
	}
	if (f->get_cbits_pixel() == 8)
	{
		Cddpf_conversion pfc;
		pfc.set_pf(ddsdesc.ddpfPixelFormat);
		for (int i = 0; i < 256; i++)
			m_color_table[i] = pfc.get_color(palet[i].r, palet[i].g, palet[i].b);
	}		
	byte* line_start = static_cast<byte*>(ddsdesc.lpSurface);
	byte* out_read = vqa_out;
	for (int y = 0; y < cy; y++)
	{
		if (f->get_cbits_pixel() == 16)
		{
			memcpy(line_start, out_read, cx * mcb_d_pixel);
			out_read += cx * mcb_d_pixel;
		}
		else if (use16)
		{
			word* pixel = reinterpret_cast<word*>(line_start);
			for (int x = 0; x < cx; x++)
				*pixel++ = m_color_table[*out_read++];
		}
		else
		{
			dword* pixel = reinterpret_cast<dword*>(line_start);
			for (int x = 0; x < cx; x++)
				*pixel++ = m_color_table[*out_read++];
		}
		line_start += ddsdesc.lPitch;
	}
	ts->Unlock(&ddsdesc);
	if (!audio_started)
	{
		if (f->get_c_channels())
			psb->Play(0, 0, DSBPLAY_LOOPING);
		audio_started = true;
		timer.start();
	}
	while (!timer.passed())
		;
	timer += 1000000 / 15;

	CRect s_rect(CPoint(0, 0), CSize(cx, cy));
	int d_cx = GetSystemMetrics(SM_CXSCREEN);
	int d_cy = GetSystemMetrics(SM_CYSCREEN);
	CRect d_rect;
	switch (cx)
	{
	case 140:
		d_rect = CRect(CPoint(d_cx * (147 - cx) / 2 / 147, 0), CSize(d_cx * cx / 147, d_cy));
		break;
	case 320:
		d_rect = CRect(CPoint(0, d_cy * (200 - cy) / 2 / 200), CSize(d_cx, d_cy * cy / 200));
		break;
	default:
		d_rect = CRect(CPoint(0, d_cy * (400 - cy) / 2 / 400), CSize(d_cx, d_cy * cy / 400));
	}	
	if (DD_OK != ps->Blt(d_rect, ts, s_rect, 0, 0))
	{
		AfxMessageBox("DD Blt failed", MB_ICONINFORMATION);
		return false;
	}
	i_frame++;
	error = false;
	return i_frame < c_frames && !window.stop_req();
}