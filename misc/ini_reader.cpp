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
#include "ini_reader.h"

#include "string_conversion.h"
#include "virtual_tfile.h"

int Cini_reader::find_id(string_view s, span<const char*> t, int count)
{
	int i = 0;
	while (i < count && t[i] != s)
		i++;
	return i;
}

static int split_key_now(const string& key, string& name, string& value)
{
	int i = key.find('=');
	if (i == string::npos)
		return 1;
	name = trim_copy(key.substr(0, i));
	value = trim_copy(key.substr(i + 1));
	return 0;
}

int Cini_reader::process(const Cvirtual_binary s)
{
	Cvirtual_tfile tf;
	tf.load_data(s);
	int error = 0;
	int line = 0;
	m_section_open = false;
	while ((!error || m_skip_errors) && !tf.eof())
	{
		line++;
		error = process_line(tf.read_line(true));
	}
	if (m_section_open)
		process_section_end();
	return error;
}

int Cini_reader::process_line(string_view line)
{
	size_t i = 0;
	int first_non_ws;
	int last_non_ws;
	while (i < line.length())
	{
		switch (line[i])
		{
		case '\t':
		case ' ':
			break;
		case ';':
			return 0;
		case '=':
			return 1;
		case '[':
			first_non_ws = ++i;
			last_non_ws = line.find(']', i);
			if (last_non_ws == string::npos)
				return 1;
			if (m_section_open)
				process_section_end();
			m_section_open = true;
			line = line.substr(first_non_ws, last_non_ws - first_non_ws);
			return process_section_start(m_lower_case ? to_lower_copy(string(line)) : line);
		default:
			if (!process_section())
				return 0;
			first_non_ws = last_non_ws = i++;
			while (i < line.length())
			{
				switch (line[i])
				{
				case '\t':
				case ' ':
					break;
				case ';':
					return 1;
				case '=':
					{
						string name = string(line.substr(first_non_ws, last_non_ws - first_non_ws + 1));
						if (m_lower_case)
							boost::to_lower(name);
						i++;
						while (i < line.length())
						{
							switch (line[i])
							{
							case '\t':
							case ' ':
								break;
							case ';':
								i = line.length();
								continue;
							default:
								first_non_ws = last_non_ws = i++;
								while (i < line.length())
								{
									switch (line[i])
									{
									case '\t':
									case ' ':
										break;
									case ';':
										i = line.length();
										continue;
									default:
										last_non_ws = i;
									}
									i++;
								}
								return process_key(name, line.substr(first_non_ws, last_non_ws - first_non_ws + 1));
							}
							i++;

						}
						return process_key(name, "");
					}
				default:
					last_non_ws = i;
				}
				i++;
			}
			return 1;
		}
		i++;
	}
	return 0;
}

void Cini_reader::process_section_end()
{
}

void Cini_reader::fast(bool v)
{
	m_fast = v;
}

void Cini_reader::lower_case(bool v)
{
	m_lower_case = v;
}

void Cini_reader::skip_errors(bool v)
{
	m_skip_errors = v;
}

