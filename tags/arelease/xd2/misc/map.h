// map.h: interface for the Cmap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_H__E74E0F1E_33BF_4521_95DE_45F0C4DB42BC__INCLUDED_)
#define AFX_MAP_H__E74E0F1E_33BF_4521_95DE_45F0C4DB42BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cell.h"
#include "location.h"

class Cmap  
{
public:
	Ccell& cell(Clocation location);
	void object(Cobject* object);

	Cmap();
	virtual ~Cmap();
private:
	int m_cx;
	int m_cy;
	Ccell* m_map;
};

#endif // !defined(AFX_MAP_H__E74E0F1E_33BF_4521_95DE_45F0C4DB42BC__INCLUDED_)
