// audio idx test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include <iostream>
#include <set>
#include "aud_decode.h"
#include "audio_idx_file.h"
#include "string_conversion.h"
#include "wav_file.h"

int main()
{
	const int cb_h = 4 << 10;
	byte h1[cb_h];
	byte h2[cb_h];
	Ccc_file g(true);
	g.open("c:/temp/audio.bag");
	Caudio_idx_file f;
	f.open("c:/temp/audio.idx");
	if (f.is_valid())
	{
		int c_sounds = f.c_sounds();
		for (int i = 0; i < c_sounds; i++)
		{
			const t_audio_idx_entry& e = f.sound_entry(i);
			/*
			if (e.unknown2 == 512)
				continue;
			*/
			cout << swsr(20, e.fname) << nwsl(10, e.offset) << nwsl(10, e.size) << nwsl(10, e.samplerate) << nwsl(10, e.unknown1) << nwsl(10, e.unknown2) << endl;
			if (e.size < cb_h)
				continue;
			if (e.unknown1 != 12 || e.unknown2 != 512)
				continue;
			aud_decode d;
			d.init();
			const byte* audio_in = g.get_data() + e.offset;
			if (i)
			{
				for (int j = 0; j < cb_h; j++)
					h2[j] |= audio_in[j] ^ h1[j];
			}
			else
			{
				memcpy(h1, audio_in, cb_h);
				memset(h2, 0, cb_h);
			}
			/*
			byte* audio_out = new byte[64 * e.samplerate];
			const int cb_header = 2;
			const int cb_chunk_header = 4;
			int c_samples = e.size - cb_header - ((e.size - cb_header + e.unknown2 - 1) / e.unknown2 * cb_chunk_header) << 1;			
			const byte* r = audio_in + cb_header;
			short* w = reinterpret_cast<short*>(audio_out + wav_file_write_header(audio_out, c_samples, e.samplerate, 2, 1));
			while (r < audio_in + e.size)
			{
				int cs_chunk = min(audio_in + e.size - r, e.unknown2 - 2) * 2;
				r += 2;
				d.decode_chunk(r, w, cs_chunk);
				r += cs_chunk >> 1;
				w += cs_chunk;
			}
			while (0 && c_samples)
			{
				int cs_chunk = min(c_samples, e.unknown2 - cb_chunk_header << 1);
				assert(r + cb_chunk_header + (cs_chunk >> 1) <= audio_in + e.size);
				int h = *reinterpret_cast<const unsigned __int16*>(r);
				assert(h < 0x80);
				r += cb_chunk_header;
				d.decode_chunk(r, w, cs_chunk);
				r += cs_chunk >> 1;
				w += cs_chunk;
				c_samples -= cs_chunk;
			}
			// file32_write(static_cast<string>("d:/temp/bin/") + e.fname + ".bin", g.get_data() + e.offset, e.size);
			file32_write(static_cast<string>("d:/temp/wav/") + e.fname + ".wav", audio_out, reinterpret_cast<byte*>(w) - audio_out);
			delete[] audio_out;
			*/
		}
	}
	f.close();
	g.close();
	for (int j = 0; j < cb_h; j++)
	{
		if (h2[j] != 0xff)
		{
			cout << nwzl(4, j) << ' ' << nh(2, h1[j]) << ' ' << nh(2, h2[j]) << endl;
		}
	}
	return 0;
}
