// xfile32.h: interface for the Cxfile32 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XFILE32_H__96C748E4_D966_11D2_B750_BBE59BC8FB67__INCLUDED_)
#define AFX_XFILE32_H__96C748E4_D966_11D2_B750_BBE59BC8FB67__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <string>
#include "vartypes.h"
#include "windows.h"

using namespace std;

class Cxfile32
{
private:
	bool fopen;
	HANDLE fhandle;
	dword fsize;
	dword pos;
	byte* pcache;
public:
	bool eof();
	void enable_cache(bool v);
	void seek(dword ipos);
	void skip(dword ipos);
	bool is_open();
	Cxfile32();
	~Cxfile32();
	
	long open(const string &fname, 
		dword access = GENERIC_READ, 
		dword creation = OPEN_EXISTING, 
		dword share = FILE_SHARE_READ, 
		dword attributes = FILE_ATTRIBUTE_NORMAL);
	dword get_size() const;
	void read(void* data, dword size);
	void write(void* data, dword size);
	void read_line(string &s);
	void close();

	dword get_p() const
	{
		return pos;
	}
};

class Cxfile32_error
{
};

class Cxfile32_read_error: public Cxfile32_error
{
};

//the format of a file is invalid
class Cxfile32_format_error: public Cxfile32_error
{
};

class Cxfile32_write_error: public Cxfile32_error
{
};

#endif // !defined(AFX_XFILE32_H__96C748E4_D966_11D2_B750_BBE59BC8FB67__INCLUDED_)