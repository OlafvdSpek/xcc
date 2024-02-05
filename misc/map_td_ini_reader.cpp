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
#include "map_td_ini_reader.h"

#include "multi_line.h"
#include "string_conversion.h"

static const char* section_code[] = {"basic", "map", "unknown"};
static const char* basic_code[] = {"name", "player", "unknown"};
static const char* map_code[] = {"x", "y", "width", "height", "theater", "unknown"};

int Cmap_td_ini_reader::process_section_start(string_view line)
{
	m_section = t_section_id(find_id(line, section_code, sei_unknown));
	return 0;
}

bool Cmap_td_ini_reader::process_section() const
{
	return m_section != sei_unknown;
}

int Cmap_td_ini_reader::process_key(string_view name, string_view value)
{
	switch (m_section)
	{
	case sei_basic:
		switch (find_id(name, basic_code, bai_unknown))
		{
		case bai_name:
			m_basic_data.name = value;
			break;
		case bai_player:
			m_basic_data.player = value;
			break;
		}
		break;
	case sei_map:
		switch (find_id(name, map_code, mai_unknown))
		{
		case mai_x:
			m_map_data.x = to_int(value);
			break;
		case mai_y:
			m_map_data.y = to_int(value);
			break;
		case mai_cx:
			m_map_data.cx = to_int(value);
			break;
		case mai_cy:
			m_map_data.cy = to_int(value);
			break;
		case mai_theater:
			m_map_data.theater = value;
			break;
		}
		break;
	}
	return 0;
}

bool Cmap_td_ini_reader::is_valid() const
{
	return !(m_map_data.x < 1 ||
		m_map_data.y < 1 ||
		m_map_data.x + m_map_data.cx > 63 ||
		m_map_data.y + m_map_data.cy > 63 ||
		m_map_data.theater.empty());
}
