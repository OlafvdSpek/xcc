// virtual_audio.h: interface for the Cvirtual_audio class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIRTUAL_AUDIO_H__BDA73B00_D9D2_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_VIRTUAL_AUDIO_H__BDA73B00_D9D2_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "virtual_file.h"

class Cvirtual_audio  
{
public:
	void load(const void* audio, int c_samples, int samplerate, int cb_sample, int c_channels);
	void save_as_aud(Cvirtual_file& f) const;
	int save_as_aud(string fname) const;
	void save_as_wav_ima_adpcm(Cvirtual_file& f) const;
	int save_as_wav_ima_adpcm(string fname) const;
	Cvirtual_audio();
	~Cvirtual_audio();

	const __int16* audio() const
	{
		return reinterpret_cast<const __int16*>(m_f.data());
	}

	int cb_audio() const
	{
		return mc_samples * mcb_sample * mc_channels;
	}

	int c_samples() const
	{
		return mc_samples;
	}

	int samplerate() const
	{
		return m_samplerate;
	}

	int cb_sample() const
	{
		return mcb_sample;
	}

	int c_channels() const
	{
		return mc_channels;
	}
private:
	Cvirtual_file m_f;
	int mc_samples;
	int m_samplerate;
	int mcb_sample;
	int mc_channels;
};

#endif // !defined(AFX_VIRTUAL_AUDIO_H__BDA73B00_D9D2_11D4_A95D_0050042229FC__INCLUDED_)
