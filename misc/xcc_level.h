/*
    XCC Utilities and Library
    Copyright (C) 2000  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include "multi_line.h"
#include "string_conversion.h"
#include "virtual_tfile.h"
#include "xcc_cell.h"
#include "xcc_infantry.h"
#include "xcc_structures.h"
#include "xcc_units.h"

enum t_edge_id
{
	e_north, e_east, e_south, e_west
};

const char* edge_code[];

enum t_side_id
{
	s_goodguy, s_badguy, s_neutral, s_special,
	s_multi1, s_multi2, s_multi3, s_multi4, s_multi5, s_multi6, s_none
};

const int c_side_id = s_multi6 + 1;

const char* side_code[];

enum t_theater_id
{
	t_desert, t_temperate, t_winter, t_snow
};

const char* theater_code[];

enum t_section_id
{
	si_basic, si_map, si_briefing, si_base,
	si_overlay, si_smudge, si_template, si_terrain,
	si_infantry, si_reinforcements, si_structures, si_units,
	si_celltriggers, si_teams, si_teamtypes, si_triggers, si_waypoints,
	si_goodguy, si_badguy, si_neutral, si_special,
	si_multi1, si_multi2, si_multi3, si_multi4, si_multi5, si_multi6
};

const char* section_code[];

enum t_basic_data_id
{
	bdt_action, bdt_brief, bdt_build_level, bdt_carry_over_cap, bdt_carry_over_money, bdt_intro, 
	bdt_lose, bdt_name, bdt_percent, bdt_player, bdt_theme, bdt_win
};

const char* basic_data_code[];

enum t_map_data_id
{
	mdt_theater, mdt_x, mdt_y, mdt_cx, mdt_cy, mdt_tactical_pos
};

const char* map_data_code[];

enum t_side_data_id
{
	sdt_allies, sdt_credits, sdt_edge, sdt_flag_home, sdt_flag_location, sdt_max_building,
	sdt_max_unit, sdt_quota
};

const char* side_data_code[];

enum t_overlay_id
{
	o_ti1, o_ti2, o_ti3, o_ti4, o_ti5, o_ti6, o_ti7, o_ti8, o_ti9, o_ti10, o_ti11, o_ti12,
	o_barb, o_wood, o_sbag, o_cycl, o_brik, o_scrate, o_wcrate,
	o_conc,
	o_fpls,
	o_road,
	o_squish,
	o_v12,
	o_v13,
	o_v14,
	o_v15,
	o_v16,
	o_v17,
	o_v18,	
	c_overlay_id
};

const char* overlay_code[];

enum t_terrain_id
{
	t_rock1, t_rock2, t_rock3, t_rock4, t_rock5, t_rock6, t_rock7,
	t_split2, t_split3,
	t_t01, t_t02, t_t03, t_t04, t_t05, t_t06, t_t07, t_t08, t_t09, t_t10,
	t_t11, t_t12, t_t13, t_t14, t_t15, t_t16, t_t17, t_t18,
	t_tc1, t_tc2, t_tc3, t_tc4, t_tc5
};		

const int c_terrain_id = t_tc5 + 1;

const char* terrain_code[];

const int c_template_id = 0xd8;

const char* template_code[];

enum t_action_id
{
	a_ambush,
	a_area_guard,
	a_attack,
	a_attack_base,
	a_attack_civil,
	a_attack_tarcom,
	a_attack_units,
	a_capture,
	a_construction,
	a_defend_base,
	a_enter,
	a_guard,
	a_harvest,
	a_hunt,
	a_missle,
	a_loop,
	a_move,
	a_none,
	a_rampage,
	a_repair,
	a_rescue,
	a_retreat,
	a_return,
	a_sabotage,
	a_selling,
	a_sleep,
	a_sticky,
	a_stop,
	a_timed_hunt,
	a_unload,
};

const char* action_code[];

enum t_cause_id
{
	c_c_buildings_destroyed, c_c_units_destroyed,
	c_any, c_all_destroyed, c_attacked, c_buildings_destroyed, c_build_it, 
	c_civilians_evacuated, c_credits, c_destroyed, c_discovered, 
	c_house_discoved, c_no_factories, c_none, c_player_enters, 
	c_time, c_units_destroyed, 
};

const char* cause_code[];

enum t_event_id
{
	e_all_to_hunt, e_airstrike, e_allow_win, e_autocreate, e_cap_win_des_lose,
	e_create_team, e_destroy_teams, 
	e_destroy_trigger_x, e_destroy_trigger_y, e_destroy_trigger_z, 
	e_dropzone_at_z, e_ion_cannon, e_lose, e_none, e_nuclear_missile, e_production,
	e_reinforcement, e_win
};

const char* event_code[];

enum t_object_id
{
	oi_template, oi_overlay, oi_smudge, oi_terrain,
	oi_infantry, oi_structure, oi_unit
};

struct t_basic_data
{
	t_basic_data()
	{
		build_level = 1;
		carry_over_money = 0;
		percent = 100;
		player = s_goodguy;
	}

	string action;
	string brief;
	int build_level;
	int carry_over_money;
	string intro;
	string lose;
	string name;
	int percent;
	t_side_id player;
	string theme;
	string win;
};

struct t_map_data
{
	t_map_data()
	{
		theater = t_temperate;
		x = 1;
		y = 1;
		cx = 62;
		cy = 62;
	}

	t_theater_id theater;
	int x;
	int y;
	int cx;
	int cy;
};

struct t_side_data
{
	int allies;
	int credits;
	t_edge_id edge;
};

struct t_infantry_data_entry
{
	t_side_id side;
	xcc_infantry::t_infantry_data_entry* t;
	int health;
	Cxcc_cell cell;
	int angle;
	t_action_id action;
	string trigger;
};

enum
{
	sd_flags_start = 1,
	sd_flags_replace = 2
};

struct t_structure_data_entry
{
	t_side_id side;
	xcc_structures::t_structure_data_entry* t;
	int health;
	Cxcc_cell cell;
	int angle;
	int flags;
	string trigger;
};

struct t_unit_data_entry
{
	t_side_id side;
	xcc_units::t_unit_data_entry* t;
	int health;
	Cxcc_cell cell;
	int angle;
	t_action_id action;
	string trigger;
};

enum
{
	td_flags_link = 1,
	td_flags_force_move = 2,
	td_flags_autocreate = 4,
	td_flags_replace = 8,
	td_flags_force_creation = 0x10
};

struct t_teamtype_data_entry
{
	using t_objects = vector<pair<string, int>>;
	using t_actions = vector<pair<int, int>>;

	t_side_id side;
	int flags;
	int u1;
	int c_teams;
	t_objects objects;
	t_actions actions;
};

struct t_trigger_data_entry
{
	t_cause_id cause;
	t_event_id event;
	int count;
	t_side_id side;
	string teamtype;
	int loop;
};

using t_briefing_data = string;
using t_base_data = map<int, xcc_structures::t_structure_data_entry*>;
using t_infantry_data = vector<t_infantry_data_entry>;
using t_structure_data = vector<t_structure_data_entry>;
using t_unit_data = vector<t_unit_data_entry>;
using t_overlay_data = map<int, int>;
using t_terrain_data = map<int, int>;
using t_celltrigger_data = map<int, string>;
using t_teamtype_data = map<string, t_teamtype_data_entry>;
using t_trigger_data = map<string, t_trigger_data_entry>;
using t_waypoint_data = array<int, 100>;
using t_bin_data = array<unsigned short, 4096>;

int convert_overlay_edit(int v);
bool is_tiberium(t_overlay_id v);
bool is_wall(t_overlay_id v);

class Cxcc_level  
{
public:
	void clear();
	void process();
	int load(const Cvirtual_binary& bin, const Cvirtual_binary& ini);
	int load_bin(const Cvirtual_binary& data);
	int load_ini(const Cvirtual_binary& data, bool fast);
	void save(Cvirtual_binary& bin, Cvirtual_binary& ini) const;
	Cvirtual_binary save_bin() const;
	Cvirtual_binary save_ini() const;
// private:
	t_bin_data bin_data;
	t_basic_data basic_data;
	t_map_data map_data;
	t_briefing_data briefing_data;
	array<t_side_data, c_side_id> side_data;
	t_base_data base_data;
	t_infantry_data infantry_data;
	t_structure_data structure_data;
	t_unit_data unit_data;
	t_overlay_data overlay_data;
	t_terrain_data terrain_data;
	t_celltrigger_data celltrigger_data;
	t_teamtype_data teamtype_data;
	t_trigger_data trigger_data;
	t_waypoint_data waypoint_data;
private:
	bool has_overlay(int i, int x, int y, int v) const;
	void convert_bin(unsigned short* data) const;
	void deconvert_bin(unsigned short* data) const;
};

class Cxcc_level_warning
{
};

class Cxcc_level_warning_ignored : public Cxcc_level_warning
{
};

class Cxcc_level_warning_illegal_char : public Cxcc_level_warning
{
};

class Cxcc_level_warning_out_of_range : public Cxcc_level_warning
{
};
