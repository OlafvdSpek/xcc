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

#include "cc_file.h"
#include "cc_structures.h"
#include "fname.h"
#include "video_decoder.h"

#pragma comment(lib, "vfw32.lib")

class Cvqa_file : public Ccc_file  
{
public:
	Cvideo_decoder* decoder();
	int post_open();
	int extract_as_avi(const string& name, HWND hwnd);
	int extract_as_pcx(const Cfname& name, t_file_type ft);
	int extract_as_wav(const string& name);
	int read_chunk_header();
	int read_chunk(void* data);
	Cvirtual_binary read_chunk();
	void set_empty_chunk();
	int skip_chunk();

	Cvqa_file():
		Ccc_file(false)
	{
	}

	bool is_valid()
	{
		int size = get_size();
		/*
		if (get_data())
			memcpy(&m_header, get_data(), sizeof(t_vqa_header));
		*/
		return !(sizeof(t_vqa_header) > size ||
			m_header.file_header.id != vqa_file_id ||
			m_header.id != vqa_form_id);
	}

	int get_c_channels() const
	{
		return m_header.c_channels;
	}

	int get_c_frames() const
	{
		return m_header.c_frames;
	}

	int get_chunk_id() const
	{
		return m_chunk_header.id;
	}

	int get_chunk_size() const
	{
		return m_chunk_header.size;
	}

	int get_cx() const
	{
		return m_header.cx;
	}

	int get_cy() const
	{
		return m_header.cy;
	}

	int get_cx_block() const
	{
		return m_header.cx_block;
	}

	int get_cy_block() const
	{
		return m_header.cy_block;
	}

	const t_vqa_header& header() const
	{
		return m_header;
	}

	int get_samplerate() const
	{
		return m_header.samplerate;
	}

	bool is_audio_chunk() const
	{
		return (get_chunk_id() & vqa_t_mask) == vqa_snd_id;
	}

	bool is_video_chunk() const
	{
		return (get_chunk_id()) == vqa_vqfr_id;
	}

	int get_cbits_pixel() const
	{
		return m_header.video_flags & 0x10 ? 16 : 8;
	}

	int get_cbits_sample() const
	{
		return m_header.cbits_sample;
	}
private:
	t_vqa_chunk_header m_chunk_header;
	t_vqa_header m_header;
};
