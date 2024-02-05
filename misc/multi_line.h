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

#include <string>

class Cmulti_line
{
public:
	Cmulti_line() = default;
	Cmulti_line(const std::string&);
	int get_next_int(const char separator = ',');
	int get_next_int(const std::string& separator);
	std::string get_next_line(const char separator = ',', bool remove_ws = true);
	std::string get_next_line(const std::string& separator, bool remove_ws = true);

	bool empty() const
	{
		return s.empty();
	};
private:
	std::string s;
};
