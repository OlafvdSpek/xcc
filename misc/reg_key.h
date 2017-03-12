#pragma once

#include <boost/noncopyable.hpp>
#include <string>
#include <windows.h>

class Creg_key : boost::noncopyable
{
public:
	Creg_key() = default;
	Creg_key(HKEY, const std::string& name, REGSAM sam_desired);
	Creg_key(const Creg_key&, const std::string& name, REGSAM sam_desired);
	~Creg_key();
	LONG create(HKEY key, const std::string& name);
	LONG open(HKEY, const std::string& name, REGSAM sam_desired);
	LONG open(const Creg_key&, const std::string& name, REGSAM sam_desired);
	LONG close();
	LONG query_value(const std::string& name, std::string& value);
	std::string query_value(const std::string& name);
	LONG set_value(const std::string& name, const std::string& value);
private:
	HKEY m_h = NULL;
};
