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

#pragma once

#include "ini_reader.h"

class Cmap_data
{
public:
	string m_description;
	string m_cd = "0,1";
	int m_min_players = 0;
	int m_max_players = 0;
	string m_gamemode = "standard";
};

class Cpkt_ts_ini_reader : public Cini_reader  
{
public:
	enum t_section_id {sei_multi_maps, sei_unknown};
	enum t_map_id {mai_description, mai_cd, mai_minplayers, mai_maxplayers, mai_gamemode, mai_unknown};
	using t_map_list = map<string, Cmap_data, less<>>;

	void erase();
	int process_section_start(string_view) override;
	bool process_section() const override;
	int process_key(string_view, string_view) override;
	bool is_valid() const;
	void write_report(ostream&) const;

	const t_map_list& get_map_list() const
	{
		return m_map_list;
	}
private:
	string m_current_map;
	t_section_id m_section = sei_unknown;
	t_map_list m_map_list;
};
