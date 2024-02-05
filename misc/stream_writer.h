/*
    XCC Utilities and Library
    Copyright (C) 2003  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <virtual_binary.h>

class Cstream_writer
{
public:
	/*
	const byte* d() const
	{
		return m_d;
	}

	const byte* d_end() const
	{
		return m_d.data_end();
	}
	*/

	byte* w() const
	{
		return m_w;
	}

	byte* write(int size)
	{
		byte* v = w();
		skip(size);
		return v;
	}

	int write_int(int v)
	{
		*reinterpret_cast<__int32*>(write(4)) = v;
	}

	int write_int(int o, int v)
	{
		seek(o);
		return write_int(v);
	}

	void write_string(const string& v)
	{
		memcpy(write(v.length() + 1), v.c_str(), v.length() + 1);
	}

	void write_string(int o, const string& v)
	{
		seek(o);
		write_string(v);
	}

	void seek(int o)
	{
		assert(false);
		// m_w = m_d.data_edit() + o;
	}

	void skip(int o)
	{
		m_w += o;
	}

	Cstream_writer()
	{
	}

	Cstream_writer(byte* w)
	{
		m_w = w;
	}
private:
	// Cvirtual_binary m_d;
	byte* m_w;
};
