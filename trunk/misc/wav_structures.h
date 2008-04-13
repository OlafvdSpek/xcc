#pragma once

#include <vartypes.h>

#pragma pack(push, 1)

struct t_wav_chunk_header
{
	int id;
	int size;
};

struct t_wav_format_chunk
{
	t_wav_chunk_header header;
	__int16 formattag;
	__int16 c_channels;
	__int32 samplerate;
	__int32 byterate;
	__int16 blockalign;
	__int16 cbits_sample;
};

struct t_wav_header
{
	t_wav_chunk_header file_header;
	int form_type;
	t_wav_format_chunk format_chunk;
	t_wav_chunk_header data_chunk_header;
};

struct t_wav_ima_adpcm_format_chunk
{
	t_wav_chunk_header header;
	__int16 formattag;
	__int16 c_channels;
	__int32 samplerate;
	__int32 byterate;
	__int16 blockalign;
	__int16 cbits_sample;
	unsigned __int16 cb_extra;
	unsigned __int16 cb_block;
};

struct t_wav_fact_chunk
{
	t_wav_chunk_header header;
	int c_samples;
};

struct t_wav_ima_adpcm_header
{
	t_wav_chunk_header file_header;
	int form_type;
	t_wav_ima_adpcm_format_chunk format_chunk;
	t_wav_fact_chunk fact_chunk;
	t_wav_chunk_header data_chunk_header;
};

#pragma pack(pop)

const int wav_file_id = *(int*)"RIFF";
const int wav_form_id = *(int*)"WAVE";
const int wav_format_id = *(int*)"fmt ";
const int wav_fact_id = *(int*)"fact";
const int wav_data_id = *(int*)"data";