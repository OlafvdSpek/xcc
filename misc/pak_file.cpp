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

#include "stdafx.h"
#include "pak_file.h"

#include "string_conversion.h"

void Cpak_file::close()
{
	m_index.clear();
	Ccc_file_small::close();
}

bool Cpak_file::is_valid()
{
	int size = get_size();
	if (5 > size)
		return false;
	const byte* r = data();
	int o1 = *reinterpret_cast<const __int32*>(r);
	if (o1 < 5 || o1 > size)
		return false;
	int ol = o1;
	const void* r_end = data() + o1;
	while (r < r_end)
	{
		int o = *reinterpret_cast<const __int32*>(r);
		r += 4;
		if (!o)
			return r - data() == o1;
		r += strlen(reinterpret_cast<const char*>(r)) + 1;
		if (o < ol || o > size)
			return false;
		ol = o;
	}
	return false;
}

int Cpak_file::post_open()
{
	if (!is_valid())
		return 1;
	const byte* r = data();
	int next_offset;
	do
	{
		t_index_entry e;
		e.offset = *reinterpret_cast<const __int32*>(r);
		r += 4;
		string name = reinterpret_cast<const char*>(r);
		r += name.length() + 1;
		next_offset = *reinterpret_cast<const __int32*>(r);
		e.size = (next_offset ? next_offset: get_size()) - e.offset;
		m_index[to_lower_copy(name)] = e;
	}
	while (next_offset);
	return 0;
}