// aud_file.h: interface for the Caud_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUD_FILE_H__FBD9B691_D563_11D3_A718_0000F81AF8CC__INCLUDED_)
#define AFX_AUD_FILE_H__FBD9B691_D563_11D3_A718_0000F81AF8CC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <cc_file.h>
#include <cc_structures.h>

class Caud_file: public Ccc_file
{
public:
	const t_aud_chunk_header* get_chunk_header(int i);
	const byte* get_chunk_data(int i);
	int extract_as_wav(const string& name);

	Caud_file():
	    Ccc_file(false)
	{
	}

	bool is_valid()
	{
		if (sizeof(t_aud_header) > get_size() ||
			m_header.samplerate < 8000 || m_header.samplerate > 48000 ||
			m_header.size_in != get_size() - sizeof(t_aud_header))
			return false;
		switch (m_header.compression)
		{
		case 1:
			return m_header.flags == 0;
		case 0x63:
			return m_header.flags == 2;
		}
		return false;
	}

    int post_open()
	{
		return read(&m_header, sizeof(t_aud_header));
	}

	bool can_be_decoded() const
	{
		return true;
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

#endif // !defined(AFX_AUD_FILE_H__FBD9B691_D563_11D3_A718_0000F81AF8CC__INCLUDED_)
