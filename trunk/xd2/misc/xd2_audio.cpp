#include "stdafx.h"
#include "xd2_audio.h"

Cxd2_audio::Cxd2_audio()
{
}

Cxd2_audio::Cxd2_audio(const shared_data& d, int samplerate)
{
	m_d = d;
	m_samplerate = samplerate;
}

enum
{
	vi_d,
	vi_samplerate,
};

Cxd2_audio::Cxd2_audio(const Cxif_key_r& key)
{
	m_d = key.get_value(vi_d).get_vdata();
	m_samplerate = key.get_value_int(vi_samplerate);
}

Cxif_key Cxd2_audio::save() const
{
	Cxif_key key;
	key.set_value_binary(vi_d, m_d);
	key.set_value_int(vi_samplerate, m_samplerate);
	return key;
}
