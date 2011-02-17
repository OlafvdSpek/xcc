#include "multi_line.h"

#include <boost/algorithm/string.hpp>

using namespace boost;

Cmulti_line::Cmulti_line()
{
}

Cmulti_line::Cmulti_line(const char* is)
{
	s = is;
}

Cmulti_line::Cmulti_line(const string &is)
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

