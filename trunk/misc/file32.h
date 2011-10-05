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
	int write(int v);
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
#ifdef _MSC_VER
    Cwin_handle m_h;
#else
	fstream m_f;
#endif
    int m_p;
};

class Cmemory_map_source
{
public:
	Cmemory_map_source(const Cfile32&);
	Cmemory_map_source* attach();
	void detach();

	const byte* d() const
	{
		return m_d;
	}
private:
	Cwin_handle m_fh;
	Cwin_handle m_mh;
	const byte* m_d;
	int mc_references;
};

class Cmemory_map
{
public:
	void clear();
	const Cmemory_map& operator=(const Cmemory_map&);
	Cmemory_map(const Cfile32&);
	Cmemory_map(const Cmemory_map&);
	~Cmemory_map();

	const byte* d() const
	{
		return m_source ? m_source->d() : NULL;
	}

	Cmemory_map()
	{
		m_source = NULL;
	}
private:
	Cmemory_map_source* m_source;
};

Cvirtual_binary file32_read(const string& name);
int file32_write(const string& name, const void* s, int cb_s);
