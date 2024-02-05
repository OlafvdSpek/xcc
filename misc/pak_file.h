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

#include <map>
#include "cc_file_small.h"

class Cpak_file : public Ccc_file_small
{
public:
	void close();
	bool is_valid();
    int post_open();

	int get_c_files() const
	{
		return m_index.size();
	}

	string get_name(int index) const
	{
		return next(m_index.begin(), index)->first;
	}

	int get_offset(const string& name) const
    {
        return find_ref(m_index, name).offset;
    }

    int get_size() const
	{
		return Ccc_file_small::get_size();
	}

	int get_size(const string& name) const
    {
        return find_ref(m_index, name).size;
    }
private:
	struct t_index_entry
	{
		int offset;
		int size;
	};

	using t_index = map<string, t_index_entry>;
	t_index m_index;
};
