#pragma once

#include "ini_reader.h"

class Ctileset_data
{
public:
	Ctileset_data();

	string m_fname;
	int m_count;
};

class Citc_ini_reader: public Cini_reader    
{
public:
	enum t_section_id {sei_unknown};
	enum t_tileset_id {tsi_fname, tsi_count, tsi_unknown};
	typedef map<int, Ctileset_data> t_list;

	Citc_ini_reader();
	void erase();
	int process_section_start(const string& line);
	bool process_section() const;
	int process_key(const string& name, const string& value);
	bool is_valid() const;

	const t_list& get_list() const
	{
		return m_list;
	}
private:
	int m_current_tileset;
	t_section_id m_section;
	t_list m_list;
};
