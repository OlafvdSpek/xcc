#pragma once

#include <string>

class Cmulti_line
{
public:
	Cmulti_line();
	Cmulti_line(const char* is);
	Cmulti_line(const std::string &is);
	int get_next_int(const char separator = ',');
	int get_next_int(const std::string& separator);
	std::string get_next_line(const char separator = ',', bool remove_ws = true);
	std::string get_next_line(const std::string& separator, bool remove_ws = true);

	bool empty() const
	{
		return s.empty();
	};
private:
	std::string s;
};
