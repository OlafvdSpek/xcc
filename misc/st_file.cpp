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
#include <fstream>
#include "st_file.h"

bool Cst_file::is_valid() const
{
	int size = get_size();
	if (2 > size)
		return false;
	const unsigned __int16* r = get_index();
	int o1 = *r++;
	if (o1 < 2 || o1 > size)
		return false;
	int ol = o1;
	const void* r_end = data() + o1;
	while (r < r_end)
	{
		int o = *r++;
		if (o < ol || o > size || data()[o - 1])
			return false;
		ol = o;
	}
	return ol + 1 == size && !data()[ol];
}

ostream& Cst_file::extract_as_text(ostream& os) const
{
	for (int i = 0; i < get_c_strings(); i++)
		os << get_string(i) << endl;
	return os;
}

