// strings.cpp: implementation of the Cstrings class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "strings.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cstrings::Cstrings()
{
	m_data = NULL;
}

Cstrings::~Cstrings()
{
	delete[] m_data;
}

int Cstrings::add_string(string v)
{
	if (m_data)
	{
		const char* r = m_data;
		const char* r_end = m_data + m_size;
		while (r < r_end)
		{
			if (!strcmp(r, v.c_str()))
				return r - m_data;
			r += strlen(r) + 1;
		}
	}
	int cb_v = v.length() + 1;
	int size = m_size + cb_v;
	char* data = new char[size];
	memcpy(data, m_data, m_size);
	memcpy(data + m_size, v.c_str(), cb_v);
	delete[] m_data;
	m_data = data;
	m_size = size;
	return m_size - cb_v;
}

static int read_int(fstream& f)
{
	int r;
	f.read(reinterpret_cast<char*>(&r), sizeof(int));
	return r;
}

static void write_int(fstream& f, int v)
{
	f.write(reinterpret_cast<char*>(&v), sizeof(int));
};

int Cstrings::read(fstream& f)
{
	delete[] m_data;
	m_size = read_int(f);
	if (f.fail())
		return 1;
	m_data = new char[m_size];
	f.read(m_data, m_size);
	return f.fail();
}

int Cstrings::write(fstream& f)
{
	if (!m_data)
		m_size = 0;
	write_int(f, m_size);
	f.write(m_data, m_size);
	return f.fail();
}

