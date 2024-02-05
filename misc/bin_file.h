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

#include <cc_file_small.h>

class Cbin_file : public Ccc_file_small  
{
public:
	bool is_valid() const
	{
		if (get_size() != 8192)
			return false;
		const byte* p = data();
		for (int i = 0; i < 64 * 64; i++)
		{
			int v = *p++;
			int w = *p++;
			if (v > 0xd7 && v != 0xff || w > 64)
				return false;
		}
		return true;
	}
};
