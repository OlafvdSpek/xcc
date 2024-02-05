/*
    XCC Utilities and Library
    Copyright (C) 2004  Olaf van der Spek  <olafvdspek@gmail.com>

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
#include <vector>

class Circ_params
{
public:
	Circ_params(const std::string&);
	void clear();
	std::string read() const;
	const std::string& prefix() const;
	std::string prefix_nick() const;
	std::string prefix_user() const;
	std::string prefix_host() const;
	const std::string& operator[](size_t) const;
	int p_int(int i) const;
	void p(int i, const std::string&);
	void p(int i, int v);

	Circ_params() = default;

	int count() const
	{
		return m_params.size();
	}
private:
	std::string m_prefix;
	std::vector<std::string> m_params;
};
