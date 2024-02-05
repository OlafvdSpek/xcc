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
#include "pkt_ts_ini_reader.h"

#include "multi_line.h"
#include "string_conversion.h"
#include "xste.h"

static const char* section_code[] = {"multimaps", "unknown"};
static const char* map_code[] = {"description", "cd", "minplayers", "maxplayers", "gamemode", "unknown"};

void Cpkt_ts_ini_reader::erase()
{
	m_map_list.clear();
}

int Cpkt_ts_ini_reader::process_section_start(string_view line)
{
	m_section = t_section_id(find_id(line, section_code, sei_unknown));
	if (m_section != sei_unknown)
		return 0;
	if (!m_map_list.count(line))
		return 1;
	m_current_map = line;
	return 0;
}

bool Cpkt_ts_ini_reader::process_section() const
{
	return true;
}

int Cpkt_ts_ini_reader::process_key(string_view name, string_view value)
{
	switch (m_section)
	{
	case sei_multi_maps:
		m_map_list[(to_lower_copy(string(value)))];
		break;
	case sei_unknown:
		switch (find_id(name, map_code, mai_unknown))
		{
		case mai_description:
			m_map_list[m_current_map].m_description = value;
			break;			
		case mai_cd:
			m_map_list[m_current_map].m_cd = value;
			break;
		case mai_minplayers:
			m_map_list[m_current_map].m_min_players = to_int(value);
			break;
		case mai_maxplayers:
			m_map_list[m_current_map].m_max_players = to_int(value);
			break;
		case mai_gamemode:
			m_map_list[m_current_map].m_gamemode = value;
			break;			
		default:
			return 1;
		}
	}
	return 0;
}

bool Cpkt_ts_ini_reader::is_valid() const
{
	return m_map_list.size();
}

void Cpkt_ts_ini_reader::write_report(ostream& os) const
{
	CXSTE xste;
	bool xste_available = !xste.open(game_ra2_yr);
	os << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"><link rel=stylesheet href=\"http://xccu.sourceforge.net/xcc.css\"><title>PKT dump</title><table border=1>"
		<< "<tr><th>Name<th>Description<th>Gamemode<th>Preview";
	for (auto& i : m_map_list)
	{
		/*
		bool skip = true;
		Cmulti_line l = i->second.m_gamemode;
		while (!l.empty())
		{			
			if (l.get_next_line(',') == "standard")
			{
				skip = false;
				break;
			}
		}
		if (skip) 
			continue;
		*/
		string description = i.second.m_description;
		if (xste_available)
		{
			Ccsf_file& csf_f = xste.csf_f();
			if (csf_f.has_name(to_lower_copy(description)))
				description = csf_f.get_converted_value(to_lower_copy(description));
		}
		os << "<tr><td><a href=" << i.first << ".html>" << i.first << "</a><td>" << description << "<td>" << i.second.m_gamemode << "<td><img src=" << i.first << "_pv.png>";
		// page += "\"" + i->first + "\", " + "\"" + description + "\",\n";
	}
	os << "</table>";
	// os << page;
}
