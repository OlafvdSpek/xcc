// map.cpp: implementation of the Cmap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "map.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cmap::Cmap()
{
	m_cx = 1 << 8;
	m_cy = 1 << 8;
	m_map = new Ccell[m_cx * m_cy];
}

Cmap::~Cmap()
{
	delete[] m_map;
}

Ccell& Cmap::cell(Clocation location)
{
	assert(location.xh() >= 0);
	assert(location.xh() < m_cx);
	assert(location.yh() >= 0);
	assert(location.yh() < m_cy);
	return m_map[location.xh() + m_cx * location.yh()];
}

void Cmap::object(Cobject* object)
{
	cell(object->l()).object(object);
}