// map_ts_ini_reader.h: interface for the Cmap_ts_ini_reader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_TS_INI_READER_H__06E64C81_7C49_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_MAP_TS_INI_READER_H__06E64C81_7C49_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ini_reader.h"

class Cmap_ts_ini_reader: public Cini_reader  
{
public:
	enum t_section_id {sei_basic, sei_map, sei_preview, sei_preview_pack, sei_unknown};
	enum t_basic_id {bai_name, bai_player, bai_unknown};
	enum t_map_id {mai_localsize, mai_size, mai_theater, mai_unknown};
	enum t_preview_id {pri_size, pri_unknown};

	struct t_basic_data
	{
		string name;
		string player;
	};

	struct t_map_data
	{
		int localsize_left;
		int localsize_top;
		int localsize_right;
		int localsize_bottom;
		int size_left;
		int size_top;
		int size_right;
		int size_bottom;
		string theater;
	};

	struct t_preview_data
	{
		int x;
		int y;
		int cx;
		int cy;
	};

	Cmap_ts_ini_reader();
	void erase();
	int process_section_start(const string& line);
	bool process_section() const;
	int process_key(const string& name, const string& value);
	bool is_valid() const;

	const t_basic_data& get_basic_data() const
	{
		return m_basic_data;
	}

	const t_map_data& get_map_data() const
	{
		return m_map_data;
	}

	const t_preview_data& get_preview_data() const
	{
		return m_preview_data;
	}

	const string& get_preview_pack_data() const
	{
		return m_preview_pack_data;
	}
private:
	t_basic_data m_basic_data;
	t_map_data m_map_data;
	t_preview_data m_preview_data;
	string m_preview_pack_data;

	t_section_id m_section;
};

#endif // !defined(AFX_MAP_TS_INI_READER_H__06E64C81_7C49_11D4_B606_0000B4936994__INCLUDED_)
