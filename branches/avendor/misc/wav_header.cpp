#include "stdafx.h"
#include "wav_header.h"

void wav_fill_header(t_wav_header &header, long samplesize, long samplerate, long cbits_sample, long c_channels)
{
	header.file_header.id = wav_file_id;
	header.file_header.size = sizeof(header) - sizeof(header.file_header) + samplesize;
	header.form_type = wav_form_id;
	header.format_chunk.header.id = wav_format_id;
	header.format_chunk.header.size = sizeof(header.format_chunk) - sizeof(header.format_chunk.header);
	header.format_chunk.formattag = 1;
	header.format_chunk.c_channels = short(c_channels);
	header.format_chunk.samplerate = samplerate;
	header.format_chunk.byterate = (cbits_sample >> 3) * c_channels * samplerate;
	header.format_chunk.blockalign = short((cbits_sample >> 3) * c_channels);
	header.format_chunk.cbits_sample = short(cbits_sample);
	header.data_chunk_header.id = wav_data_id;
	header.data_chunk_header.size = samplesize;
}