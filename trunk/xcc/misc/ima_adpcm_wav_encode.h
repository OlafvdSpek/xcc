// ima_adpcm_wav_encode.h: interface for the Cima_adpcm_wav_encode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMA_ADPCM_WAV_ENCODE_H__25A0A520_C62D_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_IMA_ADPCM_WAV_ENCODE_H__25A0A520_C62D_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vartypes.h"

class Cima_adpcm_wav_encode  
{
public:
	Cima_adpcm_wav_encode();
	void load(const short* s, int cb_s, int c_channels);
	~Cima_adpcm_wav_encode();

	int cb_data() const
	{
		return mcb_data;
	}

	int c_samples() const
	{
		return mc_samples;
	}

	const byte* data() const
	{
		return m_data;
	}
private:
	byte* m_data;
	int mcb_data;
	int mc_samples;
};

#endif // !defined(AFX_IMA_ADPCM_WAV_ENCODE_H__25A0A520_C62D_11D4_B606_0000B4936994__INCLUDED_)
