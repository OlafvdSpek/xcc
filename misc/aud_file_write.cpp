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
#include "aud_file_write.h"

#include "aud_decode.h"

Caud_file_write::Caud_file_write()
{
	mc_samples = 0;
	m_samplerate = 22050;
}

void Caud_file_write::set_c_samples(int c_samples)
{
	mc_samples = c_samples;
}

void Caud_file_write::set_samplerate(int samplerate)
{
	m_samplerate = samplerate;
}

int Caud_file_write::write_header()
{
	t_aud_header header;
	header.samplerate = m_samplerate;
	header.size_in = (mc_samples + 0x3ff) / 0x400 * sizeof(t_aud_chunk_header) + (mc_samples + 1 >> 1);
	header.size_out = mc_samples << 1;
	header.flags = 0x02;
	header.compression = 0x63;
	return write(&header, sizeof(t_aud_header));
}

int Caud_file_write::write_chunk(const void* data, int c_samples)
{
	t_aud_chunk_header header;
	header.size_in = c_samples + 1 >> 1;
	header.size_out = c_samples << 1;
	header.id = aud_chunk_id;
	int error = write(&header, sizeof(t_aud_chunk_header));
	if (error)
		return error;
	return write(data, header.size_in);
}

void audio_combine_channels(__int16* data, int c_samples)
{
	const __int16* r = reinterpret_cast<const __int16*>(data);
	const __int16* r_end = r + c_samples;
	__int16* w = reinterpret_cast<__int16*>(data);
	while (r < r_end)
	{
		int v = *r++ + *r++;
		*w++ = v / 2;
	}
}

Cvirtual_file aud_file_write(const void* s, int cb_s, int c_samples, int samplerate, int c_channels)
{
	Cvirtual_file f;
	assert(c_channels == 1);
	t_aud_header header;
	header.samplerate = samplerate;
	header.size_in = (c_samples + 0x3ff) / 0x400 * sizeof(t_aud_chunk_header) + (c_samples + 1 >> 1);
	header.size_out = c_samples << 1;
	header.flags = 0x02;
	header.compression = 0x63;
	f.write(&header, sizeof(t_aud_header));
	aud_decode aud_d;
	aud_d.init();
	const short* r = reinterpret_cast<const short*>(s);
	t_aud_chunk_header chunk_header;
	chunk_header.id = aud_chunk_id;
	byte chunk[512];
	while (c_samples)
	{
		int cs_chunk = min(c_samples, 1024);
		aud_d.encode_chunk(r, chunk, cs_chunk);
		r += cs_chunk;
		chunk_header.size_in = cs_chunk + 1 >> 1;
		chunk_header.size_out = cs_chunk << 1;
		f.write(&chunk_header, sizeof(t_aud_chunk_header));
		f.write(chunk, chunk_header.size_in);
		c_samples -= cs_chunk;
	}
	return f;
}

int aud_file_write(string fname, const void* s, int cb_s, int c_samples, int samplerate, int c_channels)
{
	return aud_file_write(s, cb_s, c_samples, samplerate, c_channels).save(fname);
}