// xd2_shape.h: interface for the Cxd2_shape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XD2_SHAPE_H__8368B5E9_F681_11D6_B606_0000C006A2C2__INCLUDED_)
#define AFX_XD2_SHAPE_H__8368B5E9_F681_11D6_B606_0000C006A2C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xd2_file_map.h"
#include "xd2_image.h"

class Cxd2_shape  
{
public:
	Cxif_key save() const;
	Cxd2_shape();
	Cxd2_shape(const Cxif_key_r& key);

	const Cxd2_image& get(int i) const
	{
		return m_map[i];
	}
	
	void resize(int size)
	{
		m_map.resize(size);
	}
	
	void set(int i, Cxd2_image d)
	{
		m_map[i] = d;
	}
private:
	typedef vector<Cxd2_image> t_map;

	t_map m_map;
};

typedef Cxd2_file_map<Cxd2_shape> Cxd2_shape_map;

#endif // !defined(AFX_XD2_SHAPE_H__8368B5E9_F681_11D6_B606_0000C006A2C2__INCLUDED_)
