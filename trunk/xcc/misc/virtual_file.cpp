// virtual_file.cpp: implementation of the Cvirtual_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "virtual_file.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cvirtual_file::Cvirtual_file()
{
	m_data = NULL;
}

Cvirtual_file::~Cvirtual_file()
{
	delete[] m_data;
}

void Cvirtual_file::write(const byte* d, int cb_d)
{
	delete[] m_data;
	m_data = new byte[cb_d];
	m_size = cb_d;
	memcpy(m_data, d, cb_d);
}