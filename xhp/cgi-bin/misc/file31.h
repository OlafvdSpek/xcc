// file31.h: interface for the Cfile31 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILE31_H__1D97FC60_7FF2_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_FILE31_H__1D97FC60_7FF2_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fstream>
#include <string>

using namespace std;

class Cfile31  
{
public:
	Cfile31();
	~Cfile31();
	int open_read(string fname);
	int open_edit(string fname);
	int open_write(string fname);
	void close();
	int size();
	void seek(int v);
	void read(void* d, int cb_d);
	void write(const void* d, int cb_d);
	void write_bin(const void* d, int cb_d);
	int read_int();
	void write_int(int v);
	string read_str();
	void write_str(const string& v);

	bool eof() const
	{
		return m_f.eof();
	}

	int fail() const
	{
		return m_f.fail();
	}
private:
	fstream m_f;
};

int file31_write(const string& name, const void* s, int cb_s);

#endif // !defined(AFX_FILE31_H__1D97FC60_7FF2_11D4_B606_0000B4936994__INCLUDED_)
