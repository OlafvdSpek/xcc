// xap.cpp: implementation of the Cxap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xap.h"

#include "aud_decode.h"
#include "aud_file.h"
#include "ima_adpcm_wav_decode.h"
#include "ogg_file.h"
#include "voc_file.h"
#include "wav_file.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

bool Cxap::busy()
{
	return m_s.data();
}

int Cxap::load(const Cvirtual_binary s)
{
	m_s = s;
	return 0;
}

unsigned int Cxap::play(void* p)
{
	return reinterpret_cast<Cxap*>(p)->play(false);
}

int Cxap::play(bool start_thread)
{
	if (start_thread)
	{
		AfxBeginThread(play, this);
		return 0;
	}
	Cvirtual_binary s = m_s;
	m_s.clear();

	int error = 0;
	HRESULT dsr;
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
				error = 0x105;
			else
			{
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
						error = 0x107;
					cb_sample = 2;
					c_samples = f.get_fact_chunk().c_samples;
					break;
				default:
					error = 0x106;
				}
				samplerate = format_chunk.samplerate;
			}
			break;
		}
	default:
		error = 0x100;
	}
	if (!error)
	{
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
		if (DS_OK != m_ds->CreateSoundBuffer(&dsbdesc, &dsb, NULL))
			error = 0x101;
		else if (DS_OK != dsb->Lock(0, 0, &p1, &s1, NULL, NULL, DSBLOCK_ENTIREBUFFER))
			error = 0x102;
		else
		{		
			switch (ft)
			{
			case ft_aud:
				{
					Caud_file f;
					f.load(s);
					switch (f.get_header()->compression)
					{
					case 1:
						{
							int chunk_i = 0;
							int cs_remaining = c_samples;
							byte* w = reinterpret_cast<byte*>(p1);
							while (cs_remaining)
							{				
								const t_aud_chunk_header& header = *f.get_chunk_header(chunk_i);
								int cs_chunk = header.size_out / cb_sample;
								aud_decode_ws_chunk(f.get_chunk_data(chunk_i++), reinterpret_cast<char*>(w), header.size_in, header.size_out);
								w += cb_sample * cs_chunk;
								cs_remaining -= cs_chunk;
							}
							Cvirtual_binary(p1, w - reinterpret_cast<byte*>(p1)).export("/temp/aud_ws.bin");
						}
						break;
					case 0x63:
						{
							int chunk_i = 0;
							int cs_remaining = c_samples;
							aud_decode decode;
							decode.init();
							byte* w = reinterpret_cast<byte*>(p1);
							while (cs_remaining)
							{				
								const t_aud_chunk_header& header = *f.get_chunk_header(chunk_i);
								int cs_chunk = header.size_out / cb_sample;
								decode.decode_chunk(f.get_chunk_data(chunk_i++), reinterpret_cast<short*>(w), cs_chunk);
								w += cb_sample * cs_chunk;
								cs_remaining -= cs_chunk;
							}
						}
						break;
					}
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
			if (DS_OK != dsb->Unlock(p1, s1, NULL, NULL))
				error = 0x103;
			else if (dsr = dsb->Play(0, 0, 0), DS_OK != dsr)
				error = 0x104;
			else
			{
				dword status;
				while (dsr = dsb->GetStatus(&status), DS_OK == dsr && status & DSBSTATUS_PLAYING)
					Sleep(100);
				dsb->Release();
				dsb = NULL;
			}
		}
	}
	return error;
}

void Cxap::ds(LPDIRECTSOUND ds)
{
	m_ds = ds;
}