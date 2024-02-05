/*
    XCC Utilities and Library
    Copyright (C) 2000  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
