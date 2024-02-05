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

#include "cc_file_small.h"

class Ctext_file : public Ccc_file_small
{
public:
	bool is_valid() const
	{
		if (!get_size())
			return false;
		const byte* data = get_data();
		int cb_data = min<int>(get_size(), 16 << 10);
		for (int i = 0; i < cb_data; i++)
		{
			byte c = data[i];
			if (c != 0x09 && c != 0x0d && c != 0x0a && c < 0x20)
			{
				switch (get_size())
				{
				case 351263:
					// TS: g_knoll.map
					if (i == 1919 && c == 0x05)
						break;
					else
						return false;
				default:
					return false;
				}
			}
		}
		return true;
	}
};
