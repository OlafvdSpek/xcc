#pragma once

#include <ostream>

class Cneat_key_list  
{
public:
	using t_key_map = map<string, string>;
	using t_key_list = list<t_key_map::iterator>;

	Cneat_key_list() = default;
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
