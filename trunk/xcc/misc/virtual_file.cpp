// virtual_file.cpp: implementation of the Cvirtual_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "virtual_file.h"

#include "file32.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cvirtual_file::Cvirtual_file()
{
}

Cvirtual_file::~Cvirtual_file()
{
}

void Cvirtual_file::clear()
{
	m_data.clear();
}

void Cvirtual_file::compact()
{
	if (m_data.size() == 1)
		return;
	int cb_d = size();
	byte* d = new byte[cb_d];
	read(d);
	/*
	byte* w = d;
	for (t_data::const_iterator i = m_data.begin(); i != m_data.end(); i++)
		w += i->read(w);
	*/
	clear();
	write(Cvirtual_binary(d, cb_d));
	delete[] d;
}

const byte* Cvirtual_file::data() const
{
	if (m_data.size() != 1)
		return NULL;
	return m_data.begin()->data();
}

int Cvirtual_file::size() const
{
	int r = 0;
	for (t_data::const_iterator i = m_data.begin(); i != m_data.end(); i++)
		 r += i->size();
	return r;
}

int Cvirtual_file::export(string fname) const
{
	Cfile32 f;
	int error = f.open_write(fname);
	if (!error)
	{
		for (t_data::const_iterator i = m_data.begin(); i != m_data.end(); i++)
		{
			error = f.write(i->data(), i->size());
			if (error)
				break;
		}
		f.close();
	}
	return error;
}

int Cvirtual_file::import(string fname)
{
	Cfile32 f;
	int error = f.open_read(fname);
	if (!error)
	{
		int cb_d = f.get_size();
		byte* d = new byte[cb_d];
		error = f.read(d, cb_d);
		if (!error)
		{
			clear();
			write(Cvirtual_binary(d, cb_d));
		}
		delete[] d;
		f.close();
	}
	return error;
}

Cvirtual_binary Cvirtual_file::read() const
{
	if (m_data.size() == 1)
		return *m_data.begin();
	int cb_d = size();
	byte* d = new byte[cb_d];
	read(d);
	Cvirtual_binary r(d, cb_d);
	delete[] d;
	return r;
}

int Cvirtual_file::read(void* d) const
{
	byte* w = reinterpret_cast<byte*>(d);
	for (t_data::const_iterator i = m_data.begin(); i != m_data.end(); i++)
		w += i->read(w);
	return w - reinterpret_cast<byte*>(d);
}

void Cvirtual_file::write(const Cvirtual_binary& d)
{
	m_data.push_back(d);
}

void Cvirtual_file::write(const void* d, int cb_d)
{
	write(Cvirtual_binary(d, cb_d));
}