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

#include "stdafx.h"
#include "aud_decode.h"

#include <cstring>

const static int aud_ima_index_adjust_table[8] = {-1, -1, -1, -1, 2, 4, 6, 8};

const static int aud_ima_step_table[89] = 
{
	7,     8,     9,     10,    11,    12,     13,    14,    16,
    17,    19,    21,    23,    25,    28,     31,    34,    37,
    41,    45,    50,    55,    60,    66,     73,    80,    88,
    97,    107,   118,   130,   143,   157,    173,   190,   209,
    230,   253,   279,   307,   337,   371,    408,   449,   494,
    544,   598,   658,   724,   796,   876,    963,   1060,  1166,
    1282,  1411,  1552,  1707,  1878,  2066,   2272,  2499,  2749,
    3024,  3327,  3660,  4026,  4428,  4871,   5358,  5894,  6484,
    7132,  7845,  8630,  9493,  10442, 11487,  12635, 13899, 15289,
    16818, 18500, 20350, 22385, 24623, 27086,  29794, 32767
};

const static int aud_ws_step_table2[] = {-2, -1, 0, 1};

const static int aud_ws_step_table4[] = 
{
    -9, -8, -6, -5, -4, -3, -2, -1,
     0,  1,  2,  3,  4,  5,  6,  8
};

void aud_decode_ima_chunk(const byte* audio_in, short* audio_out, int& index, int& sample, int cs_chunk)
{
	int code;
	int delta;
	int step;
	for (int sample_index = 0; sample_index < cs_chunk; sample_index++)
	{
		code = audio_in[sample_index >> 1];
		code = sample_index & 1 ? code >> 4 : code & 0xf;
		step = aud_ima_step_table[index];
		delta = step >> 3;
		if (code & 1)
			delta += step >> 2;
		if (code & 2)
			delta += step >> 1;
		if (code & 4)
			delta += step;
		if (code & 8)
		{
			sample -= delta;
			if (sample < -32768)
				sample = -32768;
		}
		else
		{
			sample += delta;
			if (sample > 32767)
				sample = 32767;
		}
		audio_out[sample_index] = short(sample);
		index += aud_ima_index_adjust_table[code & 7];
		if (index < 0)
			index = 0;
		else if (index > 88)
			index = 88;  
	}
}

static int clip8(int v)
{
	if (v < 0)
		return 0;
	return v > 0xff ? 0xff : v;
}

void aud_decode_ws_chunk(const byte* r, char* w, int cb_s, int cb_d)
{
    if (cb_s == cb_d)
    {
        memcpy(w, r, cb_s);
        return;
    }
	const byte* s_end = r + cb_s;
    int sample = 0x80;
    while (r < s_end)
    {
        char count = *r++ & 0x3f;
        switch (r[-1] >> 6)
        {
		case 0:
			for (count++; count > 0; count--)
			{
				int code = *r++;
				*w++ = sample = clip8(sample + aud_ws_step_table2[code & 3]);
				*w++ = sample = clip8(sample + aud_ws_step_table2[code >> 2 & 3]);
				*w++ = sample = clip8(sample + aud_ws_step_table2[code >> 4 & 3]);
				*w++ = sample = clip8(sample + aud_ws_step_table2[code >> 6]);
			}
			break;
		case 1:
			for (count++; count > 0; count--)
			{
				int code = *r++;
				sample += aud_ws_step_table4[code & 0xf];
				*w++ = sample = clip8(sample);
				sample += aud_ws_step_table4[code >> 4];
				*w++ = sample = clip8(sample);
			}
			break;
		case 2:
			if (count & 0x20)
				*w++ = sample += static_cast<char>(count << 3) >> 3;
			else
			{
				memcpy(w, r, ++count);
				r += count;
				w += count;
				sample = r[-1];
			}
			break;
		default:
			memset(w, sample, ++count);
			w += count;
        }
    }
}

void aud_encode_ima_chunk(const short* audio_in, byte* audio_out, int& index, int& sample, int cs_chunk)
{
	const short* r = audio_in;
	byte* w = audio_out;
	bool sign;
	int code;
	int delta;
	int step;
	for (int sample_index = 0; sample_index < cs_chunk; sample_index++)
	{
		delta = *r++ - sample;
		sign = delta < 0;
		if (delta < 0)
		{
			code = 8;
			delta =- delta;
		}
		else
			code = 0;
		step = aud_ima_step_table[index];
		if (delta >= step)
		{
			code |= 4;
			delta -= step;
		}
		step >>= 1;
		if (delta >= step)
		{
			code |= 2;
			delta -= step;
		}
		step >>= 1;
		if (delta >= step)
		{
			code |= 1;
			delta -= step;
		}
		if (sample_index & 1)
			*w++ |= code << 4;
		else
			*w = code;

		step = aud_ima_step_table[index];
		delta = step >> 3;
		if (code & 1)
			delta += step >> 2;
		if (code & 2)
			delta += step >> 1;
		if (code & 4)
			delta += step;
		if (code & 8)
		{
			sample -= delta;
			if (sample < -32768)
				sample = -32768;
		}
		else
		{
			sample += delta;
			if (sample > 32767)
				sample = 32767;
		}
		index += aud_ima_index_adjust_table[code & 7];
		if (index < 0)
			index = 0;
		else if (index > 88)
			index = 88;  
	}
}

void aud_decode::init(int index, int sample)
{
	m_index = index;
	m_sample = sample;
}

void aud_decode::decode_chunk(const byte* audio_in, short* audio_out, int cs_chunk)
{
	aud_decode_ima_chunk(audio_in, audio_out, m_index, m_sample, cs_chunk);
}

void aud_decode::encode_chunk(const short* audio_in, byte* audio_out, int cs_chunk)
{
	aud_encode_ima_chunk(audio_in, audio_out, m_index, m_sample, cs_chunk);
}
