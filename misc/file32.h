// file32.h: interface for the Cfile32 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILE32_H__DB898AD3_D338_11D3_867E_0000F81AF605__INCLUDED_)
#define AFX_FILE32_H__DB898AD3_D338_11D3_867E_0000F81AF605__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <string>
#include <vartypes.h>
#ifdef _MSC_VER
#include <windows.h>
#else
#include <fstream>
#endif

using namespace std;

class Cfile32  
{
public:
	/*
	void attach(HANDLE handle);
	void detach();
	*/
	int open(HANDLE handle);
    int open(const string& name, dword access);
    int open(const string& name, dword access, dword creation, dword share);
	int open_read(const string& name);
	int open_edit(const string& name);
	int open_write(const string& name);
    int get_size() const;
	FILETIME get_creation_time() const;
	FILETIME get_last_access_time() const;
	FILETIME get_last_write_time() const;
    int read(void* data, int size);
	int read_line(string& s);
    int write(const void* data, int size);
	int write(int v);
	int write(const string& s);
	int set_eof();
    void close();
	const Cfile32& operator=(const Cfile32& v);
	Cfile32();
	Cfile32(const Cfile32& v);
	~Cfile32();

    bool eof() const
	{
		return m_p >= get_size();
	}
	
	HANDLE handle() const
	{
		return m_handle;
	}

	bool is_open() const
    {
        return handle() != INVALID_HANDLE_VALUE;
    }

    int get_p() const
    {
        return m_p;
    }

    void seek(int p)
    {
        m_p = p;
    }

    void skip(int p)
    {
        m_p += p;
    }
private:
#ifdef _MSC_VER
    HANDLE m_handle;
#else
	fstream m_f;
#endif
    // bool m_is_open;
    int m_p;
};

int file32_write(const string& name, const void* s, int cb_s);

#endif // !defined(AFX_FILE32_H__DB898AD3_D338_11D3_867E_0000F81AF605__INCLUDED_)
