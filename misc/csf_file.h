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

#include "cc_file_sh.h"
#include "cc_structures.h"

class Ccsf_file : public Ccc_file_sh<t_csf_header>
{
public:
	struct t_map_entry
	{
		wstring value;
		string extra_value;
	};

	using t_map = map<string, t_map_entry>;

    int post_open();
	void erase_value(const string& name);
	string get_converted_value(const string& name) const;
	void set_value(const string& name, const wstring& value, const string& extra_value);
	static string convert2string(const wstring& s);
	static wstring convert2wstring(const string& s);
	Cvirtual_binary write() const;

	bool is_valid() const
	{
		const t_csf_header& h = header();
		return !(sizeof(t_csf_header) > get_size() || 
			h.id != csf_file_id);
	}

	int get_c_strings() const
	{
		return m_map.size();
	}

	const t_map& get_map() const
	{
		return m_map;
	}

	wstring get_value(const string& name) const
	{
		return find_ref(m_map, name).value;
	}

	string get_extra_value(const string& name) const
	{
		return find_ref(m_map, name).extra_value;
	}

	bool has_name(const string& name) const
	{
		return m_map.count(name);
	}
private:
	int get_write_size() const;
	void write(byte* d) const;

	t_map m_map;
};
