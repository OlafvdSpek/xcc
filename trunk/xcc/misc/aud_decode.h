// aud_decode.h: interface for the aud_decode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUD_DECODE_H__91D272A4_CB0C_11D2_99E5_AC7708C14908__INCLUDED_)
#define AFX_AUD_DECODE_H__91D272A4_CB0C_11D2_99E5_AC7708C14908__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <vartypes.h>

class aud_decode  
{
public:
	void init(int index = 0, int sample = 0);
	void decode_chunk(const byte* audio_in, short* audio_out, int cs_chunk);
	void encode_chunk(const short* audio_in, byte* audio_out, int cs_chunk);

	int index() const
	{
		return m_index;
	}
private:
	int m_index;
	int m_sample;
};

void aud_decode_ws_chunk(const byte* r, char* w, int cs_chunk);
// void aud_encode_chunk(const short* audio_in, byte* audio_out, int& index, int& sample, int cs_chunk);

#endif // !defined(AFX_AUD_DECODE_H__91D272A4_CB0C_11D2_99E5_AC7708C14908__INCLUDED_)
