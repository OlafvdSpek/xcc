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
}

Cvirtual_tfile::~Cvirtual_tfile()
{
}

void Cvirtual_tfile::load_data(const Cvirtual_binary s)
{
	m_data = s;
	// m_size = s.size();
	pos = 0;
}

/*
void Cvirtual_tfile::save_data(byte*& _data, dword& _size) const
{
	_data = new byte[size];
	memcpy(_data, data, size);
	_size = size;
}
*/

string Cvirtual_tfile::read_line()
{
	assert(data());
	const int first_non_ws = pos;
	int last_non_ws;
	while (pos < size())
	{
		switch (data()[pos++])
		{
		case '\r':
			last_non_ws = pos - 2;
			if (pos < size() && data()[pos] == '\n')
				pos++;
			return string(data() + first_non_ws, last_non_ws - first_non_ws + 1);
		case '\n':
			last_non_ws = pos - 2;
			return string(data() + first_non_ws, last_non_ws - first_non_ws + 1);
		}
	}
	last_non_ws = size() - 1;
	return string(data() + first_non_ws, last_non_ws - first_non_ws + 1);
}

string Cvirtual_tfile::read_line(bool remove_ws)
{
	if (!remove_ws)
		return read_line();
	assert(data());
	int first_non_ws;
	int last_non_ws;
	while (pos < size())
	{
		switch (data()[pos++])
		{
		case '\r':
			if (pos < size() && data()[pos] == '\n')
				pos++;
		case '\n':
			return "";
		case '\t':
		case ' ':
			break;
		default:
			first_non_ws = pos - 1;
			last_non_ws = pos - 2;
			while (pos < size())
			{
				switch (data()[pos++])
				{
				case '\r':
					if (pos < size() && data()[pos] == '\n')
						pos++;
				case '\n':
					return string(data() + first_non_ws, last_non_ws - first_non_ws + 1);
				case '\t':
				case ' ':
					break;
				default:
					last_non_ws = pos - 1;
				}
			}
			return string(data() + first_non_ws, last_non_ws - first_non_ws + 1);
		}
	}
	return "";
}

/*
void Cvirtual_tfile::write(const string& s)
{
	const dword cb_inc = 4096;
	if (!data())
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
	write(s + "\r\n");
}
*/
