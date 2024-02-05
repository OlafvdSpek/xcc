/*
    XCC Utilities and Library
    Copyright (C) 2000  Olaf van der Spek  <olafvdspek@gmail.com>

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

#include <vartypes.h>
#include <virtual_binary.h>

using namespace std;

enum t_vt {vt_bin32, vt_binary, vt_int32, vt_string, vt_external_binary, vt_float, vt_unknown};

class Cxif_value
{
public:
	Cxif_value()
	{
		m_type = vt_unknown;
	}

	Cxif_value(float v)
	{
		m_type = vt_float;
		m_value_float = v;
	}

	Cxif_value(t_vt type, int v)
	{
		m_type = type;
		m_value_int = v;
	}

	Cxif_value(const Cvirtual_binary v, bool fast = false)
	{
		m_type = fast ? vt_external_binary : vt_binary;
		m_data = v;
		// m_fast = fast;
	}

	Cxif_value(const string& v)
	{
		m_type = vt_string;
		memcpy(m_data.write_start(v.length() + 1), v.c_str(), v.length() + 1);
	}

	Cvirtual_binary get_vdata() const
	{
		assert(!idata());
		return m_data;
	}

	const byte* get_data() const
	{
		return idata() ? m_value : m_data.data();
	}

	int get_size() const
	{
		return idata() ? 4 : m_data.size();
	}

	float get_float() const
	{
		assert(get_size() == 4);
		return m_value_float;
	}

	float get_float(float v) const
	{
		return get_size() ? get_float() : v;
	}

	int get_int() const
	{
		assert(get_size() == 4);
		return m_value_int;
	}

	int get_int(int v) const
	{
		return get_size() ? get_int() : v;
	}

	string get_string() const
	{
		assert(get_size());
		return reinterpret_cast<const char*>(get_data());
	}

	string get_string(const string& v) const
	{
		return get_size() ? get_string() : v;
	}

	bool idata() const
	{
		// internal data?
		return get_type() == vt_bin32 || get_type() == vt_float || get_type() == vt_int32;
	}

	void dump(ostream& os, int depth = 0) const;
	t_vt get_type() const;
	void load_old(const byte*& data);
	void load_new(const byte*& data);
	void load_external(const byte*& data);
	void save(byte*& data) const;
	static int skip(const byte* s);
	bool external_data() const;
	void external_save(byte*& data) const;
private:
	Cvirtual_binary m_data;
	t_vt m_type;
	union
	{
		byte m_value[4];
		float m_value_float;
		int m_value_int;
	};
};
