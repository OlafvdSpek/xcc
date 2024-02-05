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
#include "big_file_write.h"

#include "cc_structures.h"

void Cbig_file_write::insert(const string& name, const Cvirtual_binary& d)
{
	m_index[name] = d;
}

void Cbig_file_write::clear()
{
	m_index.clear();
}

Cvirtual_binary Cbig_file_write::write()
{
	int cb_header = sizeof(t_big_header);
	int cb_d = sizeof(t_big_header);
	for (auto& i : m_index)
	{
		cb_header += sizeof(t_big_index_entry) + i.first.length() + 1;
		cb_d += sizeof(t_big_index_entry) + i.first.length() + 1 + i.second.size();
	}
	Cvirtual_binary d;
	byte* w = d.write_start(cb_d);
	t_big_header& header = *reinterpret_cast<t_big_header*>(w);
	header.id = big_id;
	header.size = d.size();
	header.mc_files = reverse(m_index.size());
	header.mcb_header = reverse(cb_header);
	byte* w2 = w + cb_header;
	w += sizeof(t_big_header);
	for (auto& i : m_index)
	{
		t_big_index_entry& e = *reinterpret_cast<t_big_index_entry*>(w);
		e.offset = reverse(w2 - d.data());
		e.size = reverse(i.second.size());
		w += sizeof(t_big_index_entry);
		memcpy(w, i.first.c_str(), i.first.length() + 1);
		w += i.first.length() + 1;
		w2 += i.second.read(w2);
	}
	assert(w2 == d.data_end());
	return d;
}
