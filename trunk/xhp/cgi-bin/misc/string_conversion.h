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
void split_key(const string& key, string& name, string& value);

inline string n(bool v)
{
	return n(static_cast<int>(v));
};

inline void trim(string& s)
{
	ltrim(s);
	rtrim(s);
}
