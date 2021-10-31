#pragma once

#include <virtual_binary.h>

class Cini_reader  
{
public:
	static int find_id(string_view, span<const char*>, int count);
	int process(const Cvirtual_binary);
	int process_line(string);
	virtual int process_section_start(string_view) = 0;
	virtual bool process_section() const = 0;
	virtual int process_key(string_view, string_view) = 0;
	virtual void process_section_end();
	void fast(bool);
	void lower_case(bool);
	void skip_errors(bool);
protected:
	bool m_fast = false;
	bool m_lower_case = true;
	bool m_section_open;
	bool m_skip_errors = false;
};
