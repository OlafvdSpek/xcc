// aud_file_write.h: interface for the Caud_file_write class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUD_FILE_WRITE_H__33F65560_F820_11D3_B605_0000B4936994__INCLUDED_)
#define AFX_AUD_FILE_WRITE_H__33F65560_F820_11D3_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_structures.h"
#include "file32.h"

class Caud_file_write: public Cfile32
{
public:
	void set_c_samples(int c_samples);
	void set_samplerate(int samplerate);
	int write_header();
	int write_chunk(const void* data, int c_samples);
	Caud_file_write();
private:
	int mc_samples;
	int m_samplerate;
};

void audio_combine_channels(__int16* data, int c_samples);

#endif // !defined(AFX_AUD_FILE_WRITE_H__33F65560_F820_11D3_B605_0000B4936994__INCLUDED_)
