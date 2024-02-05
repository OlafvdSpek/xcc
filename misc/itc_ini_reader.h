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

class Ctileset_data
{
public:
	Ctileset_data();

	string m_fname;
	int m_count;
};

class Citc_ini_reader : public Cini_reader    
{
public:
	enum t_section_id {sei_unknown};
	enum t_tileset_id {tsi_fname, tsi_count, tsi_unknown};
	using t_list = map<int, Ctileset_data>;

	Citc_ini_reader();
	void erase();
	int process_section_start(const string& line);
	bool process_section() const;
	int process_key(const string& name, const string& value);
	bool is_valid() const;

	const t_list& get_list() const
	{
		return m_list;
	}
private:
	int m_current_tileset;
	t_section_id m_section;
	t_list m_list;
};
