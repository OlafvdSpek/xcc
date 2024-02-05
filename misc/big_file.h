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

#pragma once

#include <vector>
#include "cc_file.h"
#include "cc_structures.h"

class Cbig_file : public Ccc_file  
{
public:
	typedef map<string, t_big_index_entry> t_index;
	typedef vector<string> t_old_index;

	int get_c_files() const
	{
		return m_index.size();
	}

	string get_name(int index) const
	{
		return m_old_index[index];
	}

	int get_offset(const string& name) const
	{
		return m_index.find(name)->second.offset;
	}

	using Ccc_file::get_size;

	int get_size(const string& name) const
	{
		return find_ref(m_index, name).size;
	}

	const t_index& index() const
	{
		return m_index;
	}

	bool is_valid();
	int post_open();
	Cbig_file();
private:
	t_index m_index;
	t_old_index m_old_index;
};
