// virtual_binary.cpp: implementation of the Cvirtual_binary class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "virtual_binary.h"

#include "file32.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cvirtual_binary::Cvirtual_binary()
{
	m_data = NULL;
}

Cvirtual_binary::Cvirtual_binary(const Cvirtual_binary& v)
{
	*this = v;
}

Cvirtual_binary::Cvirtual_binary(const void* d, int cb_d)
{
	m_data = new byte[cb_d];
	m_size = cb_d;
	memcpy(m_data, d, cb_d);
}

Cvirtual_binary::~Cvirtual_binary()
{
	delete[] m_data;
}

const Cvirtual_binary& Cvirtual_binary::operator=(const Cvirtual_binary& v)
{
	m_data = new byte[v.m_size];
	m_size = v.m_size;
	memcpy(m_data, v.m_data, v.m_size);
	return *this;
}

int Cvirtual_binary::export(string fname) const
{
	return file32_write(fname, m_data, m_size);
}

int Cvirtual_binary::import(string fname)
{
	Cfile32 f;
	int error = f.open_read(fname);
	if (!error)
	{
		m_size = f.get_size();
		delete[] m_data;
		m_data = new byte[m_size];
		error = f.read(m_data, m_size);
	}
	return error;
}

int Cvirtual_binary::read(void* d) const
{
	if (!data())
		return 0;
	memcpy(d, data(), size());
	return size();
}

void Cvirtual_binary::write(const void* d, int cb_d)
{
	delete[] m_data;
	m_data = new byte[cb_d];
	m_size = cb_d;
	memcpy(m_data, d, cb_d);
}