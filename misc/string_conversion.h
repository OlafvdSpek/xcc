#pragma once

#include <string>
#include "vartypes.h"

using namespace std;

int a2ip(const string& s);
string ip2a(int v);
int get_net_mask(int v);
int get_net_part(int v);
bool atob(string s);
string btoa(bool v);
string js_encode(const string&);
string n(unsigned int v);
string n(int v);
string n(__int64 v);
string swsl(int l, string s);
string swsr(int l, string s);
string nwp(int l, unsigned int v);
string nwsl(int l, unsigned int v);
string nwzl(int l, unsigned int v);
string nh(int l, __int64 v);
void split_key(const string& key, string& name, string& value);
string tabs2spaces(const string& v);
string time2a(time_t v);
string trim_field(const string&);
string trim_text(const string&);
