/*
    XCC Utilities and Library
    Copyright (C) 2002  Olaf van der Spek  <olafvdspek@gmail.com>

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
#include "xif_value.h"

class Cxif_key_r
{
public:
	using t_key_map = vector<pair<int, Cxif_key_r>>;
	using t_value_map = vector<pair<int, Cxif_value>>;

	const Cxif_key_r& get_key(int id) const
	{
		return *find_key(id);
	}

	const Cxif_value& get_value(int id) const
	{
		static Cxif_value z;
		auto i = find_value(id);
		return i ? *i : z;
	}

	float get_value_float(int id) const
	{
		return get_value(id).get_float();
	}

	float get_value_float(int id, float v) const
	{
		return get_value(id).get_float(v);
	}

	int get_value_int(int id) const
	{
		return get_value(id).get_int();
	}

	int get_value_int(int id, int v) const
	{
		return get_value(id).get_int(v);
	}

	__int64 get_value_int64(int id) const
	{
		return *reinterpret_cast<const __int64*>(get_value(id).get_data());
	}

	string get_value_string(int id) const
	{
		return get_value(id).get_string();
	}

	string get_value_string(int id, const string& v) const
	{
		return get_value(id).get_string(v);
	}

	const t_key_map& keys() const
	{
		return m_keys;
	}

	const t_value_map& values() const
	{
		return m_values;
	}

	int c_keys() const
	{
		return keys().size();
	}

	int c_values() const
	{
		return values().size();
	}

	bool has_key(int id) const
	{
		return find_key(id);
	}

	bool has_value(int id) const
	{
		return find_value(id);
	}

	const Cxif_key_r* find_key(int id) const;
	const Cxif_value* find_value(int id) const;
	int import(Cvirtual_binary s);
private:
	int load(const byte* s);

	t_key_map m_keys;
	t_value_map m_values;
};
