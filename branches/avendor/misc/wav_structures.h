#pragma once

#include "vartypes.h"

#pragma pack(push, 1)

struct t_wav_chunk_header
{
	dword id;
	dword size;
};

struct t_wav_format_chunk
{
	t_wav_chunk_header header;
	word formattag;
	word c_channels;
	long samplerate;
	long byterate;
	word blockalign;
	word cbits_sample;
};

struct t_wav_header  
{
	t_wav_chunk_header file_header;
	dword form_type;
	t_wav_format_chunk format_chunk;
	t_wav_chunk_header data_chunk_header;
};

#pragma pack(pop)

const dword wav_file_id = *(dword*)"RIFF";
const dword wav_form_id = *(dword*)"WAVE";
const dword wav_format_id = *(dword*)"fmt ";
const dword wav_data_id = *(dword*)"data";