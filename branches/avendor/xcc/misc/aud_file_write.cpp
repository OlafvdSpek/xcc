// aud_file_write.cpp: implementation of the Caud_file_write class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "aud_file_write.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

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