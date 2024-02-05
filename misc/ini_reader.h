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

#include <virtual_binary.h>

class Cini_reader  
{
public:
	static int find_id(string_view, span<const char*>, int count);
	int process(const Cvirtual_binary);
	int process_line(string_view);
	virtual int process_section_start(string_view) = 0;
	virtual bool process_section() const = 0;
	virtual int process_key(string_view, string_view) = 0;
	virtual void process_section_end();
	void fast(bool);
	void lower_case(bool);
	void skip_errors(bool);
protected:
	bool m_fast = false;
	bool m_lower_case = true;
	bool m_section_open;
	bool m_skip_errors = false;
};
