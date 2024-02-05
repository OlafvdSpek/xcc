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
#include "ima_adpcm_wav_decode.h"

#include "aud_decode.h"
#include "minmax.h"
#include "riff_structures.h"

Cima_adpcm_wav_decode::Cima_adpcm_wav_decode()
{
	m_data = NULL;
}

Cima_adpcm_wav_decode::~Cima_adpcm_wav_decode()
{
	delete[] m_data;
}

void Cima_adpcm_wav_decode::load(const byte* r, int cb_s, int c_channels, int chunk_size)
{
	int c_chunks = (cb_s + chunk_size - 1) / chunk_size ;
	mc_samples = (cb_s - sizeof(t_ima_adpcm_chunk_header) * c_channels * c_chunks << 1) + c_chunks * c_channels;
	delete[] m_data;
	mcb_data = mc_samples << 1;
	m_data = new short[mc_samples];
	short* w = m_data;
	int cs_remaining = mc_samples;
	while (cs_remaining)
	{
		if (c_channels == 1)
		{
			const t_ima_adpcm_chunk_header& chunk_header = *reinterpret_cast<const t_ima_adpcm_chunk_header*>(r);
			r += sizeof(t_ima_adpcm_chunk_header);
			*w++ = chunk_header.sample;
			cs_remaining--;
			int cs_chunk = min(cs_remaining, chunk_size - sizeof(t_ima_adpcm_chunk_header) << 1);
			aud_decode d;
			d.init(chunk_header.index, chunk_header.sample);
			d.decode_chunk(r, w, cs_chunk);
			r += cs_chunk >> 1;
			w += cs_chunk;
			cs_remaining -= cs_chunk;
		}
		else
		{
			assert(c_channels == 2);
			const t_ima_adpcm_chunk_header& left_chunk_header = *reinterpret_cast<const t_ima_adpcm_chunk_header*>(r);
			r += sizeof(t_ima_adpcm_chunk_header);
			*w++ = left_chunk_header.sample;
			cs_remaining--;
			const t_ima_adpcm_chunk_header& right_chunk_header = *reinterpret_cast<const t_ima_adpcm_chunk_header*>(r);
			r += sizeof(t_ima_adpcm_chunk_header);
			*w++ = right_chunk_header.sample;
			cs_remaining--;
			int cs_chunk = min(cs_remaining, chunk_size - (sizeof(t_ima_adpcm_chunk_header) << 1) << 1);
			aud_decode left_d, right_d;
			left_d.init(left_chunk_header.index, left_chunk_header.sample);
			right_d.init(right_chunk_header.index, right_chunk_header.sample);
			while (cs_chunk >= 16)
			{
				short left_t[8], right_t[8];
				left_d.decode_chunk(r, left_t, 8);
				r += 4;
				right_d.decode_chunk(r, right_t, 8);
				r += 4;
				for (int i = 0; i < 8; i++)
				{
					*w++ = left_t[i];
					*w++ = right_t[i];
				}
				cs_chunk -= 16;
				cs_remaining -= 16;
			}
			if (cs_remaining < 16)
				cs_remaining = 0;
		}
	}
	mc_samples /= c_channels;
}