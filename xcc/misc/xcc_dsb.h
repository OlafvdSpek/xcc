#pragma once

#include "xcc_ds.h"

class Cxcc_dsb  
{
private:
	Cxcc_ds* pds;
	LPDIRECTSOUNDBUFFER pdsb;
public:
	void destroy();
	bool is_available();	
	int lock(int pos, int size, void** p1, dword* s1, void** p2, dword* s2);
	int unlock(void* p1, int s1, void* p2, int s2);
	int set_samplerate(int samplerate);
	int set_pos(int pos);
	int stop();
	int play(int flags);
	Cxcc_dsb();
	virtual ~Cxcc_dsb();
	int create(Cxcc_ds &ds, int size, int c_channels, int samplerate, int cbits_sample, int flags);
	void handle_error(const string &s) const;
	const LPDIRECTSOUNDBUFFER get_p() const;
};
