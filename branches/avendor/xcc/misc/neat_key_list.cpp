// neat_key_list.cpp: implementation of the Cneat_key_list class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "neat_key_list.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cneat_key_list::Cneat_key_list()
{
}

void Cneat_key_list::add_key(const string& name, const string& value)
{
	t_key_map::iterator i = m_key_map.find(name);
	if (i == m_key_map.end())
	{
		m_key_map[name] = value;
		i = m_key_map.find(name);
		m_key_list.push_back(i);
	}
	else
		i->second = value;
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