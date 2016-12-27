#include "stdafx.h"
#include "xcc_dsb.h"

int Cxcc_dsb::create(Cxcc_ds &ds, int size, int c_channels, int samplerate, int cbits_sample, int flags)
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
	if (!pds->get_p()->CreateSoundBuffer(&dsbdesc, &pdsb, 0))
		return 0;
	handle_error("CreateSoundBuffer failed");
	return 1;
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

int Cxcc_dsb::play(int flags)
{
	if (!pdsb->Play(0, 0, flags))
		return 0;
	handle_error("Play failed");
	return 1;
}

int Cxcc_dsb::stop()
{
	if (!pdsb->Stop())
		return 0;
	handle_error("DirectSound Stop failed");
	return 1;
}

int Cxcc_dsb::set_pos(int pos)
{
	if (!pdsb->SetCurrentPosition(pos))
		return 0;
	handle_error("SetCurrentPosition failed");
	return 1;
}

int Cxcc_dsb::set_samplerate(int samplerate)
{
	if (!pdsb->SetFrequency(samplerate))
		return 0;
	handle_error("SetFrequency failed");
	return 1;
}

int Cxcc_dsb::lock(int pos, int size, void** p1, DWORD* s1, void** p2, DWORD* s2)
{
	if (!pdsb->Lock(pos, size, p1, s1, p2, s2, 0))
		return 0;
	handle_error("Lock failed");
	return 1;
}

int Cxcc_dsb::unlock(void* p1, int s1, void* p2, int s2)
{
	if (!pdsb->Unlock(p1, s1, p2, s2))
		return 0;
	handle_error("Unlock failed");
	return 1;
}

bool Cxcc_dsb::is_available()
{
	return pdsb;
}