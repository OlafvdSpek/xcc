// virtual_file.h: interface for the Cvirtual_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIRTUAL_FILE_H__96134460_CF52_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_VIRTUAL_FILE_H__96134460_CF52_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vartypes.h"

class Cvirtual_file  
{
public:
	void write(const byte* d, int cb_d);
	Cvirtual_file();
	~Cvirtual_file();

	const byte* data()
	{
		return m_data;
	}

	int size() const
	{
		return m_size;
	}
private:
	byte* m_data;
	int m_size;
};

#endif // !defined(AFX_VIRTUAL_FILE_H__96134460_CF52_11D4_A95D_0050042229FC__INCLUDED_)
