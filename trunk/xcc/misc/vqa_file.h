// vqa_file.h: interface for the Cvqa_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VQA_FILE_H__8D085A24_D71B_11D3_B604_0000B4936994__INCLUDED_)
#define AFX_VQA_FILE_H__8D085A24_D71B_11D3_B604_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cc_file.h>
#include <cc_structures.h>
#include "fname.h"

class Cvqa_file: public Ccc_file  
{
public:
    int post_open();
	int extract_as_avi(const string& name);
	int extract_as_pcx(const Cfname& name, t_file_type ft);
	int extract_as_wav(const string& name);
	int read_chunk_header();
	int read_chunk(void* data);
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

	bool can_be_decoded() const
	{
		return true;
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

	const t_vqa_header* get_header() const
	{
		return &m_header;
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

#endif // !defined(AFX_VQA_FILE_H__8D085A24_D71B_11D3_B604_0000B4936994__INCLUDED_)
