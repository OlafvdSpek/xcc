/*
    XCC Utilities and Library
    Copyright (C) 2003  Olaf van der Spek  <olafvdspek@gmail.com>

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

#include "big_file.h"
#include "cc_structures.h"
#include "file32.h"

class Cbig_edit  
{
public:
	void close();
	void clear();
	int compact();
	void erase(const string& name);
	int insert(const string& name, Cvirtual_binary d);
	int open(const string& name);
	int write_index();
private:
	using t_block_map = map<int, t_big_index_entry*>;

	t_block_map block_map();
	int cb_header() const;
	int new_block(int size);

	Cfile32 m_f;
	t_big_header m_header;
	Cbig_file::t_index m_index;
};
