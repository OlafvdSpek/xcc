// cell.h: interface for the Ccell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CELL_H__DF70DEDE_1EBC_4F86_96DA_1A36903AD582__INCLUDED_)
#define AFX_CELL_H__DF70DEDE_1EBC_4F86_96DA_1A36903AD582__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "object.h"

class Ccell  
{
public:
	Cobject* object()
	{
		return m_object;
	}

	void object(Cobject* object)
	{
		m_object = object;
	}

	Ccell();
	virtual ~Ccell();
private:
	Cobject* m_object;
};

#endif // !defined(AFX_CELL_H__DF70DEDE_1EBC_4F86_96DA_1A36903AD582__INCLUDED_)
