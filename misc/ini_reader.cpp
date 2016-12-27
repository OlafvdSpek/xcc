#include "stdafx.h"
#include "ini_reader.h"

#include "string_conversion.h"
#include "virtual_tfile.h"

Cini_reader::Cini_reader()
{
	m_fast = false;
	m_lower_case = true;
	m_skip_errors = false;
}

int Cini_reader::find_id(const string& s, const char* t[], int count)
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

int Cini_reader::process(const byte* s, int cb_s)
{
	return process(Cvirtual_binary(s, cb_s));
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

int Cini_reader::process_line(string line)
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
			return process_section_start(m_lower_case ? to_lower_copy(line) : line);
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
						string name = line.substr(first_non_ws, last_non_ws - first_non_ws + 1);
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

