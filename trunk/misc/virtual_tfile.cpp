// virtual_tfile.cpp: implementation of the Cvirtual_tfile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "virtual_tfile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cvirtual_tfile::Cvirtual_tfile()
{
	data = 0;
}

Cvirtual_tfile::~Cvirtual_tfile()
{
	release_memory();
}

void Cvirtual_tfile::load_data(const void* _data, dword _size)
{
	release_memory();
	data = new char[_size];
	memcpy(data, _data, _size);
	size = _size;
	pos = 0;
}

void Cvirtual_tfile::save_data(byte*& _data, dword& _size) const
{
	_data = new byte[size];
	memcpy(_data, data, size);
	_size = size;
}

/*
void Cvirtual_tfile::load_data(xccfile &f)
{
	release_memory();
	size = f.get_size();
	data = new char[size];
	f.seek_block(0);
	f.read_block(reinterpret_cast<byte*>(data), size);
	pos = 0;
}
*/

void Cvirtual_tfile::release_memory()
{
	if (data)
	{
		delete[] data;	
		data = 0;
	}
}

string Cvirtual_tfile::read_line()
{
	assert(data);
	dword spos = pos;
	while (pos < size && data[pos] != 0xa && data[pos] != 0xd)
	{
		pos++;
	}
	string s(data + spos, pos - spos);
	if (pos < size)
	{
		pos++;
		if (pos < size && data[pos] == 0xa)
			pos++;
	}
	return s;
}

void Cvirtual_tfile::write(const string& s)
{
	const dword cb_inc = 4096;
	if (!data)
	{
		reserved = cb_inc;
		size = 0;
		data = new char[reserved];
		pos = 0;
	}
	const dword l = s.length();
	if (pos + l > reserved)
	{
		reserved = (pos + l + cb_inc - 1) & ~(cb_inc - 1);
		char* new_data = new char[reserved];
		memcpy(new_data, data, size);
		delete[] data;
		data = new_data;
	}
	if (force_upper_case)
	{
		for (long i = 0; i < l; i++)
			data[pos++] = toupper(s[i]);		
	}
	else
	{
		memcpy(data + pos, s.c_str(), l);
		pos += l;
	}
	if (pos > size)
		size = pos;
}

void Cvirtual_tfile::write_line(const string& s)
{
	write(s + "\xd\xa");
}