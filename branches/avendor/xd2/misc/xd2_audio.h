// xd2_audio.h: interface for the Cxd2_audio class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XD2_AUDIO_H__8368B5E6_F681_11D6_B606_0000C006A2C2__INCLUDED_)
#define AFX_XD2_AUDIO_H__8368B5E6_F681_11D6_B606_0000C006A2C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "virtual_binary.h"
#include "xd2_file_map.h"

class Cxd2_audio  
{
public:
	Cxif_key save() const;
	Cxd2_audio();
	Cxd2_audio(const Cvirtual_binary& d, int samplerate);
	Cxd2_audio(const Cxif_key_r& key);

	const byte* d() const
	{
		return m_d.data();
	}
		
	int samplerate() const
	{
		return m_samplerate;
	}
private:
	Cvirtual_binary m_d;
	int m_samplerate;
};

typedef Cxd2_file_map<Cxd2_audio> Cxd2_audio_map;

#endif // !defined(AFX_XD2_AUDIO_H__8368B5E6_F681_11D6_B606_0000C006A2C2__INCLUDED_)
