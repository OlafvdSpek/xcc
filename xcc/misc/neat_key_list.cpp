#include "stdafx.h"
#include "neat_key_list.h"

Cneat_key_list::Cneat_key_list()
{
}

Cneat_key_list::Cneat_key_list(const Cneat_key_list& v)
{
	*this = v;
}

const Cneat_key_list& Cneat_key_list::operator=(const Cneat_key_list& v)
{
	erase();
	for (t_key_list::const_iterator li = v.m_key_list.begin(); li != v.m_key_list.end(); li++)
	{
		t_key_map::const_iterator mi = *li;
		add_key(mi->first, mi->second);
	}
	return *this;
}

void Cneat_key_list::add_key(const string& name, const string& value)
{
	auto i = m_key_map.find(name);
	if (i == m_key_map.end())
	{
		m_key_map[name] = value;
		i = m_key_map.find(name);
		m_key_list.push_back(i);
	}
	else
		i->second = value;
}

void Cneat_key_list::erase()
{
	m_key_map.clear();
	m_key_list.clear();
}

int Cneat_key_list::write(ostream& os) const
{
	for (t_key_list::const_iterator li = m_key_list.begin(); li != m_key_list.end(); li++)
	{
		t_key_map::const_iterator mi = *li;
		os << mi->first << "=" << mi->second << endl;
	}
	return 0;
}