// xstring.cpp: implementation of the xstring class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xstring.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static void ltrim(string &s)
{
	while (!s.empty())
	{
		if (s[0] == 0x20)
			s.erase(0, 1);
		else
			break;
	}
}

static void rtrim(string &s)
{
	while (!s.empty())
	{
		if (s[s.length() - 1] == 0x20)
			s.erase(s.length() - 1, 1);
		else
			break;
	}
}

static void tolower(string &s)
{
	for (long i = 0; i < s.length(); i++)
		s[i] = tolower(s[i]);
}

xstring::xstring()
{
}

xstring::xstring(const string &s)
{
	string::operator=(s);
}

xstring& xstring::ltrim()
{
	::ltrim(*this);
	return *this;
}

xstring& xstring::rtrim()
{
	::rtrim(*this);
	return *this;
}

xstring& xstring::tolower()
{
	::tolower(*this);
	return *this;
}
