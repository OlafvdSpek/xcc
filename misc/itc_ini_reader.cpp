#include "stdafx.h"
#include "itc_ini_reader.h"

#include "string_conversion.h"

static const char* section_code[] = {"unknown"};
static const char* tileset_code[] = {"filename", "tilesinset", "unknown"};

Ctileset_data::Ctileset_data()
{
	m_count = 0;
}

Citc_ini_reader::Citc_ini_reader()
{
	m_section = sei_unknown;
}

void Citc_ini_reader::erase()
{
	m_list.clear();
}

int Citc_ini_reader::process_section_start(const string& line)
{
	m_section = static_cast<t_section_id>(find_id(line, section_code, sei_unknown));
	if (m_section != sei_unknown)
		return 0;
	for (int i = 0; i < 10000; i++)
	{
		if (line != "tileset" + nwzl(4, i))
			continue;
		m_current_tileset = i;
		return 0;
	}
	m_current_tileset = -1;
	return 0;
}

bool Citc_ini_reader::process_section() const
{
	return m_current_tileset != -1;
}

int Citc_ini_reader::process_key(const string& name, const string& value)
{
	switch (m_section)
	{
	case sei_unknown:
		switch (find_id(name, tileset_code, tsi_unknown))
		{
		case tsi_fname:
			m_list[m_current_tileset].m_fname = value;
			break;			
		case tsi_count:
			m_list[m_current_tileset].m_count = atoi(value.c_str());
			break;
		}
	}
	return 0;
}

bool Citc_ini_reader::is_valid() const
{
	return m_list.size();
}
