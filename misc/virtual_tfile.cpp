#include "stdafx.h"
#include "virtual_tfile.h"

void Cvirtual_tfile::load_data(const Cvirtual_binary s)
{
	m_data = s;
	pos = 0;
}

string Cvirtual_tfile::read_line()
{
	assert(data());
	const int first_non_ws = pos;
	int last_non_ws;
	while (pos < size())
	{
		switch (data()[pos++])
		{
		case '\r':
			last_non_ws = pos - 2;
			if (pos < size() && data()[pos] == '\n')
				pos++;
			return string(data() + first_non_ws, last_non_ws - first_non_ws + 1);
		case '\n':
			last_non_ws = pos - 2;
			return string(data() + first_non_ws, last_non_ws - first_non_ws + 1);
		}
	}
	last_non_ws = size() - 1;
	return string(data() + first_non_ws, last_non_ws - first_non_ws + 1);
}

string Cvirtual_tfile::read_line(bool remove_ws)
{
	if (!remove_ws)
		return read_line();
	assert(data());
	int first_non_ws;
	int last_non_ws;
	while (pos < size())
	{
		switch (data()[pos++])
		{
		case '\r':
			if (pos < size() && data()[pos] == '\n')
				pos++;
		case '\n':
			return "";
		case '\t':
		case ' ':
			break;
		default:
			first_non_ws = pos - 1;
			last_non_ws = pos - 2;
			while (pos < size())
			{
				switch (data()[pos++])
				{
				case '\r':
					if (pos < size() && data()[pos] == '\n')
						pos++;
				case '\n':
					return string(data() + first_non_ws, last_non_ws - first_non_ws + 1);
				case '\t':
				case ' ':
					break;
				default:
					last_non_ws = pos - 1;
				}
			}
			return string(data() + first_non_ws, last_non_ws - first_non_ws + 1);
		}
	}
	return "";
}