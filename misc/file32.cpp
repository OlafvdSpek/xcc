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
	m_handle = INVALID_HANDLE_VALUE;
}

Cfile32::Cfile32(const Cfile32& v)
{
	if (!DuplicateHandle(GetCurrentProcess(), v.handle(), GetCurrentProcess(), &m_handle, 0, false, DUPLICATE_SAME_ACCESS))
		m_handle = INVALID_HANDLE_VALUE;
	m_p = v.get_p();
}

Cfile32::~Cfile32()
{
	close();
}

const Cfile32& Cfile32::operator=(const Cfile32& v)
{
	if (this != &v)
	{
		close();
		DuplicateHandle(GetCurrentProcess(), v.handle(), GetCurrentProcess(), &m_handle, 0, false, DUPLICATE_SAME_ACCESS);
		m_p = v.get_p();
	}
	return *this;
}

#ifdef _MSC_VER
int Cfile32::open(HANDLE handle)
{
	close();
	DuplicateHandle(GetCurrentProcess(), handle, GetCurrentProcess(), &m_handle, 0, false, DUPLICATE_SAME_ACCESS);
	m_p = 0;
	return !is_open();
}

int Cfile32::open(const string& name, dword access)
{
	return access & GENERIC_WRITE ? open(name, access, CREATE_ALWAYS, 0) : open(name, access, OPEN_EXISTING, FILE_SHARE_READ);
}

int Cfile32::open(const string& name, dword access, dword creation, dword share)
{
    close();
	m_handle = CreateFile(name.c_str(), access, share, NULL, creation, FILE_ATTRIBUTE_NORMAL, NULL);
	m_p = 0;
    return !is_open();
}
FILETIME Cfile32::get_creation_time() const
{
    assert(is_open());
	FILETIME time;
	int r = GetFileTime(m_handle, &time, NULL, NULL);
	assert(r);
	return time;
}

FILETIME Cfile32::get_last_access_time() const
{
    assert(is_open());
	FILETIME time;
	int r = GetFileTime(m_handle, NULL, &time,  NULL);
	assert(r);
	return time;
}

FILETIME Cfile32::get_last_write_time() const
{
    assert(is_open());
	FILETIME time;
	int r = GetFileTime(m_handle, NULL, NULL, &time);
	assert(r);
	return time;
}
#endif

int Cfile32::open_read(const string& name)
{
#ifdef _MSC_VER
	return open(name, GENERIC_READ, OPEN_EXISTING, FILE_SHARE_READ);
#else
	assert(!m_f.is_open());
	m_f.open(name.c_str(), ios::binary | ios::in);
	return m_f.fail();
#endif
}

int Cfile32::open_edit(const string& name)
{
#ifdef _MSC_VER
	return open(name, GENERIC_READ | GENERIC_WRITE, OPEN_ALWAYS, 0);
#else
	m_f.open(name.c_str(), ios::binary | ios::in | ios::out);
	return m_f.fail();
#endif
}

int Cfile32::open_write(const string& name)
{
#ifdef _MSC_VER
	return open(name, GENERIC_WRITE, CREATE_ALWAYS, 0);
#else
	m_f.open(name.c_str(), ios::binary | ios::out | ios::trunc);
	return m_f.fail();
#endif
}

int Cfile32::get_size() const
{
    assert(is_open());
#ifdef _MSC_VER
    int res = GetFileSize(m_handle, NULL);
    assert(res != -1);
    return res;
#else
	fstream f = m_f;
	int pos = f.tellp();
	f.seekp(0, ios::end);
	int size = f.tellp();
	f.seekp(pos);
	return size;
#endif
}

int Cfile32::read(void* data, int size)
{
    assert(is_open());
#ifdef _MSC_VER
    if (SetFilePointer(m_handle, m_p, 0, FILE_BEGIN) == -1)
        return 1;
    dword cb_read;
	if (!ReadFile(m_handle, data, size, &cb_read, 0) || cb_read != size)
		return 1;
    m_p += size;
    return 0;
#else
	m_f.read(reinterpret_cast<char*>(data), size);
	return m_f.fail();
#endif
}

/*
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
			if (b[i] == '\r')
				break;
		}
		b[i] = 0;
		s = b;
		seek(pos + i + 2);
	}
	delete[] b;
	return error;
}
*/

int Cfile32::write(const void* data, int size)
{
    assert(is_open());
#ifdef _MSC_VER
    if (SetFilePointer(m_handle, m_p, 0, FILE_BEGIN) == -1)
        return 1;
    dword cb_write;
	if (!WriteFile(m_handle, data, size, &cb_write, 0) || cb_write != size)
		return 1;
    m_p += size;
    return 0;
#else
	m_f.write(reinterpret_cast<const char*>(data), size);
	return m_f.fail();
#endif
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
#ifdef _MSC_VER
    if (SetFilePointer(m_handle, m_p, 0, FILE_BEGIN) == -1)
        return 1;
	return !SetEndOfFile(m_handle);
#else
	return write(NULL, 0);
#endif
}

void Cfile32::close()
{
    if (!is_open())
		return;
#ifdef _MSC_VER
	CloseHandle(m_handle);
	m_handle = INVALID_HANDLE_VALUE;
#else
	m_f.close();
#endif
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