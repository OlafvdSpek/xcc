// xd2_image.h: interface for the Cxd2_image class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XD2_IMAGE_H__8368B5E8_F681_11D6_B606_0000C006A2C2__INCLUDED_)
#define AFX_XD2_IMAGE_H__8368B5E8_F681_11D6_B606_0000C006A2C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "virtual_binary.h"
#include "xd2_file_map.h"

class Cxd2_image  
{
public:
	Cxif_key save() const;
	Cxd2_image();
	Cxd2_image(const Cvirtual_binary& d, int cx, int cy);
	Cxd2_image(const Cxif_key_r& key);

	const byte* d() const
	{
		return m_d;
	}

	int cx() const
	{
		return m_cx;
	}

	int cy() const
	{
		return m_cy;
	}
private:
	Cvirtual_binary m_d;
	int m_cx;
	int m_cy;
};

typedef Cxd2_file_map<Cxd2_image> Cxd2_image_map;

#endif // !defined(AFX_XD2_IMAGE_H__8368B5E8_F681_11D6_B606_0000C006A2C2__INCLUDED_)
