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

#include <map>
#include <list>

#include "ini_reader.h"
#include "neat_key_list.h"

class Cneat_ini_reader : public Cini_reader
{
public:
	using t_section_map = map<string, Cneat_key_list>;
	using t_section_list = list<t_section_map::iterator>;

	Cneat_ini_reader();
	void erase();
	int process_section_start(const string& line);
	bool process_section() const;
	int process_key(const string& name, const string& value);
	void sub_section(string name, const Cneat_key_list& v);
	int write(ostream& os) const;
	int write(const string& name) const;

	Cneat_key_list& current_section()
	{
		return *m_current_section;
	}

	const t_section_map& get_section_map() const
	{
		return m_section_map;
	}

	const t_section_list& get_section_list() const
	{
		return m_section_list;
	}
private:
	t_section_list m_section_list;
	t_section_map m_section_map;

	Cneat_key_list* m_current_section;
};

Cneat_key_list sub_section(const Cneat_key_list& a, const Cneat_key_list& b);
