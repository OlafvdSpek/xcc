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

class Cst_file : public Ccc_file_small
{
public:
	ostream& extract_as_text(ostream&) const;
	bool is_valid() const;

	int get_c_strings() const
	{
		return get_offset(0) >> 1;
	}

	const unsigned __int16* get_index() const
	{
		return reinterpret_cast<const unsigned __int16*>(data());
	}

	int get_offset(int i) const
	{
		return get_index()[i];
	}

	const char* get_string(int i) const
	{
		return reinterpret_cast<const char*>(data() + get_offset(i));
	}
};
