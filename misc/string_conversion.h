#pragma once

#include <string>
#include "vartypes.h"

using namespace std;

bool atob(string s);
string btoa(bool v);
bool is_white(char v);
string n(unsigned int v);
string n(int v);
string n(__int64 v);
string swsl(int l, string s);
string swsr(int l, string s);
string nwp(int l, unsigned int v);
string nwsl(int l, unsigned int v);
string nwzl(int l, unsigned int v);
string nh(int l, __int64 v);
void ltrim(string& s);
void rtrim(string& s);
string to_lower(const string& s);
string to_normal(string s);
string to_upper(const string& s);
void split_key(const string& key, string& name, string& value);
bool string_equal_i(const char* a, const char* b);
bool string_equal_ip(const char* a, const char* b);
string tabs2spaces(const string& v);

inline string n(__int32 v)
{
	return n(static_cast<int>(v));
}

inline string n(unsigned __int32 v)
{
	return n(static_cast<unsigned int>(v));
}

inline bool string_equal_i(const string& a, const string& b)
{
	return string_equal_i(a.c_str(), b.c_str());
}

inline bool string_equal_ip(const string& a, const string& b)
{
	return string_equal_ip(a.c_str(), b.c_str());
}

inline void trim(string& s)
{
	ltrim(s);
	rtrim(s);
}