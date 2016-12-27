#include "stdafx.h"
#include "theme_ts_ini_reader.h"

#include "string_conversion.h"

Ctheme_data::Ctheme_data()
{
	m_normal = true;
	m_scenario = 0;
	m_repeat = false;
}

void Ctheme_data::name(string v)
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

void Ctheme_data::side(string v)
{
	m_side = v;
}

void Ctheme_data::sound(string v)
{
	m_sound = v;
}

void Ctheme_data::repeat(bool v)
{
	m_repeat = v;
}

static const char* section_code[] = {"themes", "unknown"};
static const char* theme_code[] = {"name", "length", "normal", "scenario", "side", "sound", "repeat", "unknown"};

Ctheme_ts_ini_reader::Ctheme_ts_ini_reader()
{
	m_section = sei_unknown;
	erase();
}

void Ctheme_ts_ini_reader::erase()
{
	m_theme_list.clear();
}

int Ctheme_ts_ini_reader::process_section_start(const string& line)
{
	m_section = static_cast<t_section_id>(find_id(line, section_code, sei_unknown));
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

int Ctheme_ts_ini_reader::process_key(const string& name, const string& value)
{
	switch (m_section)
	{
	case sei_themes:
		if (!value.empty())
			m_theme_list[to_lower_copy(value)];
		break;
	case sei_unknown:
		switch (find_id(name, theme_code, thi_unknown))
		{
		case thi_name:
			m_theme_list[m_current_theme].name(value);
			break;
		case thi_length:
			m_theme_list[m_current_theme].length(atof(value.c_str()));
			break;
		case thi_normal:
			m_theme_list[m_current_theme].normal(atob(to_lower_copy(value)));
			break;
		case thi_scenario:
			m_theme_list[m_current_theme].scenario(atoi(value.c_str()));
			break;
		case thi_side:
			m_theme_list[m_current_theme].side(value);
			break;
		case thi_sound:
			m_theme_list[m_current_theme].sound(value);
			break;
		case thi_repeat:
			m_theme_list[m_current_theme].repeat(atob(to_lower_copy(value)));
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
