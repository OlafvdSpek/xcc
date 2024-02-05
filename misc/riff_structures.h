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

struct t_ima_adpcm_chunk_header
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