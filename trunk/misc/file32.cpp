// file32.cpp: implementation of the Cfile32 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include "file32.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cfile32::Cfile32()
{
    m_is_open = false;
}

Cfile32::~Cfile32()
{
    assert(!is_open());
}

int Cfile32::open(const string& name, dword access)
{
    if (access & GENERIC_WRITE)
        return open(name, access, CREATE_ALWAYS, 0);
    else
        return open(name, access, OPEN_EXISTING, FILE_SHARE_READ);
}

int Cfile32::open(const string& name, dword access, dword creation, dword share)
{
    assert(!is_open());
	m_handle = CreateFile(name.c_str(), access, share, NULL, creation, FILE_ATTRIBUTE_NORMAL, NULL);
	if (m_handle == INVALID_HANDLE_VALUE)
		return 1;
	m_p = 0;
    m_is_open = true;
    return 0;
}

int Cfile32::open_read(const string& name)
{
	return open(name, GENERIC_READ, OPEN_EXISTING, FILE_SHARE_READ);
}

int Cfile32::open_write(const string& name)
{
	return open(name, GENERIC_WRITE, CREATE_ALWAYS, 0);
}

int Cfile32::get_size() const
{
    assert(is_open());
    int res = GetFileSize(m_handle, NULL);
    assert(res != -1);
    return res;
}

int Cfile32::read(void* data, int size)
{
    assert(is_open());
    if (SetFilePointer(m_handle, m_p, 0, FILE_BEGIN) == -1)
        return 1;
    dword cb_read;
	if (!ReadFile(m_handle, data, size, &cb_read, 0) || cb_read != size)
		return 1;
    m_p += size;
    return 0;
}

int Cfile32::read_line(string& s)
{
	int error;
	assert(is_open() & !eof());
	int pos = get_p();
	int size = get_size();
	int cb_b = size - pos;
	if (cb_b > 1024)
		cb_b = 1024;
	char* b = new char[cb_b + 1];
	error = read(b, cb_b);
	if (!error)
	{
		for (int i = 0; i < cb_b; i++)
		{
			if (b[i] == 0x0d)
				break;
		}
		b[i] = 0;
		s = b;
		seek(pos + i + 2);
	}
	delete[] b;
	return error;
}

int Cfile32::write(const void* data, int size)
{
    assert(is_open());
    if (SetFilePointer(m_handle, m_p, 0, FILE_BEGIN) == -1)
        return 1;
    dword cb_write;
	if (!WriteFile(m_handle, data, size, &cb_write, 0) || cb_write != size)
		return 1;
    m_p += size;
    return 0;
}

int Cfile32::write(int v)
{
	return write(&v, sizeof(int));
};

int Cfile32::write(const string& s)
{
	return write(s.c_str(), s.length() + 1);
};

int Cfile32::set_eof()
{
    assert(is_open());
    if (SetFilePointer(m_handle, m_p, 0, FILE_BEGIN) == -1)
        return 1;
	return !SetEndOfFile(m_handle);
}

void Cfile32::close()
{
    assert(is_open());
	CloseHandle(m_handle);
    m_is_open = false;
}

int file32_write(const string& name, const void* s, int cb_s)
{
	Cfile32 f;
	int error = f.open_write(name);
	if (!error)
	{
		error = f.write(s, cb_s);
		f.close();
	}
	return error;
}