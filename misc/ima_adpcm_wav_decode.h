#pragma once

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
