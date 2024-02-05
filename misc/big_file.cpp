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

#include "stdafx.h"
#include "big_file.h"

Cbig_file::Cbig_file():
	Ccc_file(false)
{
}

bool Cbig_file::is_valid()
{
	if (get_size() < sizeof(t_big_header))
		return false;
	t_big_header header;
	seek(0);
	if (read(&header, sizeof(t_big_header))
		|| header.id != big_id && header.id != big4_id
		|| header.size != get_size()
		|| header.c_files() < 0
		|| header.cb_header() < sizeof(t_big_header))
		return false;
	return true;
}

int Cbig_file::post_open()
{
	m_index.clear();
	m_old_index.clear();
	if (!is_valid())
		return 1;
	t_big_header header;
	seek(0);
	if (int error = read(&header, sizeof(t_big_header)))
		return error;
	Cvirtual_binary index;
	if (data() && vdata().size() < header.cb_header())
		return 0;
	if (int error = read(index.write_start(header.cb_header() - sizeof(t_big_header)), header.cb_header() - sizeof(t_big_header)))
		return error;
	int size = header.c_files();
	m_old_index.reserve(size);
	const byte* r = index.data();
	while (size--)
	{
		t_big_index_entry e = *reinterpret_cast<const t_big_index_entry*>(r);
		r += sizeof(t_big_index_entry);
		e.offset = reverse(e.offset);
		e.size = reverse(e.size);
		string name = reinterpret_cast<const char*>(r);
		m_index[name] = e;
		m_old_index.push_back(name);
		r += name.length() + 1;
	}
	return 0;
}