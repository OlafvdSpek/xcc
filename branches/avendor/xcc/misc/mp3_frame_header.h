// mp3_frame_header.h: interface for the Cmp3_frame_header class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MP3_FRAME_HEADER_H__37153EC1_5D90_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_MP3_FRAME_HEADER_H__37153EC1_5D90_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Cmp3_frame_header  
{
public:
	Cmp3_frame_header();
	Cmp3_frame_header(int v);

	int bitrate() const
	{
		return m_bitrate;
	}

	int channel_mode() const
	{
		return m_channel_mode;
	}

	bool copyright() const
	{
		return m_copyright;
	}

	bool crc() const
	{
		return m_crc;
	}

	int emphasis() const
	{
		return m_emphasis;
	}

	int layer() const
	{
		return m_layer;
	}

	int mode_extension() const
	{
		return m_mode_extension;
	}

	bool original() const
	{
		return m_original;
	}

	bool padding() const
	{
		return m_padding;
	}

	int samplerate() const
	{
		return m_samplerate;
	}

	bool valid() const
	{
		return m_valid;
	}

	int version() const
	{
		return m_version;
	}
private:
	int m_bitrate;
	int m_channel_mode;
	bool m_copyright;
	bool m_crc;
	int m_emphasis;
	int m_layer;
	int m_mode_extension;
	bool m_original;
	bool m_padding;
	int m_samplerate;
	bool m_valid;
	int	m_version;
};

#endif // !defined(AFX_MP3_FRAME_HEADER_H__37153EC1_5D90_11D4_B606_0000B4936994__INCLUDED_)
