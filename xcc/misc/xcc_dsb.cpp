// xcc_dsb.cpp: implementation of the Cxcc_dsb class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xcc_dsb.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cxcc_dsb::Cxcc_dsb()
{
	pdsb = NULL;
}

Cxcc_dsb::~Cxcc_dsb()
{
}

long Cxcc_dsb::create(Cxcc_ds &ds, long size, long c_channels, long samplerate, long cbits_sample, dword flags)
{
	pds = &ds;
	WAVEFORMATEX wfdesc;
	wfdesc.wFormatTag = WAVE_FORMAT_PCM;    
	wfdesc.nChannels = c_channels;
	wfdesc.nSamplesPerSec = samplerate;
	wfdesc.wBitsPerSample = cbits_sample;			
	wfdesc.nBlockAlign = wfdesc.nChannels * wfdesc.wBitsPerSample >> 3;
	wfdesc.nAvgBytesPerSec = wfdesc.nSamplesPerSec * wfdesc.nBlockAlign;
	wfdesc.cbSize = 0;
	
	DSBUFFERDESC dsbdesc;
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | flags;
	dsbdesc.dwBufferBytes = size; 
	dsbdesc.dwReserved = 0;
	dsbdesc.lpwfxFormat = (LPWAVEFORMATEX)&wfdesc;
	if (DS_OK != pds->get_p()->CreateSoundBuffer(&dsbdesc, &pdsb, 0))
	{
		handle_error("CreateSoundBuffer failed");
		return 1;
	}
	return 0;		
}

void Cxcc_dsb::destroy()
{
	pdsb->Release();
	pdsb = NULL;
}

void Cxcc_dsb::handle_error(const string &s) const
{
	pds->handle_error(s);
}

const LPDIRECTSOUNDBUFFER Cxcc_dsb::get_p() const
{
	return pdsb;
}

long Cxcc_dsb::play(dword flags)
{
	if (DS_OK != pdsb->Play(0, 0, flags))
	{
		handle_error("Play failed");
		return 1;
	}	
	return 0;
}

long Cxcc_dsb::stop()
{
	if (DS_OK != pdsb->Stop())
	{
		handle_error("DirectSound Stop failed");
		return 1;
	}
	return 0;
}

long Cxcc_dsb::set_pos(dword pos)
{
	if (DS_OK != pdsb->SetCurrentPosition(pos))
	{
		handle_error("SetCurrentPosition failed");
		return 1;
	}
	return 0;
}

long Cxcc_dsb::set_samplerate(dword samplerate)
{
	if (DS_OK != pdsb->SetFrequency(samplerate))
	{
		handle_error("SetFrequency failed");
		return 1;
	}
	return 0;
}

long Cxcc_dsb::lock(dword pos, dword size, void** p1, dword* s1, void** p2, dword* s2)
{

	if (DS_OK != pdsb->Lock(pos, size, p1, s1, p2, s2, 0))
	{
		handle_error("Lock failed");
		return 1;
	}	
	return 0;
}

long Cxcc_dsb::unlock(void* p1, dword s1, void* p2, dword s2)
{
	
	if (DS_OK != pdsb->Unlock(p1, s1, p2, s2))
	{
		handle_error("Unlock failed");
		return 1;
	}	
	return 0;
}

#pragma warning (disable: 4800)

bool Cxcc_dsb::is_available()
{
	return pdsb;
}