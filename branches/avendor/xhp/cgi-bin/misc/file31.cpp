// file31.cpp: implementation of the Cfile31 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include "file31.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cfile31::Cfile31()
{
}

Cfile31::~Cfile31()
{
	assert(fail() || !m_f.is_open());
}

int Cfile31::open_read(string fname)
{
	assert(!m_f.is_open());
	m_f.open(fname.c_str(), ios::binary | ios::in);
	return m_f.fail();
}

int Cfile31::open_edit(string fname)
{
	assert(!m_f.is_open());
	m_f.open(fname.c_str(), ios::binary | ios::in | ios::out);
	return m_f.fail();
}

int Cfile31::open_write(string fname)
{
	assert(!m_f.is_open());
	m_f.open(fname.c_str(), ios::binary | ios::out | ios::trunc);
	return m_f.fail();
}

void Cfile31::close()
{
	assert(m_f.is_open());
	m_f.close();
}

int Cfile31::size()
{
	assert(m_f.is_open());
	int pos = m_f.tellp();
	m_f.seekp(0, ios::end);
	int size = m_f.tellp();
	m_f.seekp(pos);
	return size;
}

void Cfile31::read(void* d, int cb_d)
{
	assert(m_f.is_open());
	m_f.read(reinterpret_cast<char*>(d), cb_d);
}

void Cfile31::write(const void* d, int cb_d)
{
	assert(m_f.is_open());
	m_f.write(reinterpret_cast<const char*>(d), cb_d);
}

void Cfile31::seek(int v)
{
	assert(m_f.is_open());
	m_f.seekg(v);
	m_f.seekp(v);
}

void Cfile31::write_bin(const void* d, int cb_d)
{
	write_int(cb_d);
	write(d, cb_d);
}

int Cfile31::read_int()
{
	int r;
	read(&r, sizeof(int));
	return r;
}

void Cfile31::write_int(int v)
{
	write(&v, sizeof(int));
};

string Cfile31::read_str()
{
	int size = read_int();
	char* data = new char[size + 1];
	read(data, size);
	data[size] = 0;
	string r = data;
	delete[] data;
	return r;
}

void Cfile31::write_str(const string& v)
{
	write_bin(v.c_str(), v.length());
}

int file31_write(const string& name, const void* s, int cb_s)
{
	Cfile31 f;
	int error = f.open_write(name);
	if (!error)
	{
		f.write(s, cb_s);
		error = f.fail();
		f.close();
	}
	return error;
}