#pragma once

#pragma pack(push, 1)

struct t_riff_header
{
	unsigned __int32 id;
	unsigned __int32 size;
};

struct t_riff_chunk
{
	unsigned __int32 id;
};

struct t_riff_wave_format_chunk
{
	unsigned __int16 tag;
	unsigned __int16 c_channels;
	unsigned __int32 samplerate;
	unsigned __int32 byterate;
	unsigned __int16 block_align;
	unsigned __int16 cbits_sample;
};

struct t_riff_wave_fact_chunk
{
	unsigned __int32 c_samples;
};

struct t_dvi_adpcm_block_header
{
	__int16 sample;
	unsigned __int8 index;
	unsigned __int8 reserved;
};

const __int32 riff_id = 'FFIR';
const __int32 riff_avi_id = ' IVA';
const __int32 riff_wave_id = 'EVAW';
const __int32 riff_wave_format_id = ' tmf';
const __int32 riff_wave_fact_id = 'tcaf';
const __int32 riff_wave_data_id = 'atad';

#pragma pack(pop)