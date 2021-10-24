#pragma once

#include "ini_reader.h"

class Cmap_data
{
public:
	string m_description;
	string m_cd = "0,1";
	int m_min_players = 0;
	int m_max_players = 0;
	string m_gamemode = "standard";
};

class Cpkt_ts_ini_reader : public Cini_reader  
{
public:
	enum t_section_id {sei_multi_maps, sei_unknown};
	enum t_map_id {mai_description, mai_cd, mai_minplayers, mai_maxplayers, mai_gamemode, mai_unknown};
	using t_map_list = map<string, Cmap_data>;

	void erase();
	int process_section_start(const string& line);
	bool process_section() const;
	int process_key(const string& name, const string& value);
	bool is_valid() const;
	void write_report(ostream&) const;

	const t_map_list& get_map_list() const
	{
		return m_map_list;
	}
private:
	string m_current_map;
	t_section_id m_section = sei_unknown;
	t_map_list m_map_list;
};
