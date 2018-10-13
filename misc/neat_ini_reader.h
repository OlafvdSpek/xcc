#pragma once

#include <map>
#include <list>

#include "ini_reader.h"
#include "neat_key_list.h"

class Cneat_ini_reader : public Cini_reader
{
public:
	using t_section_map = map<string, Cneat_key_list>;
	using t_section_list = list<t_section_map::iterator>;

	Cneat_ini_reader();
	void erase();
	int process_section_start(const string& line);
	bool process_section() const;
	int process_key(const string& name, const string& value);
	void sub_section(string name, const Cneat_key_list& v);
	int write(ostream& os) const;
	int write(const string& name) const;

	Cneat_key_list& current_section()
	{
		return *m_current_section;
	}

	const t_section_map& get_section_map() const
	{
		return m_section_map;
	}

	const t_section_list& get_section_list() const
	{
		return m_section_list;
	}
private:
	t_section_list m_section_list;
	t_section_map m_section_map;

	Cneat_key_list* m_current_section;
};

Cneat_key_list sub_section(const Cneat_key_list& a, const Cneat_key_list& b);
