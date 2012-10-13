#pragma once

#include "xd2_file_map.h"

class Cxd2_audio
{
public:
	Cxif_key save() const;
	Cxd2_audio();
	Cxd2_audio(const shared_data& d, int samplerate);
	Cxd2_audio(const Cxif_key_r& key);

	const byte* d() const
	{
		return m_d.data();
	}

	int samplerate() const
	{
		return m_samplerate;
	}
private:
	shared_data m_d;
	int m_samplerate;
};

typedef Cxd2_file_map<Cxd2_audio> Cxd2_audio_map;
