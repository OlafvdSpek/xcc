#include "stdafx.h"
#include "map_td_ini_reader.h"

#include "multi_line.h"
#include "string_conversion.h"

static const char* section_code[] = {"basic", "map", "unknown"};
static const char* basic_code[] = {"name", "player", "unknown"};
static const char* map_code[] = {"x", "y", "width", "height", "theater", "unknown"};

void Cmap_td_ini_reader::erase()
{
	m_map_data.x = 0;
	m_map_data.y = 0;
	m_map_data.cx = 0;
	m_map_data.cy = 0;
};

int Cmap_td_ini_reader::process_section_start(const string& line)
{
	m_section = static_cast<t_section_id>(find_id(line, section_code, sei_unknown));
	return 0;
}

bool Cmap_td_ini_reader::process_section() const
{
	return m_section != sei_unknown;
}

int Cmap_td_ini_reader::process_key(const string& name, const string& value)
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
			m_map_data.x = atoi(value.c_str());
			break;
		case mai_y:
			m_map_data.y = atoi(value.c_str());
			break;
		case mai_cx:
			m_map_data.cx = atoi(value.c_str());
			break;
		case mai_cy:
			m_map_data.cy = atoi(value.c_str());
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
