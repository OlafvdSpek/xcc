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

#include <ostream>

class Cneat_key_list  
{
public:
	using t_key_map = map<string, string>;
	using t_key_list = list<t_key_map::iterator>;

	Cneat_key_list() = default;
	Cneat_key_list(const Cneat_key_list& v);
	const Cneat_key_list& operator=(const Cneat_key_list& v);
	void add_key(const string& name, const string& value);
	void erase();
	int write(ostream& os) const;

	const t_key_list& get_key_list() const
	{
		return m_key_list;
	}

	const t_key_map& get_key_map() const
	{
		return m_key_map;
	}
private:
	t_key_map m_key_map;
	t_key_list m_key_list;
};
