// virtual_audio.cpp: implementation of the Cvirtual_audio class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "virtual_audio.h"

#include "aud_file_write.h"
#include "wav_file.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cvirtual_audio::Cvirtual_audio()
{
}

Cvirtual_audio::~Cvirtual_audio()
{
}

void Cvirtual_audio::load(Cvirtual_file f, int c_samples, int samplerate, int cb_sample, int c_channels)
{
	mc_samples = c_samples;
	m_samplerate = samplerate;
	mcb_sample = cb_sample;
	mc_channels = c_channels;
	m_f = f;
	m_f.compact();
}

Cvirtual_file Cvirtual_audio::save_as_aud() const
{
	return aud_file_write(audio(), cb_audio(), c_samples(), samplerate(), c_channels());
}

int Cvirtual_audio::save_as_aud(string fname) const
{
	return aud_file_write(fname, audio(), cb_audio(), c_samples(), samplerate(), c_channels());
}

Cvirtual_file Cvirtual_audio::save_as_wav_ima_adpcm() const
{
	return wav_ima_adpcm_file_write(audio(), cb_audio(), c_samples(), samplerate(), c_channels());
}

int Cvirtual_audio::save_as_wav_ima_adpcm(string fname) const
{
	return wav_ima_adpcm_file_write(fname, audio(), cb_audio(), c_samples(), samplerate(), c_channels());
}

Cvirtual_file Cvirtual_audio::save_as_wav_pcm() const
{
	return wav_pcm_file_write(audio(), cb_audio(), samplerate(), cb_sample(), c_channels());
}

int Cvirtual_audio::save_as_wav_pcm(string fname) const
{
	return wav_pcm_file_write(fname, audio(), cb_audio(), samplerate(), cb_sample(), c_channels());
}