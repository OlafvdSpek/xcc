#pragma once

#include <string>
#include <windows.h>

using namespace std;

class Cfname
{
private:
	string path;
	string title;
	string ext;
public:
	const Cfname& operator=(const string&);
	bool exists() const;
	void make_path();
	void use_default_ext(const string&);
	void use_default_path(const string&);
	void set_ext(const string&);
	void set_path(const string&);
	void set_title(const string&);
	void expand();
	string get_all() const;
	string get_path() const;
	string get_fname() const;
	string get_ftitle() const;
	string get_fext() const;
	Cfname() = default;
	Cfname(const string&);

	operator string() const
	{
		return get_all();
	}
};

Cfname GetModuleFileName(HMODULE hModule = 0);
bool fname_filter(const string& fname, const string& filter);
int create_dir(const string&  dir);
void create_deep_dir(string dir, const string& name);
int delete_file(string fname);
int copy_file(string s, string d);
int move_file(string s, string d);
string get_temp_fname(string path);
string get_temp_path();
string get_temp_fname();
string operator+(const string& a, const Cfname& b);
