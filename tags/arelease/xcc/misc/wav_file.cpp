// wav_file.cpp: implementation of the Cwave_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wav_file.h"
#include "wav_structures.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
int Cwav_file::process()
{
	return Criff_file::process();
}
*/

int Cwav_file::process_chunk(const t_riff_header& header)
{
	if (m_validating)
	{
		if (header.id != riff_id || header.size != get_size() - sizeof(t_riff_header))
			return 1;
	}
	switch (header.id)
	{
	case riff_id:
		{
			t_riff_chunk chunk;
			if (read(&chunk, sizeof(t_riff_chunk)))
				return 1;
			if (m_validating)
				return chunk.id != riff_wave_id;
			int size = header.size - sizeof(t_riff_chunk);
			while (size)
			{
				if (sizeof(t_riff_header) > size)
					return 1;
				t_riff_header header;
				if (read(&header, sizeof(t_riff_header)))
					return 1;
				size -= sizeof(t_riff_header);
				if (header.size > size)
					return 1;
				int error = process_chunk(header);
				if (error)
					return error;
				size -= header.size;
			}
			return 0;
		}
	case riff_wave_format_id:
		if (read(&m_format_chunk, sizeof(t_riff_wave_format_chunk)))
			return 1;
		skip(header.size - sizeof(t_riff_wave_format_chunk));
		return 0;
	case riff_wave_fact_id:
		if (read(&m_fact_chunk, sizeof(t_riff_wave_fact_chunk)))
			return 1;
		skip(header.size - sizeof(t_riff_wave_fact_chunk));
		return 0;
	case riff_wave_data_id:
		m_data_header = header;
		m_data_ofs = get_p();
	}
	skip(header.size);
	return 0;
}

int wav_file_write_header(void* w, int c_samples, int samplerate, int cb_sample, int c_channels)
{
	t_wav_header& header = *reinterpret_cast<t_wav_header*>(w);
	memset(&header, 0, sizeof(t_wav_header));
	header.file_header.id = wav_file_id;
	header.file_header.size = sizeof(header) - sizeof(header.file_header) + cb_sample * c_samples * c_channels;
	header.form_type = wav_form_id;
	header.format_chunk.header.id = wav_format_id;
	header.format_chunk.header.size = sizeof(header.format_chunk) - sizeof(header.format_chunk.header);
	header.format_chunk.formattag = 1;
	header.format_chunk.c_channels = c_channels;
	header.format_chunk.samplerate = samplerate;
	header.format_chunk.byterate =  cb_sample * c_channels;
	header.format_chunk.blockalign = cb_sample * c_channels;
	header.format_chunk.cbits_sample = cb_sample << 3;
	header.data_chunk_header.id = wav_data_id;
	header.data_chunk_header.size = cb_sample * c_samples * c_channels;
	return sizeof(t_wav_header);
}