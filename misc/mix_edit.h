/*
    XCC Utilities and Library
    Copyright (C) 2002  Olaf van der Spek  <olafvdspek@gmail.com>

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

#include "cc_structures.h"
#include "file32.h"
#include "mix_file.h"

class Cmix_edit  
{
public:
	static int cb_header(int size);
	void close();
	void clear();
	int compact();
	void erase(int id);
	void erase(const string& name);
	int id(const string& name) const;
	int insert(const string& name, Cvirtual_binary d);
	int open(const string& name);
	int write_index();
private:
	using t_block_map = map<int, t_mix_index_entry*>;

	t_block_map block_map();
	int new_block(int size);

	Cfile32 m_f;
	t_game m_game;
	map<int, t_mix_index_entry> m_index;
};
