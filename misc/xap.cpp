#include "stdafx.h"
#include "xap.h"

#include "aud_decode.h"
#include "aud_file.h"
#include "ima_adpcm_wav_decode.h"
#include "ogg_file.h"
#include "voc_file.h"
#include "wav_file.h"

static int xap_play2(LPDIRECTSOUND ds, Cvirtual_binary s)
{
	Ccc_file f(true);
	f.load(s);
	t_file_type ft = f.get_file_type();

	int c_channels;
	int cb_sample;
	int samplerate;
	int c_samples;

	switch (ft)
	{
	case ft_aud:
		{
			Caud_file f;
			f.load(s);
			c_channels = 1;
			cb_sample = f.get_cb_sample();
			c_samples = f.get_c_samples();
			samplerate = f.get_samplerate();
			break;
		}
	case ft_ogg:
		{
			Cogg_file f;
			f.load(s);
			c_channels = f.get_c_channels();
			cb_sample = 2;
			c_samples = f.get_c_samples();
			samplerate = f.get_samplerate();
			break;
		}
	case ft_voc:
		{
			Cvoc_file f;
			f.load(s);
			c_channels = 1;
			cb_sample = 1;
			c_samples = f.get_c_samples();
			samplerate = f.get_samplerate();
			break;
		}
	case ft_wav:
		{
			Cwav_file f;
			f.load(s);
			if (f.process())
				return 0x105;
			const t_riff_wave_format_chunk& format_chunk = f.get_format_chunk();
			c_channels = format_chunk.c_channels;
			switch (format_chunk.tag)
			{
			case 1:
				cb_sample = format_chunk.cbits_sample >> 3;
				c_samples = f.get_data_header().size / (cb_sample * format_chunk.c_channels);
				break;
			case 0x11:
				if (format_chunk.cbits_sample != 4)
					return 0x107;
				cb_sample = 2;
				c_samples = f.get_fact_chunk().c_samples;
				break;
			default:
				return 0x106;
			}
			samplerate = format_chunk.samplerate;
			break;
		}
	default:
		return 0x100;
	}
	int cb_audio = c_channels * cb_sample * c_samples;

	WAVEFORMATEX wfdesc;
	ZeroMemory(&wfdesc, sizeof(WAVEFORMATEX));
	wfdesc.wFormatTag = WAVE_FORMAT_PCM;
	wfdesc.nChannels = c_channels;
	wfdesc.nSamplesPerSec = samplerate;
	wfdesc.wBitsPerSample = cb_sample << 3;
	wfdesc.nBlockAlign = wfdesc.nChannels * wfdesc.wBitsPerSample >> 3;
	wfdesc.nAvgBytesPerSec = wfdesc.nSamplesPerSec * wfdesc.nBlockAlign;

	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags = DSBCAPS_GLOBALFOCUS;
	dsbdesc.dwBufferBytes = cb_audio;
	dsbdesc.lpwfxFormat = (LPWAVEFORMATEX)&wfdesc;

	LPDIRECTSOUNDBUFFER dsb;
	void* p1;
	dword s1;
	if (ds->CreateSoundBuffer(&dsbdesc, &dsb, NULL))
		return 0x101;
	int error = 0;
	if (dsb->Lock(0, 0, &p1, &s1, NULL, NULL, DSBLOCK_ENTIREBUFFER))
		error = 0x102;
	else
	{
		switch (ft)
		{
		case ft_aud:
		{
			Caud_file f;
			f.load(s);
			f.decode().read(p1);
			break;
		}
		case ft_ogg:
		{
			Cogg_file f;
			f.load(s);
			Cvirtual_audio audio;
			if (!f.decode(audio))
				memcpy(p1, audio.audio(), audio.cb_audio());
			break;
		}
		case ft_voc:
		{
			Cvoc_file f;
			f.load(s);
			memcpy(p1, f.get_sound_data(), cb_audio);
			break;
		}
		case ft_wav:
		{
			Cwav_file f;
			f.load(s);
			f.process();
			switch (f.get_format_chunk().tag)
			{
			case 1:
				f.seek(f.get_data_ofs());
				f.read(p1, cb_audio);
				break;
			case 0x11:
			{
				Cima_adpcm_wav_decode decode;
				decode.load(f.get_data() + f.get_data_ofs(), f.get_data_size(), c_channels, 512 * c_channels);
				memcpy(p1, decode.data(), cb_audio);
				break;
			}
			}
			break;
		}
		}
		HRESULT dsr;
		if (dsb->Unlock(p1, s1, NULL, NULL))
			error = 0x103;
		else if (dsb->Play(0, 0, 0))
			error = 0x104;
		else
		{
			dword status;
			while (dsr = dsb->GetStatus(&status), DS_OK == dsr && status & DSBSTATUS_PLAYING)
				Sleep(100);
		}
	}
	dsb->Release();
	return error;
}

void xap_play(LPDIRECTSOUND ds, Cvirtual_binary s)
{
	thread([ds, s]()
	{
		xap_play2(ds, s);
	}).detach();
}