// multi_line.cpp: implementation of the Cmulti_line class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "multi_line.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

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

string Cmulti_line::get_next_line(const char separator)
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
	return r;
}

int Cmulti_line::get_next_int(const char separator)
{
	return atoi(get_next_line(separator).c_str());
}

string Cmulti_line::get_next_line(const string& separator)
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
	return r;
}