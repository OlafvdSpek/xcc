// neat_key_list.h: interface for the Cneat_key_list class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEAT_KEY_LIST_H__E2E4BEC3_9322_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_NEAT_KEY_LIST_H__E2E4BEC3_9322_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ostream>
#include <map>
#include <list>
#include <string>

using namespace std;

class Cneat_key_list  
{
public:
	typedef map<string, string> t_key_map;
	typedef list<t_key_map::iterator> t_key_list;

	Cneat_key_list();
	Cneat_key_list(const Cneat_key_list& v);
	const Cneat_key_list& operator=(const Cneat_key_list& v);
	void add_key(const string& name, const string& value);
	void erase();
	int write(ostream& os) const;

	const t_key_list& get_key_list() const
	{
		return m_key_list;
	}

	const t_key_map& get_key_map() const
	{
		return m_key_map;
	}
private:
	t_key_map m_key_map;
	t_key_list m_key_list;
};

#endif // !defined(AFX_NEAT_KEY_LIST_H__E2E4BEC3_9322_11D4_B606_0000B4936994__INCLUDED_)
