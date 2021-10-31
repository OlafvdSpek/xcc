#pragma once

#include "ini_reader.h"

class Cnull_ini_reader : public Cini_reader  
{
public:
	int process_section_start(string_view) override
	{
		mc_sections++;
		return 0;
	}

	bool process_section() const override
	{
		return true;
	}
	
	int process_key(string_view, string_view) override
	{
		return 0;
	}

	bool is_valid() const 
	{
		return mc_sections;
	}
private:
	int mc_sections = 0;
};
