#pragma once

#include "cc_structures.h"
#include "file32.h"
#include "virtual_file.h"

class Caud_file_write : public Cfile32
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

Cvirtual_file aud_file_write(const void* s, int cb_s, int c_samples, int samplerate, int c_channels);
int aud_file_write(string fname, const void* s, int cb_s, int c_samples, int samplerate, int c_channels);
void audio_combine_channels(__int16* data, int c_samples);
