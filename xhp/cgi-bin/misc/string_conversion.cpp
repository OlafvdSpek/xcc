#include "stdafx.h"
#include "string_conversion.h"

int a2ip(const string& s)
{
	int r = 0;
	int l = 0;
	for (int i = 0; i < 3; i++)
	{
		int c = s.find('.', l);
		r = r << 8 | atoi(s.substr(l, c - l).c_str());
		l = c + 1;
	}
	r = r << 8 | atoi(s.substr(l).c_str());
	return r;
}

string ip2a(int v)
{
	return n(v >> 24 & 0xff) + '.' + n(v >> 16 & 0xff) + '.' + n(v >> 8 & 0xff) + '.' + n(v & 0xff);
}

int get_net_mask(int v)
{
	if (v & 0x80000000)
		return 0xffffff00;
	if (v & 0x40000000)
		return 0xffff0000;
	return 0xff000000;
}

int get_net_part(int v)
{
	return v & get_net_mask(v);
}

bool atob(string s)
{
	return s == "true" || s == "yes";
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

string nwzl(int l, int v)
{
	string s = n(v);
	while (s.length() < l)
		s = '0' + s;
	return s;
}

string nwsl(int l, int v)
{
	return swsl(l, n(v));
}

string nh(int l, int v)
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

void ltrim(string& s)
{
	while (!s.empty() && s[0] == ' ')
		s.erase(0, 1);
}

void rtrim(string& s)
{
	while (!s.empty() && s[s.length() - 1] == ' ')
		s.erase(s.length() - 1, 1);
}

string to_lower(const string& s)
{
	string r;
	for (int i = 0; i < s.length(); i++)
		r += tolower(s[i]);
	return r;
}

string to_upper(const string& s)
{
	string r;
	for (int i = 0; i < s.length(); i++)
		r += toupper(s[i]);
	return r;
}

string nwp(int l, int v)
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
		value = "";
	}
	else
	{
		name = key.substr(0, i);
		value = key.substr(i + 1);
	}
}