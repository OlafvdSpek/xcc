// ini_reader.cpp: implementation of the Cini_reader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ini_reader.h"
#include "string_conversion.h"
#include "virtual_tfile.h"

Cini_reader::Cini_reader()
{
	m_fast = false;
	m_skip_errors = false;
	m_lower_case = true;
}

int Cini_reader::find_id(string s, const char* t[], int count)
{
	for (int i = 0; i < count; i++)
	{
		if (s == t[i])
			break;
	}
	return i;
}

static bool is_section_start(const string &s)
{
	return s[0] == '[' && s[s.length() - 1] == ']';
}

static int split_key_now(const string& key, string& name, string& value)
{
	int i = key.find('=');
	if (i == string::npos)
		return 1;
	name = key.substr(0, i);
	value = key.substr(i + 1);
	rtrim(name);
	ltrim(value);
	return 0;
}

int Cini_reader::process(const byte* s, int cb_s)
{
	Cvirtual_tfile tf;
	tf.load_data(s, cb_s);
	int error = 0;
	int line = 0;
	while (!error && !tf.eof())
	{
		line++;
		error = process_line(tf.read_line());
	}
	return error;
}

int Cini_reader::process_line(string line)
{
	int comment_start = line.find(';');
	if (comment_start != string::npos)
		line = line.substr(0, comment_start);
	trim(line);
	if (line.empty())
		return 0;
	if (is_section_start(line))
	{
		line = line.substr(1, line.length() - 2);
		if (m_lower_case)
			return process_section_start(to_lower(line));
		return process_section_start(line);
	}
	if (!process_section())
		return 0;
	string name;
	string value;
	if (split_key_now(line, name, value))
		return !m_skip_errors;
	if (m_lower_case)
		return process_key(to_lower(name), value);
	return process_key(name, value);
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

