#pragma once

#include "ini_reader.h"

class Cnull_ini_reader : public Cini_reader  
{
public:
	Cnull_ini_reader()
	{
		mc_sections = 0;
	}

	int process_section_start(const string& line)
	{
		mc_sections++;
		return 0;
	}

	bool process_section() const
	{
		return true;
	}
	
	int process_key(const string& name, const string& value)
	{
		return 0;
	}

	bool is_valid() const
	{
		return mc_sections;
	}
private:
	int mc_sections;
};
