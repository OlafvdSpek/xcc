// virtual_binary.h: interface for the Cvirtual_binary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIRTUAL_BINARY_H__B59C9DC0_DB25_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_VIRTUAL_BINARY_H__B59C9DC0_DB25_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vartypes.h"

class Cvirtual_binary  
{
public:
	int export(string fname) const;
	int import(string fname);
	int read(void* d) const;
	void write(const void* d, int cb_d);
	const Cvirtual_binary& operator=(const Cvirtual_binary& v);
	Cvirtual_binary();
	Cvirtual_binary(const Cvirtual_binary& v);
	Cvirtual_binary(const void* d, int cb_d);
	~Cvirtual_binary();

	const byte* data() const
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

#endif // !defined(AFX_VIRTUAL_BINARY_H__B59C9DC0_DB25_11D4_A95D_0050042229FC__INCLUDED_)
