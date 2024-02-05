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

class Cstream_reader
{
public:
	const byte* d() const
	{
		return m_d.data();
	}

	const byte* d_end() const
	{
		return m_d.data_end();
	}

	const byte* r() const
	{
		return m_r;
	}

	const byte* read(int size)
	{
		const byte* v = r();
		skip(size);
		return v;
	}

	short read_short()
	{
		return *reinterpret_cast<const __int16*>(read(2));
	}

	int read_int()
	{
		return *reinterpret_cast<const __int32*>(read(4));
	}

	int read_int(int o)
	{
		seek(o);
		return read_int();
	}

	const char* read_string()
	{
		return reinterpret_cast<const char*>(read(strlen(reinterpret_cast<const char*>(r())) + 1));
	}

	const char* read_string(int o)
	{
		seek(o);
		return read_string();
	}

	void seek(int o)
	{
		m_r = d() + o;
	}

	void skip(int o)
	{
		m_r += o;
	}

	Cstream_reader()
	{
	}

	Cstream_reader(const Cvirtual_binary& v)
	{
		m_d = v;
    m_r = d();
	}
private:
	Cvirtual_binary m_d;
	const byte* m_r;
};
