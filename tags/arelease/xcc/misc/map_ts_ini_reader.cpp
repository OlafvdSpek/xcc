// map_ts_ini_reader.cpp: implementation of the Cmap_ts_ini_reader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "map_ts_ini_reader.h"
#include "multi_line.h"
#include "string_conversion.h"

static const char* section_code[] = {"basic", "map", "preview", "previewpack", "unknown"};
static const char* basic_code[] = {"name", "player", "unknown"};
static const char* map_code[] = {"localsize", "size", "theater", "unknown"};
static const char* preview_code[] = {"size", "unknown"};

Cmap_ts_ini_reader::Cmap_ts_ini_reader()
{
	m_fast = false;
	m_section = sei_unknown;
	erase();
}

void Cmap_ts_ini_reader::erase()
{
	m_map_data.localsize_left = 0;
	m_map_data.localsize_top = 0;
	m_map_data.localsize_right = 0;
	m_map_data.localsize_bottom = 0;
	m_map_data.size_left = 0;
	m_map_data.size_top = 0;
	m_map_data.size_right = 0;
	m_map_data.size_bottom = 0;
	m_preview_data.x = 0;
	m_preview_data.y = 0;
	m_preview_data.cx = 0;
	m_preview_data.cy = 0;
};

int Cmap_ts_ini_reader::process_section_start(const string& line)
{
	m_section = static_cast<t_section_id>(find_id(line, section_code, sei_unknown));
	return 0;
}

bool Cmap_ts_ini_reader::process_section() const
{
	if (m_fast && m_section == sei_preview_pack)
		return false;
	return m_section != sei_unknown;
}

int Cmap_ts_ini_reader::process_key(const string& name, const string& value)
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
		case mai_localsize:
			{
				Cmulti_line l = value;
				m_map_data.localsize_left = l.get_next_int();
				m_map_data.localsize_top = l.get_next_int();
				m_map_data.localsize_right = l.get_next_int();
				m_map_data.localsize_bottom = l.get_next_int();
				break;
			}
		case mai_size:
			{
				Cmulti_line l = value;
				m_map_data.size_left = l.get_next_int();
				m_map_data.size_top = l.get_next_int();
				m_map_data.size_right = l.get_next_int();
				m_map_data.size_bottom = l.get_next_int();
				break;
			}
		case mai_theater:
			m_map_data.theater = value;
			break;
		default:
			return 1;
		}
		break;
	case sei_preview:
		switch (find_id(name, preview_code, pri_unknown))
		{
		case pri_size:
			{
				Cmulti_line l = value;
				m_preview_data.x = l.get_next_int();
				m_preview_data.y = l.get_next_int();
				m_preview_data.cx = l.get_next_int();
				m_preview_data.cy = l.get_next_int();
				break;
			};
		}
		break;
	case sei_preview_pack:
		m_preview_pack_data += value;
		break;
	}
	return 0;
}

bool Cmap_ts_ini_reader::is_valid() const
{
	return !(m_map_data.size_left || m_map_data.size_top || 
		m_map_data.size_right < 1 || m_map_data.size_bottom < 1||
		m_map_data.size_left > m_map_data.localsize_left ||
		m_map_data.size_top > m_map_data.localsize_top ||
		m_map_data.size_right < m_map_data.localsize_right ||
		m_map_data.size_bottom < m_map_data.localsize_bottom ||
		m_map_data.theater.empty() ||
		m_preview_data.x ||
		m_preview_data.y ||
		m_preview_data.cx < 0 ||
		m_preview_data.cy < 0);
}
