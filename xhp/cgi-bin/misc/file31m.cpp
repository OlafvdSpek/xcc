// file31m.cpp: implementation of the Cfile31m class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "file31m.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cfile31m::Cfile31m()
{
	m_data = NULL;
}

int Cfile31m::open_read(string fname)
{
	int error = Cfile31::open_read(fname);
	if (!error)
	{
		m_pos = 0;
		m_size = Cfile31::size();
		m_data = new byte[m_size];
		Cfile31::read(m_data, m_size);
		error = fail();
		if (!error)
			Cfile31::close();
		else
			close();
	}
	return error;
}

void Cfile31m::close()
{
	assert(m_data);
	delete[] m_data;
}

void Cfile31m::seek(int v)
{
	m_pos = v;
}

void Cfile31m::read(void* d, int cb_d)
{
	assert(m_data);
	memcpy(d, m_data + m_pos, cb_d);
	m_pos += cb_d;
}

int Cfile31m::read_int()
{
	assert(m_data);
	m_pos += sizeof(int);
	return *reinterpret_cast<const int*>(m_data + m_pos - sizeof(int));
}

string Cfile31m::read_str()
{
	int size = read_int();
	char* data = new char[size + 1];
	read(data, size);
	data[size] = 0;
	string r = data;
	delete[] data;
	return r;
}