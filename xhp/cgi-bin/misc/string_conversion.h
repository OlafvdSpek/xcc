#include <string>
#include "vartypes.h"

using namespace std;

int a2ip(const string& s);
string ip2a(int v);
int get_net_mask(int v);
int get_net_part(int v);
bool is_white(char v);
// char* make_c_str(const char* s);
string n(unsigned int v);
string n(int v);
string swsl(int l, string s);
string swsr(int l, string s);
string nwp(int l, int v);
string nwsl(int l, int v);
string nwzl(int l, int v);
string nh(int l, int v);
void ltrim(string& s);
void rtrim(string& s);
string to_lower(const string& s);
string to_upper(const string& s);
bool string_equal_i(const char* a, const char* b);
bool string_equal_ip(const char* a, const char* b);
void split_key(const string& key, string& name, string& value);

inline string n(bool v)
{
	return n(static_cast<int>(v));
};

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
