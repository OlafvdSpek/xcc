// file31m.h: interface for the Cfile31m class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILE31M_H__4E675482_9938_11D4_A95A_0050042229FC__INCLUDED_)
#define AFX_FILE31M_H__4E675482_9938_11D4_A95A_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "file31.h"
#include "vartypes.h"

class Cfile31m: private Cfile31
{
public:
	Cfile31m();
	int open_read(string fname);
	void close();
	void seek(int v);
	void read(void* d, int cb_d);
	int read_int();
	string read_str();

	bool eof() const
	{
		return m_pos == m_size;
	}

	int size() const
	{
		return m_size;
	}
private:
	byte* m_data;
	int m_pos;
	int m_size;
};

#endif // !defined(AFX_FILE31M_H__4E675482_9938_11D4_A95A_0050042229FC__INCLUDED_)
