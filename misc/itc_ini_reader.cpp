/*
    XCC Utilities and Library
    Copyright (C) 2001  Olaf van der Spek  <olafvdspek@gmail.com>

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
#include "itc_ini_reader.h"

#include "string_conversion.h"

static const char* section_code[] = {"unknown"};
static const char* tileset_code[] = {"filename", "tilesinset", "unknown"};

Ctileset_data::Ctileset_data()
{
	m_count = 0;
}

Citc_ini_reader::Citc_ini_reader()
{
	m_section = sei_unknown;
}

void Citc_ini_reader::erase()
{
	m_list.clear();
}

int Citc_ini_reader::process_section_start(const string& line)
{
	m_section = static_cast<t_section_id>(find_id(line, section_code, sei_unknown));
	if (m_section != sei_unknown)
		return 0;
	for (int i = 0; i < 10000; i++)
	{
		if (line != "tileset" + nwzl(4, i))
			continue;
		m_current_tileset = i;
		return 0;
	}
	m_current_tileset = -1;
	return 0;
}

bool Citc_ini_reader::process_section() const
{
	return m_current_tileset != -1;
}

int Citc_ini_reader::process_key(const string& name, const string& value)
{
	switch (m_section)
	{
	case sei_unknown:
		switch (find_id(name, tileset_code, tsi_unknown))
		{
		case tsi_fname:
			m_list[m_current_tileset].m_fname = value;
			break;			
		case tsi_count:
			m_list[m_current_tileset].m_count = atoi(value.c_str());
			break;
		}
	}
	return 0;
}

bool Citc_ini_reader::is_valid() const
{
	return m_list.size();
}
