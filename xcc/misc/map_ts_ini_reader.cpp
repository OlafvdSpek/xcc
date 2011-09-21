#include "stdafx.h"
#include <fstream>
#include "map_ts_ini_reader.h"
#include "multi_line.h"
#include "string_conversion.h"
#include "virtual_image.h"

static const char* section_code[] = {"basic", "map", "preview", "previewpack", "waypoints", "unknown"};
static const char* basic_code[] = {"name", "player", "multiplayeronly", "unknown"};
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
		case bai_multiplayeronly:
			m_basic_data.multiplayeronly = atoi(value.c_str());
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
	case sei_waypoints:
		m_waypoints_data[atoi(name.c_str())] = atoi(value.c_str());
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

int Cmap_ts_ini_reader::max_players() const
{
	int count = 0;
	for (int i = 0; i < 8; i++)
	{
		if (get_waypoints_data().count(i))
			count++;
	}
	return count;
}

void Cmap_ts_ini_reader::write_report(ostream& os, string fname, const Cmap_ts_encoder& encoder) const
{
	string path = Cfname(fname).get_path();
	string image_fname = Cfname(fname).get_ftitle();
	Cvirtual_image preview;
	preview.load(encoder.preview_pack().data(), m_preview_data.cx, m_preview_data.cy, 3, NULL);
	preview.save(path + image_fname + "_pv.png", ft_png);
	encoder.create_heightmap().save(path + image_fname + "_hm.png", ft_png);
	os << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"><link rel=stylesheet href=\"http://xccu.sourceforge.net/xcc.css\"><title>Map dump</title><table border=1>"
		<< "<tr><td>Name:<td>" << (get_basic_data().name.empty() ? Cfname(fname).get_ftitle() : get_basic_data().name)
		<< "<tr><td>Size:<td>" << get_map_data().size_right << " x " << get_map_data().size_bottom
		<< "<tr><td>Max players:<td>" << max_players()
		<< "<tr><td>Preview:<td><img src=" << image_fname << "_pv.png>"
		<< "<tr><td>Height map:<td><img src=" << image_fname << "_hm.png>"
		<< "</table>";
}