// aud_decode.cpp: implementation of the aud_decode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "aud_decode.h"

const static int aud_ima_index_adjust_table[8] = {-1, -1, -1, -1, 2, 4, 6, 8};

const static int aud_ima_step_table[89] = {
	7,     8,     9,     10,    11,    12,     13,    14,    16,
    17,    19,    21,    23,    25,    28,     31,    34,    37,
    41,    45,    50,    55,    60,    66,     73,    80,    88,
    97,    107,   118,   130,   143,   157,    173,   190,   209,
    230,   253,   279,   307,   337,   371,    408,   449,   494,
    544,   598,   658,   724,   796,   876,    963,   1060,  1166,
    1282,  1411,  1552,  1707,  1878,  2066,   2272,  2499,  2749,
    3024,  3327,  3660,  4026,  4428,  4871,   5358,  5894,  6484,
    7132,  7845,  8630,  9493,  10442, 11487,  12635, 13899, 15289,
    16818, 18500, 20350, 22385, 24623, 27086,  29794, 32767};

const static int aud_ws_step_table2[] = {-2, -1, 0, 1};

const static int aud_ws_step_table4[] = {
    -9, -8, -6, -5, -4, -3, -2, -1,
     0,  1,  2,  3,  4,  5,  6,  8};

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
	if (v > 255)
		return 255;
	return v;
}

static void output(char*& w, int v)
{
	*w++ = v - 128;
}

void aud_decode_ws_chunk(const byte* s, char* w, int cs_chunk)
{
	/*
SHORT CurSample;
const BYTE*  InputBuffer = s;
WORD  wOutSize = cs_chunk;
BYTE  code;
signed char  count; // this is a signed char!
WORD  i; // index into InputBuffer
WORD  input; // shifted input
CurSample=0x80; // unsigned 8-bit
i=0;

// note that wOutSize value is crucial for decompression!

while (wOutSize>0) // until wOutSize is exhausted!
{
  input=InputBuffer[i++];
  input<<=2;
  code=HIBYTE(input);
  count=LOBYTE(input)>>2;
  switch (code) // parse code
  {
    case 2: // no compression...
	 if (count & 0x20)
	 {
	   count<<=3;		// here it's significant that (count) is signed:
	   CurSample+=count>>3; // the sign bit will be copied by these shifts!

	   output(w, (BYTE)CurSample);

	   wOutSize--; // one byte added to output
	 }
	 else // copy (count+1) bytes from input to output
	 {
	   for (count++;count>0;count--,wOutSize--,i++)
	       output(w, InputBuffer[i]);
	   CurSample=InputBuffer[i-1]; // set (CurSample) to the last byte sent to output
	 }
	 break;
    case 1: // ADPCM 8-bit -> 4-bit
	 for (count++;count>0;count--) // decode (count+1) bytes
	 {
	   code=InputBuffer[i++];

	   CurSample+=aud_ws_step_table4[(code & 0x0F)]; // lower nibble

	   CurSample=clip8(CurSample);
	   output(w, (BYTE)CurSample);

	   CurSample+=aud_ws_step_table4[(code >> 4)]; // higher nibble

	   CurSample=clip8(CurSample);
	   output(w, (BYTE)CurSample);

	   wOutSize-=2; // two bytes added to output
	 }
	 break;
    case 0: // ADPCM 8-bit -> 2-bit
	 for (count++;count>0;count--) // decode (count+1) bytes
	 {
	   code=InputBuffer[i++];

	   CurSample+=aud_ws_step_table2[(code & 0x03)]; // lower 2 bits

	   CurSample=clip8(CurSample);
	   output(w, (BYTE)CurSample);

	   CurSample+=aud_ws_step_table2[((code>>2) & 0x03)]; // lower middle 2 bits

	   CurSample=clip8(CurSample);
	   output(w, (BYTE)CurSample);

	   CurSample+=aud_ws_step_table2[((code>>4) & 0x03)]; // higher middle 2 bits

	   CurSample=clip8(CurSample);
	   output(w, (BYTE)CurSample);

	   CurSample+=aud_ws_step_table2[((code>>6) & 0x03)]; // higher 2 bits

	   CurSample=clip8(CurSample);
	   output(w, (BYTE)CurSample);

	   wOutSize-=4; // 4 bytes sent to output
	 }
	 break;
    default: // just copy (CurSample) (count+1) times to output
	 for (count++;count>0;count--,wOutSize--)
	     output(w, (BYTE)CurSample);
  }
}
}

void aud_decode_ws_chunk_x(const byte* s, char* w, int cs_chunk)
{
	int sample = 0;
	const byte* r = s;
	char* w_end = w + cs_chunk;
	while (w < w_end)
	{
		int code = *r++;
		int count = code & 0x3f;
		switch (code >> 6)
		{
		case 0: 
			count++;
			while (count--)
			{
				code = *r++;
				*w++ = sample = clip8(sample + aud_ws_step_table2[code & 0x3]);
				*w++ = sample = clip8(sample + aud_ws_step_table2[code >> 2 & 0x3]);
				*w++ = sample = clip8(sample + aud_ws_step_table2[code >> 4 & 0x3]);
				*w++ = sample = clip8(sample + aud_ws_step_table2[code >> 6]);
			}
			break;
		case 1: 
			count++;
			while (count--)
			{
				code = *r++;
				*w++ = sample = clip8(sample + aud_ws_step_table4[code & 0xf]);
				*w++ = sample = clip8(sample + aud_ws_step_table4[code >> 4]);
			}
			break;			
		case 2:
			if (count & 0x20)
			{
				// *w++ = sample = clip8(sample + (static_cast<char>(count << 3) >> 3));
				sample += static_cast<char>(count << 3) >> 3;
				*w++ = sample;
			}
			else 
			{
				count++;
				while (count--)
					*w++ = sample = static_cast<char>(*r++);
			}
			break;
		case 3:
			count++;
			while (count--)
				*w++ = sample;
		}
	}
*/
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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

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
