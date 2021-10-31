#pragma once

#include "ini_reader.h"

class Cmap_td_ini_reader : public Cini_reader    
{
public:
	enum t_section_id {sei_basic, sei_map, sei_unknown};
	enum t_basic_id {bai_name, bai_player, bai_unknown};
	enum t_map_id {mai_x, mai_y, mai_cx, mai_cy, mai_theater, mai_unknown};

	struct t_basic_data
	{
		string name;
		string player;
	};

	struct t_map_data
	{
		int x = 0;
		int y = 0;
		int cx = 0;
		int cy = 0;
		string theater;
	};

	int process_section_start(string_view) override;
	bool process_section() const override;
	int process_key(string_view, string_view) override;
	bool is_valid() const;

	const t_basic_data& get_basic_data() const
	{
		return m_basic_data;
	}

	const t_map_data& get_map_data() const
	{
		return m_map_data;
	}
private:
	t_basic_data m_basic_data;
	t_map_data m_map_data;

	t_section_id m_section = sei_unknown;
};
