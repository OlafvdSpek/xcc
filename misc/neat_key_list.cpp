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

#include "stdafx.h"
#include "neat_key_list.h"

Cneat_key_list::Cneat_key_list(const Cneat_key_list& v)
{
	*this = v;
}

const Cneat_key_list& Cneat_key_list::operator=(const Cneat_key_list& v)
{
	erase();
	for (auto& i : v.m_key_list)
		add_key(i->first, i->second);
	return *this;
}

void Cneat_key_list::add_key(const string& name, const string& value)
{
	auto i = m_key_map.find(name);
	if (i == m_key_map.end())
	{
		m_key_map[name] = value;
		i = m_key_map.find(name);
		m_key_list.push_back(i);
	}
	else
		i->second = value;
}

void Cneat_key_list::erase()
{
	m_key_map.clear();
	m_key_list.clear();
}

int Cneat_key_list::write(ostream& os) const
{
	for (auto& i : m_key_list)
		os << i->first << "=" << i->second << endl;
	return 0;
}
