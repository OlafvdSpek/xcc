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
#include "mp3_frame_header.h"

Cmp3_frame_header::Cmp3_frame_header()
{
	m_valid = false;
}

Cmp3_frame_header::Cmp3_frame_header(int v)
{
	m_bitrate = v >> 12 & 0xf;
	m_channel_mode = v >> 6 & 3;
	m_copyright = v >> 3 & 1;
	m_crc = v >> 16 & 1;
	m_emphasis = v & 3;
	m_layer = 4 - (v >> 17 & 3);
	m_mode_extension = v >> 4 & 3;
	m_original = v >> 2 & 1;
	m_padding = v >> 9 & 1;
	m_samplerate = v >> 10 & 3;
	m_version = v >> 19 & 3;
	
	m_valid = (v & 0xfe000000) == 0xfe000000 && 
		m_version != 1 &&
		m_layer != 4 &&
		m_bitrate && m_bitrate != 0xf &&
		m_samplerate != 3;
	if (m_valid)
	{
		const int bitrate_table[2][3][16] = 
		{
			{
				{0,  8, 16, 24, 32, 40, 48,  56,  64,  80,  96, 112, 128, 144, 160, 0}, 
				{0,  8, 16, 24, 32, 40, 48,  56,  64,  80,  96, 112, 128, 144, 160, 0}, 
				{0, 32, 48, 56, 64, 80, 96, 112, 128, 144, 160, 176, 192, 224, 256, 0}  
			},
			{
				{0, 32, 40, 48,  56,  64,  80,  96, 112, 128, 160, 192, 224, 256, 320, 0}, 
				{0, 32, 48, 56,  64,  80,  96, 112, 128, 160, 192, 224, 256, 320, 384, 0}, 
				{0, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 0}  
			}
		};
		m_bitrate = bitrate_table[m_version & 1][3 - m_layer][m_bitrate];
		
		const int samplerate_table[4][3] = 
		{
			{32000, 16000,  8000},
			{    0,     0,     0},
			{22050, 24000, 16000},
			{44100, 48000, 32000} 
			
		};
		m_samplerate = samplerate_table[m_version][m_samplerate];
	}
}