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
#include "theme_ts_ini_reader.h"

#include "string_conversion.h"

void Ctheme_data::name(string_view v)
{
	m_name = v;
}

void Ctheme_data::length(float v)
{
	m_length = v;
}

void Ctheme_data::normal(bool v)
{
	m_normal = v;
}

void Ctheme_data::scenario(int v)
{
	m_scenario = v;
}

void Ctheme_data::side(string_view v)
{
	m_side = v;
}

void Ctheme_data::sound(string_view v)
{
	m_sound = v;
}

void Ctheme_data::repeat(bool v)
{
	m_repeat = v;
}

static const char* section_code[] = {"themes", "unknown"};
static const char* theme_code[] = {"name", "length", "normal", "scenario", "side", "sound", "repeat", "unknown"};

int Ctheme_ts_ini_reader::process_section_start(string_view line)
{
	m_section = t_section_id(find_id(line, section_code, sei_unknown));
	if (m_section != sei_unknown)
		return 0;
	if (!m_theme_list.count(line))
		return 1;
	m_current_theme = line;
	return 0;
}

bool Ctheme_ts_ini_reader::process_section() const
{
	return true;
}

int Ctheme_ts_ini_reader::process_key(string_view name, string_view value)
{
	switch (m_section)
	{
	case sei_themes:
		if (!value.empty())
			m_theme_list[to_lower_copy(string(value))];
		break;
	case sei_unknown:
		switch (find_id(name, theme_code, thi_unknown))
		{
		case thi_name:
			m_theme_list[m_current_theme].name(value);
			break;
		case thi_length:
			m_theme_list[m_current_theme].length(to_float(value));
			break;
		case thi_normal:
			m_theme_list[m_current_theme].normal(atob(to_lower_copy(string(value))));
			break;
		case thi_scenario:
			m_theme_list[m_current_theme].scenario(to_int(value));
			break;
		case thi_side:
			m_theme_list[m_current_theme].side(value);
			break;
		case thi_sound:
			m_theme_list[m_current_theme].sound(value);
			break;
		case thi_repeat:
			m_theme_list[m_current_theme].repeat(atob(to_lower_copy(string(value))));
			break;
		default:
			return 1;
		}
	}
	return 0;
}

bool Ctheme_ts_ini_reader::is_valid() const
{
	return m_theme_list.size();
}
