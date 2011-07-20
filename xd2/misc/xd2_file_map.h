#pragma once

#include "xif_key.h"
#include "xif_key_r.h"

template<class T>
class Cxd2_file_map  
{
public:
	typedef map<string, T> t_map;

	void load(const Cxif_key_r& key)
	{
		m_map.clear();
		BOOST_FOREACH(auto& i, key.keys())
			load_entry(i.second);
	}

	Cxif_key save() const
	{
		Cxif_key key;
		BOOST_FOREACH(auto& i, m_map)
			key.open_key_write() = save(i);
		return key;
	}

	void erase(const string& name)
	{
		m_map.erase(name);
	}
	
	const T& operator[](const string& name) const
	{
		return m_map.find(name)->second;
	}
	
	bool has(const string& name) const
	{
		return m_map.find(name) != m_map.end();
	}

	const t_map& map() const
	{
		return m_map;
	}
	
	void set(const string& name, const T& d)
	{
		m_map[name] = d;
	}
private:
	enum
	{
		vi_name,
		vi_value,
	};

	void load_entry(const Cxif_key_r& key)
	{
		m_map[key.get_value_string(vi_name)] = T(key.get_key(vi_value));
	}

	static Cxif_key save(typename t_map::const_reference i)
	{
		Cxif_key key;
		key.set_value_string(vi_name, i.first);
		key.open_key_write(vi_value) = i.second.save();
		return key;
	}

	t_map m_map;
};

void Cxd2_file_map<Cvirtual_binary>::load_entry(const Cxif_key_r& key)
{
	m_map[key.get_value_string(vi_name)] = key.get_value(vi_value).get_vdata();
}

Cxif_key Cxd2_file_map<Cvirtual_binary>::save(Cxd2_file_map<Cvirtual_binary>::t_map::const_reference i)
{
	Cxif_key key;
	key.set_value_string(vi_name, i.first);
	key.set_value_binary(vi_value, i.second);
	return key;
}

typedef Cxd2_file_map<Cvirtual_binary> Cxd2_data_map;
