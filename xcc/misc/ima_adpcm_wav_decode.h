// ima_adpcm_wav_decode.h: interface for the Cima_adpcm_wav_decode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMA_ADPCM_WAV_DECODE_H__66DAC660_C2E5_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_IMA_ADPCM_WAV_DECODE_H__66DAC660_C2E5_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Cima_adpcm_wav_decode  
{
public:
	Cima_adpcm_wav_decode();
	void load(const byte* s, int cb_s, int c_channels, int chunk_size);
	~Cima_adpcm_wav_decode();
	
	int cb_data() const
	{
		return mcb_data;
	}

	int c_samples() const
	{
		return mc_samples;
	}

	const short* data() const
	{
		return m_data;
	}
private:
	short* m_data;
	int mcb_data;
	int mc_samples;
};

#endif // !defined(AFX_IMA_ADPCM_WAV_DECODE_H__66DAC660_C2E5_11D4_A95D_0050042229FC__INCLUDED_)
