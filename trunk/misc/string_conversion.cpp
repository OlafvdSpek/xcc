#include "stdafx.h"
#include "string_conversion.h"

bool atob(string s)
{
	return s == "true" || s == "yes";
}

string btoa(bool v)
{
	return v ? "yes" : "no";
}

char* make_c_str(const char* s)
{
	char* v = new char[strlen(s) + 1];
	return strcpy(v, s);
}

string n(unsigned int v)
{
	if (!v)
		return "0";
	string s;
	while (v)
	{
		s = char(v % 10 + 48) + s;
		v /= 10;
	}
	return s;
}

string n(int v)
{
	if (!v)
		return "0";
	string s;
	bool negative = false;
	if (v < 0)
	{
		negative = true;
		v = -v;
	}
	while (v)
	{
		s = char(v % 10 + 48) + s;
		v /= 10;
	}
	if (negative)
		s = "-" + s;
	return s;
}

string n(__int64 v)
{
	if (!v)
		return "0";
	string s;
	bool negative = false;
	if (v < 0)
	{
		negative = true;
		v = -v;
	}
	while (v)
	{
		s = char(v % 10 + 48) + s;
		v /= 10;
	}
	if (negative)
		s = "-" + s;
	return s;
}

string swsl(int l, string s)
{
	while (s.length()<l)
		s = ' '+ s;
	return s;
}

string swsr(int l, string s)
{
	while (s.length() < l)
		s = s + ' ';
	return s;
}

string nwzl(int l, unsigned int v)
{

	string s = n(v);
	while (s.length() < l)
		s = '0' + s;
	return s;
}

string nwsl(int l, unsigned int v)
{
	return swsl(l, n(v));
}

string nh(int l, __int64 v)
{
	string s;
	int w;
	while (l)
	{
		w = v & 0xf;
		if (w > 9)
			w += 7;
		s = char(w + 48) + s;
		v >>= 4;
		l--;
	}
	return s;
}

bool is_white(char v)
{
	switch (v)
	{
	case '\t':
	case '\n':
	case '\r':
	case ' ':
		return true;
	default:
		return false;
	}
}

void ltrim(string& s)
{
	while (!s.empty() && is_white(s[0]))
		s.erase(0, 1);
}

void rtrim(string& s)
{
	while (!s.empty() && is_white(s[s.length() - 1]))
		s.erase(s.length() - 1, 1);
}

string to_lower(const string& s)
{
	string r;
	for (int i = 0; i < s.length(); i++)
		r += tolower(s[i]);
	return r;
}

string to_normal(string s)
{
	if (!s.empty())
		s[0] = toupper(s[0]);
	for (int i = 1; i < s.length(); i++)
		s[i] = tolower(s[i]);
	return s;
}

string to_upper(const string& s)
{
	string r;
	for (int i = 0; i < s.length(); i++)
		r += toupper(s[i]);
	return r;
}

string nwp(int l, unsigned int v)
{
	string r;
	string s = n(v);
	while (1)
	{		
		int l = s.length();
		if (l > 3)
		{
			r = '.' + s.substr(l - 3, 3) + r;
			s.erase(l - 3, 3);
		}
		else
		{
			r = s + r;
			break;
		}

	}
	return swsl(l, r);
}

void split_key(const string& key, string& name, string& value)
{
	int i = key.find('=');
	if (i == string::npos)
	{
		name = key;
		value.erase();
	}
	else
	{
		name = key.substr(0, i);
		value = key.substr(i + 1);
	}
}

string tabs2spaces(const string& v)
{
	string r;
	for (int i = 0; i < v.length(); i++)
	{
		char c = v[i];
		if (c == '\t')
		{
			do
				r += ' ';
			while (r.length() & 3);
		}
		else
			r += c;
	}
	return r;
}

bool string_equal_i(const char* a, const char* b)
{
	while (1)
	{
		if (*a != *b && tolower(*a) != tolower(*b))
			return false;
		if (!*a)
			return true;
		a++;
		b++;
	}
}

bool string_equal_ip(const char* a, const char* b)
{
	while (1)
	{
		if (!*b)
			return true;
		if (*a != *b && tolower(*a) != tolower(*b))
			return false;
		a++;
		b++;
	}
}
