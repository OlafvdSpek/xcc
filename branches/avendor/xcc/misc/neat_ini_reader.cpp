// neat_ini_reader.cpp: implementation of the Cneat_ini_reader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <fstream>
#include "neat_ini_reader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cneat_ini_reader::Cneat_ini_reader()
{
	lower_case(false);
	skip_errors(true);
	m_current_section = NULL;
}

void Cneat_ini_reader::erase()
{
	m_section_map.clear();
	m_section_list.clear();
}

int Cneat_ini_reader::process_section_start(const string& line)
{
	t_section_map::iterator i = m_section_map.find(line);
	if (i == m_section_map.end())
	{
		m_section_map[line] = Cneat_key_list();
		i = m_section_map.find(line);
		m_section_list.push_back(i);
	}
	m_current_section = &i->second;
	return 0;
}

bool Cneat_ini_reader::process_section() const
{
	return m_current_section;
}

int Cneat_ini_reader::process_key(const string& name, const string& value)
{
	m_current_section->add_key(name, value);
	return 0;
}

int Cneat_ini_reader::write(const string& name) const
{
	ofstream f(name.c_str());
	for (t_section_list::const_iterator li = m_section_list.begin(); li != m_section_list.end(); li++)
	{
		t_section_map::const_iterator mi = *li;
		f << "[" + mi->first + "]" << endl;
		mi->second.write(f);
		f << endl;
	}
	return f.fail();
}