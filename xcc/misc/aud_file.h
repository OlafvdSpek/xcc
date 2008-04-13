#pragma once

#include "cc_file.h"
#include "cc_structures.h"
#include <virtual_binary.h>

class Caud_file: public Ccc_file
{
public:
	const t_aud_chunk_header* get_chunk_header(int i);
	const byte* get_chunk_data(int i);
	Cvirtual_binary decode();
	int extract_as_wav(const string& name);
	bool is_valid();

	Caud_file():
	    Ccc_file(false)
	{
	}

	int post_open()
	{
		return read(&m_header, sizeof(t_aud_header));
	}

	int get_c_samples() const
	{
		return m_header.size_out / get_cb_sample();
	}

	int get_samplerate() const
	{
		return m_header.samplerate;
	}

	const t_aud_header* get_header() const
	{
		return &m_header;
	}

	int get_c_channels() const
	{
		return m_header.flags & 1 ? 2 : 1;
	}

	int get_cb_sample() const
	{
		return m_header.flags & 2 ? 2 : 1;
	}
private:
	t_aud_header m_header;
};
