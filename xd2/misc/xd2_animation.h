// xd2_animation.h: interface for the Cxd2_animation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XD2_ANIMATION_H__8368B5EB_F681_11D6_B606_0000C006A2C2__INCLUDED_)
#define AFX_XD2_ANIMATION_H__8368B5EB_F681_11D6_B606_0000C006A2C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "virtual_binary.h"
#include "xd2_file_map.h"

class Cxd2_animation  
{
public:
	Cxif_key save() const;
	Cxd2_animation();
	Cxd2_animation(const Cvirtual_binary& d, int cf, int cx, int cy);
	Cxd2_animation(const Cxif_key_r& key);

	const byte* d(int i) const
	{
		return m_d.data() + cx() * cy() * i;
	}

	int cf() const
	{
		return m_cf;
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
	int m_cf;
	int m_cx;
	int m_cy;
};

typedef Cxd2_file_map<Cxd2_animation> Cxd2_animation_map;

#endif // !defined(AFX_XD2_ANIMATION_H__8368B5EB_F681_11D6_B606_0000C006A2C2__INCLUDED_)
