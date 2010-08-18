#pragma once

class Cmulti_line
{
public:
	Cmulti_line();
	Cmulti_line(const char* is);
	Cmulti_line(const string &is);
	int get_next_int(const char separator = ',');
	int get_next_int(const string& separator);
	string get_next_line(const char separator = ',', bool remove_ws = true);
	string get_next_line(const string& separator, bool remove_ws = true);

	bool empty() const
	{
		return s.empty();
	};
private:
	string s;
};
