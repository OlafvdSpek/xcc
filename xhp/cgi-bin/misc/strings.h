// strings.h: interface for the Cstrings class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGS_H__6FC64BA0_CF65_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_STRINGS_H__6FC64BA0_CF65_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fstream>
#include <string>

using namespace std;

class Cstrings  
{
public:
	int add_string(string v);
	int read(fstream& f);
	int write(fstream& f);
	Cstrings();
	~Cstrings();

	const char* get_string(int offset) const
	{
		return m_data + offset;
	}

	int size() const
	{
		return m_size;
	}
private:
	char* m_data;
	int m_size;
};

#endif // !defined(AFX_STRINGS_H__6FC64BA0_CF65_11D4_A95D_0050042229FC__INCLUDED_)
