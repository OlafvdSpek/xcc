#pragma once

#include <boost/noncopyable.hpp>
#include <windows.h>

class Creg_key : boost::noncopyable
{
public:
	Creg_key() = default;
	Creg_key(HKEY, const string& name, REGSAM sam_desired);
	Creg_key(const Creg_key&, const string& name, REGSAM sam_desired);
	~Creg_key();
	LONG create(HKEY key, const string& name);
	LONG open(HKEY, const string& name, REGSAM sam_desired);
	LONG open(const Creg_key&, const string& name, REGSAM sam_desired);
	LONG close();
	LONG query_value(const string& name, string& value);
	string query_value(const string& name);
	LONG set_value(const string& name, const string& value);
private:
	HKEY m_h = NULL;
};
