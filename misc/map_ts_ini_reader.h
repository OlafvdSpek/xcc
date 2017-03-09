#pragma once

#include "fname.h"
#include "ini_reader.h"
#include "map_ts_encoder.h"

class Cmap_ts_ini_reader : public Cini_reader  
{
public:
	enum t_section_id {sei_basic, sei_map, sei_preview, sei_preview_pack, sei_waypoints, sei_unknown};
	enum t_basic_id {bai_name, bai_player, bai_multiplayeronly, bai_unknown};
	enum t_map_id {mai_localsize, mai_size, mai_theater, mai_unknown};
	enum t_preview_id {pri_size, pri_unknown};

	struct t_basic_data
	{
		string name;
		string player;
		int multiplayeronly;
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

	typedef map<int, int> t_waypoints_data;

	Cmap_ts_ini_reader();
	void erase();
	int max_players() const;
	int process_section_start(const string& line);
	bool process_section() const;
	int process_key(const string& name, const string& value);
	void write_report(ostream& os, string fname, const Cmap_ts_encoder& encoder) const;
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

	const t_waypoints_data& get_waypoints_data() const
	{
		return m_waypoints_data;
	}
private:
	t_basic_data m_basic_data;
	t_map_data m_map_data;
	t_preview_data m_preview_data;
	string m_preview_pack_data;
	t_waypoints_data m_waypoints_data;

	t_section_id m_section;
};
