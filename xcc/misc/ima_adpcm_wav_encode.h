#pragma once

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
