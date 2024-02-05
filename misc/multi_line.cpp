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

#include "multi_line.h"

#include <boost/algorithm/string.hpp>

using namespace boost;

Cmulti_line::Cmulti_line(const string& is)
{
	s = is;
}

string Cmulti_line::get_next_line(const char separator, bool remove_ws)
{
	string r;
	int p = s.find(separator);
	if (p == string::npos)
	{
		r = s;
		s.erase();
	}
	else
	{
		r = s.substr(0, p);
		s.erase(0, p + 1);
	}
	if (remove_ws)
		trim(r);
	return r;
}

int Cmulti_line::get_next_int(const char separator)
{
	return atoi(get_next_line(separator, true).c_str());
}

string Cmulti_line::get_next_line(const string& separator, bool remove_ws)
{
	string r;
	int p = s.find(separator);
	if (p == string::npos)
	{
		r = s;
		s.erase();
	}
	else
	{
		r = s.substr(0, p);
		s.erase(0, p + separator.length());
	}
	if (remove_ws)
		trim(r);
	return r;
}

int Cmulti_line::get_next_int(const string& separator)
{
	return atoi(get_next_line(separator, true).c_str());
}
