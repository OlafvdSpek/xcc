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

#include <vartypes.h>

class aud_decode  
{
public:
	void init(int index = 0, int sample = 0);
	void decode_chunk(const byte* audio_in, short* audio_out, int cs_chunk);
	void encode_chunk(const short* audio_in, byte* audio_out, int cs_chunk);

	int index() const
	{
		return m_index;
	}
private:
	int m_index;
	int m_sample;
};

void aud_decode_ws_chunk(const byte* s, char* d, int cb_s, int cb_d);
