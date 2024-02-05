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

#include "palet.h"
#include "aud_decode.h"
#include "cc_structures.h"
#include "ddpf_conversion.h"
#include <virtual_binary.h>

class Cvqa_decode  
{
private:
	int* cbf;
	int* cbf_new;
	byte* cbf_write;
	int frame_index;
	int c_cbf_read;
	int mc_channels;
	int m_cx;
	int m_cy;
	int mcx_block;
	int mcy_block;
	byte* m_in_decoded;
	t_game m_version;
	aud_decode aud_dl;
	aud_decode aud_dr;
	Cddpf_conversion m_pfc;
	int mcb_d_pixel;
public:
	void start_decode(const t_vqa_header& header);
	void set_pf(const DDPIXELFORMAT& pf, int cb_pixel);
	void decode_cbf_chunk(const byte* in_raw, int cb_s);
	void decode_snd2_chunk(const byte* in, int size, short* out);
	void decode_vpt_chunk(const byte* in, byte* out);
	void decode_vqfl_chunk(const byte* s, int cb_s);
	void decode_vqfl_chunk(const Cvirtual_binary&);
	void decode_vqfr_chunk(const byte* in, byte* out, t_palet palet);
	void write_block(byte* out, int v, int count, int& x, int y) const;
	Cvqa_decode();
	~Cvqa_decode();
};
