// virtual_tfile.h: interface for the Cvirtual_tfile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIRTUAL_TFILE_H__0491E503_ED81_11D2_B601_96FBFE07A371__INCLUDED_)
#define AFX_VIRTUAL_TFILE_H__0491E503_ED81_11D2_B601_96FBFE07A371__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <string>
#include "assert.h"
#include "vartypes.h"

using namespace std;

class Cvirtual_tfile  
{
private:
	char* data;
	bool force_upper_case;
	dword pos;
	dword reserved;
	dword size;
public:
	string read_line();
	void write(const string& s);
	void write_line(const string& s);
	void release_memory();
	void load_data(const void* _data, dword _size);
	void save_data(byte*& _data, dword& _size) const;
	Cvirtual_tfile();
	~Cvirtual_tfile();

	bool eof() const
	{
		return pos >= size;
	}

	void set_force_upper_case(bool v)
	{
		force_upper_case = v;
	}

	void seek(dword ipos)
	{
		pos = ipos;
	}
};

#endif // !defined(AFX_VIRTUAL_TFILE_H__0491E503_ED81_11D2_B601_96FBFE07A371__INCLUDED_)
