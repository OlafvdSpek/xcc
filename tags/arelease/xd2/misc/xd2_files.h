// xd2_files.h: interface for the Cxd2_files class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XD2_FILES_H__07830A80_534B_11D7_B607_0000C006A2C2__INCLUDED_)
#define AFX_XD2_FILES_H__07830A80_534B_11D7_B607_0000C006A2C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xd2_animation.h"
#include "xd2_audio.h"
#include "xd2_image.h"
#include "xd2_shape.h"

class Cxd2_files  
{
public:
	int load(const Cxif_key_r& key);
	Cxif_key save() const;
	int load(const string& dir);
	Cxd2_files();

	const Cxd2_animation_map& animations() const
	{
		return m_animation_map;
	}

	const Cxd2_audio_map& audio() const
	{
		return m_audio_map;
	}

	const Cxd2_data_map& data_map() const
	{
		return m_data_map;
	}

	const Cxd2_image_map& images() const
	{
		return m_image_map;
	}

	const Cxd2_shape_map& shapes() const
	{
		return m_shape_map;
	}
private:
	int load_audio_pak(const string& name);
	int load_pak(const string& name);

	Cxd2_animation_map m_animation_map;
	Cxd2_audio_map m_audio_map;
	Cxd2_data_map m_data_map;
	Cxd2_image_map m_image_map;
	Cxd2_shape_map m_shape_map;
};

#endif // !defined(AFX_XD2_FILES_H__07830A80_534B_11D7_B607_0000C006A2C2__INCLUDED_)
