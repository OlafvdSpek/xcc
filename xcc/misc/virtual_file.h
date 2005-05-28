// virtual_file.h: interface for the Cvirtual_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIRTUAL_FILE_H__96134460_CF52_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_VIRTUAL_FILE_H__96134460_CF52_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
#include "virtual_binary.h"

using namespace std;

class Cvirtual_file  
{
public:
	int save(const string& fname) const;
	int load(const string& fname);
	void clear();
	void compact();
	const byte* data() const;
	int size() const;
	Cvirtual_binary read() const;
	int read(void* d) const;
	void write(const Cvirtual_binary& d);
	void write(const void* d, int cb_d);
	Cvirtual_file();
	Cvirtual_file(const Cvirtual_binary& d);
private:
	typedef list<Cvirtual_binary> t_data;
	t_data m_data;
};

#endif // !defined(AFX_VIRTUAL_FILE_H__96134460_CF52_11D4_A95D_0050042229FC__INCLUDED_)
