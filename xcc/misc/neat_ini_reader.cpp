#include "stdafx.h"
#include <fstream>
#include "neat_ini_reader.h"

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

int Cneat_ini_reader::write(ostream& os) const
{
	for (t_section_list::const_iterator li = m_section_list.begin(); li != m_section_list.end(); li++)
	{
		t_section_map::const_iterator mi = *li;
		if (mi->second.get_key_map().size())
		{
			os << "[" + mi->first + "]" << endl;
			mi->second.write(os);
			os << endl;
		}
	}
	return os.fail();
}

int Cneat_ini_reader::write(const string& name) const
{
	ofstream f(name.c_str());
	return write(f);
}

void Cneat_ini_reader::sub_section(string name, const Cneat_key_list& v)
{
	t_section_map::iterator i = m_section_map.find(name);
	Cneat_key_list a = ::sub_section(i == m_section_map.end() ? Cneat_key_list() : i->second, v);
	const Cneat_key_list::t_key_map& akm = a.get_key_map();
	process_section_start(name);
	m_section_map[name] = a; // .erase();
	return;
	for (Cneat_key_list::t_key_map::const_iterator j = akm.begin(); j != akm.end(); j++)
	{
		process_key(j->first, j->second);
	}
}

Cneat_key_list sub_section(const Cneat_key_list& a, const Cneat_key_list& b)
{
	Cneat_key_list r;
	BOOST_FOREACH(auto& i, a.get_key_list())
	{
		auto j = find_ptr(b.get_key_map(), i->first);
		if (!j || *j != i->second)
			r.add_key(i->first, i->second);
	}
	BOOST_FOREACH(auto& i, b.get_key_list())
	{
		if (!a.get_key_map().count(i->first))
			r.add_key(i->first, "");
	}
	return r;
}