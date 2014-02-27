#pragma once

#include <string>
#include <vartypes.h>
#include <virtual_binary.h>
#ifdef _MSC_VER
#include "win_handle.h"
#else
#include <fstream>
#endif

using namespace std;

class Cfile32
{
public:
	Cvirtual_binary get_mm();
	int open(const Cwin_handle& h);
	int open(const string& name, int access);
	int open(const string& name, int access, int creation, int share);
	int open_read(const string& name);
	int open_edit(const string& name);
	int open_write(const string& name);
	long long size() const;
	FILETIME get_creation_time() const;
	FILETIME get_last_access_time() const;
	FILETIME get_last_write_time() const;
	int read(void* data, int size);
	int write(const void* data, int size);
	int write(data_ref);
	int set_eof();
	void close();

	bool eof() const
	{
		return m_p >= size();
	}

	const Cwin_handle& h() const
	{
		return m_h;
	}

	bool is_open() const
	{
		return h();
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
	Cwin_handle m_h;
	int m_p;
};

Cvirtual_binary file32_read(const string& name);
int file32_write(const string& name, const void* s, int cb_s);
