// wav_file.h: interface for the Cwav_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAV_FILE_H__310B5361_F770_11D3_B605_0000B4936994__INCLUDED_)
#define AFX_WAV_FILE_H__310B5361_F770_11D3_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "riff_file.h"

class Cwav_file: public Criff_file  
{
public:
	// virtual int process();
	int process_chunk(const t_riff_header& header);

	const t_riff_wave_format_chunk& get_format_chunk() const
	{
		return m_format_chunk;
	}

	const t_riff_wave_fact_chunk& get_fact_chunk() const
	{
		return m_fact_chunk;
	}

	const t_riff_header& get_data_header() const
	{
		return m_data_header;
	}

	int get_data_ofs() const
	{
		return m_data_ofs;
	}

	int get_data_size() const
	{
		return get_data_header().size;
	}
private:
	t_riff_header				m_data_header;
	int							m_data_ofs;
	t_riff_wave_format_chunk	m_format_chunk;
	t_riff_wave_fact_chunk		m_fact_chunk;
};

int wav_file_write_header(void* w, int c_samples, int samplerate, int cb_sample, int c_channels);
int wav_ima_adpcm_file_write_header(void* w, int cb_audio, int c_samples, int samplerate, int c_channels);

#endif // !defined(AFX_WAV_FILE_H__310B5361_F770_11D3_B605_0000B4936994__INCLUDED_)
