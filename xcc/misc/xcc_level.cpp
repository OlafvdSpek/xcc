#include "stdafx.h"
#include "xcc_level.h"

#include <boost/algorithm/string.hpp>
#include "virtual_tfile_write.h"
#include "xcc_log.h"
#include "xcc_infantry.h"
#include "xcc_structures.h"
#include "xcc_templates.h"
#include "xcc_units.h"

using namespace boost;

const char* section_code[] =
{
	"basic",
	"map",
	"briefing",
	"base",
	"overlay",
	"smudge",
	"template",
	"terrain",
	"infantry",
	"reinforcements",
	"structures",
	"units",
	"celltriggers",
	"teams",
	"teamtypes",
	"triggers",
	"waypoints",
	"goodguy",
	"badguy",
	"neutral",
	"special",
	"multi1",
	"multi2",
	"multi3",
	"multi4",
	"multi5",
	"multi6"
};

const char* basic_data_code[] =
{
	"action",
	"brief",
	"buildlevel",
	"carryovercap",
	"carryovermoney",
	"intro",
	"lose",
	"name",
	"percent",
	"player",
	"theme",
	"win"
};

const char* map_data_code[] =
{
	"theater",
	"x",
	"y",
	"width",
	"height",
	"tacticalpos"
};

const char* side_data_code[] =
{
	"allies",
	"credits",
	"edge",
	"flaghome",
	"flaglocation",
	"maxbuilding",
	"maxunit",
	"quota"
};

const char* edge_code[] =
{
	"north",
	"east",
	"south",
	"west"
};

const char* side_code[] =
{
	"goodguy",
	"badguy",
	"neutral",
	"special",
	"multi1",
	"multi2",
	"multi3",
	"multi4",
	"multi5",
	"multi6",
	"none"
};

const char* theater_code[] =
{
	"desert",
	"temperate",
	"winter"
};

const char* template_code[] =
{
	"clear1",
	"w1",
	"w2",
	"sh1",
	"sh2",
	"sh3",
	"sh4",
	"sh5",
	"sh11",
	"sh12",
	"sh13",
	"sh14",
	"sh15",
	"s01",
	"s02",
	"s03",
	"s04",
	"s05",
	"s06",
	"s07",
	"s08",
	"s09",
	"s10",
	"s11",
	"s12",
	"s13",
	"s14",
	"s15",
	"s16",
	"s17",
	"s18",
	"s19",
	"s20",
	"s21",
	"s22",
	"s23",
	"s24",
	"s25",
	"s26",
	"s27",
	"s28",
	"s29",
	"s30",
	"s31",
	"s32",
	"s33",
	"s34",
	"s35",
	"s36",
	"s37",
	"s38",
	"sh32",
	"sh33",
	"sh20",
	"sh21",
	"sh22",
	"sh23",
	"br1",
	"br2",
	"br3",
	"br4",
	"br5",
	"br6",
	"br7",
	"br8",
	"br9",
	"br10",
	"p01",
	"p02",
	"p03",
	"p04",
	"p05",
	"p06",
	"p07",
	"p08",
	"sh16",
	"sh17",
	"sh18",
	"sh19",
	"p13",
	"p14",
	"p15",
	"b1",
	"b2",
	"b3",
	"b4",
	"b5",
	"b6",
	"sh6",
	"sh7",
	"sh8",
	"sh9",
	"sh10",
	"d01",
	"d02",
	"d03",
	"d04",
	"d05",
	"d06",
	"d07",
	"d08",
	"d09",
	"d10",
	"d11",
	"d12",
	"d13",
	"d14",
	"d15",
	"d16",
	"d17",
	"d18",
	"d19",
	"d20",
	"d21",
	"d22",
	"d23",
	"d24",
	"d25",
	"d26",
	"d27",
	"d28",
	"d29",
	"d30",
	"d31",
	"d32",
	"d33",
	"d34",
	"d35",
	"d36",
	"d37",
	"d38",
	"d39",
	"d40",
	"d41",
	"d42",
	"d43",
	"rv01",
	"rv02",
	"rv03",
	"rv04",
	"rv05",
	"rv06",
	"rv07",
	"rv08",
	"rv09",
	"rv10",
	"rv11",
	"rv12",
	"rv13",
	"rv14",
	"rv15",
	"rv16",
	"rv17",
	"rv18",
	"rv19",
	"rv20",
	"rv21",
	"rv22",
	"rv23",
	"rv24",
	"rv25",
	"ford1",
	"ford2",
	"falls1",
	"falls2",
	"bridge1",
	"bridge1d",
	"bridge2",
	"bridge2d",
	"bridge3",
	"bridge3d",
	"bridge4",
	"bridge4d",
	"sh24",
	"sh25",
	"sh26",
	"sh27",
	"sh28",
	"sh29",
	"sh30",
	"sh31",
	"p16",
	"p17",
	"p18",
	"p19",
	"p20",
	"sh34",
	"sh35",
	"sh36",
	"sh37",
	"sh38",
	"sh39",
	"sh40",
	"sh41",
	"sh42",
	"sh43",
	"sh44",
	"sh45",
	"sh46",
	"sh47",
	"sh48",
	"sh49",
	"sh50",
	"sh51",
	"sh52",
	"sh53",
	"sh54",
	"sh55",
	"sh56",
	"sh57",
	"sh58",
	"sh59",
	"sh60",
	"sh61",
	"sh62",
	"sh63"
};

const char* action_code[] =
{
	"area guard",
	"attack base",
	"attack civil.",
	"attack tarcom",
	"attack units",
	"defend base",
	"guard",
	"harvest",
	"hunt",
	"loop",
	"move",
	"none",
	"rampage",
	"retreat",
	"return",
	"sleep",
	"sticky",
	"unload",
	NULL
};

const char* cause_code[]=
{
	"# bldgs dstr.",
	"# units dstr.",
	"any",
	"all destr.",
	"attacked",
	"bldgs destr.",
	"built it",
	"civ. evac.",
	"credits",
	"destroyed",
	"discovered",
	"house discov.",
	"no factories",
	"none",
	"player enters",
	"time",
	"units destr.",
	NULL
};

const char* event_code[]=
{
	"all to hunt",
	"airstrike",
	"allow win",
	"autocreate",
	"cap=win/des=lose",
	"create team",
	"dstry teams",
	"dstry trig 'xxxx'",
	"dstry trig 'yyyy'",
	"dstry trig 'zzzz'",
	"dz at 'z'",
	"ion cannon",
	"lose",
	"none",
	"nuclear missile",
	"production",
	"reinforce.",
	"win",
	NULL
};

inline static bool is_section_start(const string &s)
{
	return !s.empty() && s[0] == '[' && s[s.length() - 1] == ']';
}

int find_id(const string &s, const char* t[], bool allow_unknown = false)
{
	for (int i = 0; t[i]; i++)
	{
		if (s == t[i])
			return i;
	}
	if (!allow_unknown)
		throw Cxcc_level_warning_out_of_range();
	return -1;
}

int find_id(const string &s, const char* t[], int count, bool allow_unknown = false)
{
	for (int i = 0; i < count; i++)
	{
		if (s == t[i])
			return i;
	}
	if (!allow_unknown)
		throw Cxcc_level_warning_out_of_range();
	return -1;
}

t_section_id get_section_id(string s)
{
	s.erase(0, 1);
	s.erase(s.length() - 1, 1);
	return static_cast<t_section_id>(find_id(s, section_code, c_section_id));
}

t_basic_data_id get_basic_data_id(const string &s)
{
	return static_cast<t_basic_data_id>(find_id(s, basic_data_code, c_basic_data_id));
}

t_map_data_id get_map_data_id(const string &s)
{
	return static_cast<t_map_data_id>(find_id(s, map_data_code, c_map_data_id));
}

t_side_data_id get_side_data_id(const string &s)
{
	return static_cast<t_side_data_id>(find_id(s, side_data_code, c_side_data_id));
}

t_edge_id get_edge_id(const string &s)
{
	return static_cast<t_edge_id>(find_id(s, edge_code, c_edge_id));
}

t_overlay_id get_overlay_id(const string& s, bool allow_unknown = false)
{
	return static_cast<t_overlay_id>(find_id(s, overlay_code, c_overlay_id, allow_unknown));
}

t_side_id get_side_id(const string &s, bool allow_unknown = false)
{
	return static_cast<t_side_id>(find_id(s, side_code, c_side_id, allow_unknown));
}

t_terrain_id get_terrain_id(const string& s)
{
	return static_cast<t_terrain_id>(find_id(s, terrain_code, c_terrain_id));
}

t_theater_id get_theater_id(const string &s)
{
	return static_cast<t_theater_id>(find_id(s, theater_code, c_theater_id));
}

t_action_id get_action_id(const string& s)
{
	return static_cast<t_action_id>(find_id(s, action_code));
}

t_cause_id get_cause_id(const string& s)
{
	return static_cast<t_cause_id>(find_id(s, cause_code));
}

t_event_id get_event_id(const string& s)
{
	return static_cast<t_event_id>(find_id(s, event_code));
}

int convert_overlay_edit(int v)
{
	return is_tiberium(static_cast<t_overlay_id>(v >> 8)) ? v >> 8 : v;
}

bool is_tiberium(t_overlay_id v)
{
	return v >= o_ti1 && v <= o_ti12;
}

bool is_wall(t_overlay_id v)
{
	return v >= o_barb && v <= o_brik;
}

static int get_value(char c)
{
	if (c < '0' || c > '9')
		throw Cxcc_level_warning_illegal_char();
	return c - '0';
}

static int get_value(const string &s, int min = LONG_MIN, int max = LONG_MAX)
{
	int v = 0;
	if (!s.empty())
	{
		int i = 0;
		bool negative = false;
		if (s[0] == '-')
		{
			i++;
			negative = true;
		}
		for (; i < s.length(); i++)
			v = 10 * v + get_value(s[i]);
		if (negative)
			v = -v;
	}
	if (v < min || v > max)
		throw Cxcc_level_warning_out_of_range();
	return v;
}

static bool is_valid_cell(int v)
{
	int x = v & 0x3f;
	int y = v >> 6;
	return !(x < 1 || x > 62 || y < 1 || y > 62);
}

static int get_cell_value(const string &s)
{
	int v = get_value(s);
	if (v < 0 || !is_valid_cell(v))
		throw Cxcc_level_warning_out_of_range();
	return v;
}

static void handle_basic_section_entry(const string &a, const string &b, t_basic_data &basic_data)
{
	t_basic_data_id i = get_basic_data_id(a);
	if (i == -1)
		throw Cxcc_level_warning_ignored();
	switch (i)
	{
	case bdt_action:
		basic_data.action = b;
		break;
	case bdt_brief:
		basic_data.brief = b;
		break;
	case bdt_build_level:
		basic_data.build_level = get_value(b, 1, 98);
		break;
	case bdt_carry_over_cap:
		basic_data.carry_over_cap = get_value(b, -1, -1);
		break;
	case bdt_carry_over_money:
		basic_data.carry_over_money = 100 * get_value(b, 0, 10000);
		break;
	case bdt_intro:
		basic_data.intro = b;
		break;
	case bdt_lose:
		basic_data.lose = b;
		break;
	case bdt_name:
		basic_data.name = b;
		break;
	case bdt_percent:
		basic_data.percent = get_value(b, 0, 100);
		break;
	case bdt_player:
		{
			t_side_id i = get_side_id(b);
			if (i == -1)
				throw Cxcc_level_warning_ignored();
			basic_data.player = i;
			break;
		}
	case bdt_theme:
		basic_data.theme = b;
		break;
	case bdt_win:
		basic_data.win = b;
		break;
	}
}

static void handle_map_section_entry(const string &a, const string &b, t_map_data &map_data)
{
	t_map_data_id i = get_map_data_id(a);
	if (i == -1)
		throw Cxcc_level_warning_ignored();
	switch (i)
	{
	case mdt_theater:
		map_data.theater = get_theater_id(b);
		break;
	case mdt_x:
		map_data.x = get_value(b, 1, 62);
		break;
	case mdt_y:
		map_data.y = get_value(b, 1, 62);
		break;
	case mdt_cx:
		map_data.cx = get_value(b, 1, 62);
		break;
	case mdt_cy:
		map_data.cy = get_value(b, 1, 62);
		break;
	case mdt_tactical_pos:
		map_data.tactical_pos = get_cell_value(b);
		break;
	}
}

static void handle_briefing_section_entry(const string &a, const string &b, t_briefing_data &briefing_data)
{
	if (briefing_data.empty())
		briefing_data = b;
	else
		briefing_data += " " + b;
}

static void handle_side_section_entry(const string &a, const string &b, t_side_data &side_data)
{
	t_side_data_id i = get_side_data_id(a);
	if (i == -1)
		throw Cxcc_level_warning_ignored();
	switch (i)
	{
	case sdt_allies:
		{
			side_data.allies = 0;
			Cmulti_line line = b;
			while (1)
			{
				const string c = line.get_next_line();
				if (c.empty())
					break;
				side_data.allies |= 1 << get_side_id(c);
			}
			break;
		}
	case sdt_credits:
		side_data.credits = 100 * get_value(b, 0, 10000);
		break;
	case sdt_edge:
		side_data.edge = get_edge_id(b);
		break;
	}
}

static void handle_base_section_entry(const string &a, const string &b, t_base_data &base_data)
{
	if (a == "count")
		return;
	Cmulti_line line = b;
	int t = xcc_structures::get_id(line.get_next_line());
	int v = get_value(line.get_next_line(), 0, LONG_MAX);
	v =  v >> 8 & 0x3f | v >> 18;
	if (!is_valid_cell(v))
		throw Cxcc_level_warning_ignored();
	Cxcc_cell cell;
	cell.set_cc(v);
	base_data[cell.get_xcc()] = t;
}

static void handle_infantry_section_entry(const string &a, const string &b, t_infantry_data &infantry_data)
{
	t_infantry_data_entry d;
	Cmulti_line line = b;
	d.side = get_side_id(line.get_next_line());
	d.t = xcc_infantry::get_id(line.get_next_line());
	d.health = get_value(line.get_next_line(), 0, 256);
	d.cell.set_cc(get_cell_value(line.get_next_line()));
	d.cell.subcell(get_value(line.get_next_line(), 0, 4));
	d.action = get_action_id(line.get_next_line());
	d.angle = get_value(line.get_next_line(), 0, 256);
	d.trigger = line.get_next_line();
	infantry_data.push_back(d);
}

static void handle_structures_section_entry(const string &a, const string &b, t_structure_data &structure_data)
{
	t_structure_data_entry d;
	Cmulti_line line = b;
	d.side = get_side_id(line.get_next_line());
	d.t = xcc_structures::get_id(line.get_next_line());
	d.health = get_value(line.get_next_line(), 0, 256);
	d.cell.set_cc(get_cell_value(line.get_next_line()));
	d.angle = get_value(line.get_next_line(), 0, 256);
	d.flags = sd_flags_start;
	d.trigger = line.get_next_line();
	structure_data.push_back(d);
}

static void handle_units_section_entry(const string &a, const string &b, t_unit_data &unit_data)
{
	t_unit_data_entry d;
	Cmulti_line line = b;
	d.side = get_side_id(line.get_next_line());
	d.t = xcc_units::get_id(line.get_next_line());
	d.health = get_value(line.get_next_line(), 0, 256);
	d.cell.set_cc(get_cell_value(line.get_next_line()));
	d.angle = get_value(line.get_next_line(), 0, 256);
	d.action = get_action_id(line.get_next_line());
	d.trigger = line.get_next_line();
	unit_data.push_back(d);
}

static void handle_overlay_section_entry(const string &a, const string &b, t_overlay_data &overlay_data, t_structure_data &structure_data)
{
	t_overlay_id v = get_overlay_id(b, true);
	if (v == -1)
	{
		handle_structures_section_entry("", "neutral," + b + ",256," + a + ",0,none", structure_data);
		return;
	}
	Cxcc_cell cell;
	cell.set_cc(get_cell_value(a));
	int w = 0;
	if (is_tiberium(v))
	{
		w = v - o_ti1;
		v = static_cast<t_overlay_id>((cell.get_x() >> 8  & 63 ^ cell.get_y() >> 8) % 12 + o_ti1);
	}
	overlay_data[cell.get_xcc()] = v << 8 | w;
}

static void handle_terrain_section_entry(const string &a, const string &b, t_terrain_data &terrain_data)
{
	Cmulti_line line = b;
	Cxcc_cell cell;
	cell.set_cc(get_cell_value(a));
	terrain_data[cell.get_xcc()] = get_terrain_id(line.get_next_line()) << 8;
}

static void handle_celltriggers_section_entry(const string &a, const string &b, t_celltrigger_data &celltrigger_data)
{
	celltrigger_data[get_cell_value(a)] = b;
}

static void handle_teamtypes_section_entry(const string &a, const string &b, t_teamtype_data &teamtype_data)
{
	Cmulti_line line = b;
	t_teamtype_data_entry d;
	d.side = get_side_id(line.get_next_line());
	d.flags = 0;
	if (get_value(line.get_next_line(), 0, 1))
		d.flags |= td_flags_link;
	line.get_next_line();
	if (get_value(line.get_next_line(), 0, 1))
		d.flags |= td_flags_force_move;
	if (get_value(line.get_next_line(), 0, 1))
		d.flags |= td_flags_autocreate;
	line.get_next_line();
	d.u1 = get_value(line.get_next_line(), 2, 30);
	d.c_teams = get_value(line.get_next_line(), 0, 99);
	line.get_next_line();
	line.get_next_line();
	d.c_objects = get_value(line.get_next_line(), 1, 16);
	ZeroMemory(d.object_list, sizeof(d.object_list));
	for (int i = 0; i < d.c_objects; i++)
	{
		Cmulti_line c = line.get_next_line();
		const string t = c.get_next_line(':');
		const int n = get_value(c.get_next_line(), 1, 99);
		const int z = xcc_infantry::get_id(t);
		if (z != -1)
			d.object_list[i] = z << 8 | n;
		else
			d.object_list[i] = 0x8000 | xcc_units::get_id(t) << 8 | n;
	}
	d.c_actions = get_value(line.get_next_line(), 0, 64);
	ZeroMemory(d.action_list, sizeof(d.action_list));
	for (int i = 0; i < d.c_actions; i++)
	{
		Cmulti_line c = line.get_next_line();
		const int z = get_action_id(c.get_next_line(':'));
		if (z == -1)
			assert(false);
		const int n = get_value(c.get_next_line(), 0, 99);
		d.action_list[i] = z << 8 | n;
	}
	if (get_value(line.get_next_line(), 0, 1))
		d.flags |= td_flags_replace;
	if (get_value(line.get_next_line(), 0, 1))
		d.flags |= td_flags_force_creation;
	teamtype_data[a] = d;
}

static void handle_triggers_section_entry(const string &a, const string &b, t_trigger_data &trigger_data)
{
	Cmulti_line line = b;
	t_trigger_data_entry d;
	d.cause = get_cause_id(line.get_next_line());
	d.event = get_event_id(line.get_next_line());
	d.count = get_value(line.get_next_line(), 0, 999);
	d.side = get_side_id(line.get_next_line(), true);
	d.teamtype = line.get_next_line();
	d.loop = get_value(line.get_next_line(), 0, 2);
	trigger_data[a] = d;
}

static void handle_waypoints_section_entry(const string &a, const string &b, t_waypoint_data &waypoint_data)
{
	if (b != "-1")
		waypoint_data[get_value(a, 0, 99)] = get_cell_value(b);
}

Cxcc_level::Cxcc_level()
{
}

Cxcc_level::~Cxcc_level()
{
}

int Cxcc_level::load(const Cvirtual_binary& bin, const Cvirtual_binary& ini)
{
	clear();
	if (!bin.data())
		return load_ini(ini, true);
	if (load_ini(ini, false) || load_bin(bin))
		return 1;
	process();
	return 0;
}

int Cxcc_level::load_bin(const Cvirtual_binary& data)
{
	memcpy(bin_data, data.data(), 8192);
	convert_bin(bin_data);
	return 0;
}

int Cxcc_level::load_ini(const Cvirtual_binary& data, bool fast)
{
	Cvirtual_tfile f;
	f.load_data(data);
	t_section_id section;
	bool handle_section = false;
	int line_i = 0;
	while (!f.eof())
	{
		line_i++;
		string s = f.read_line();
		int pos = s.find(';');
		if (pos != -1)
			s.erase(pos, s.npos);
		trim(s);
		to_lower(s);
		if (s.empty())
			continue;
		try
		{
			if (is_section_start(s))
			{
				handle_section = false;
				section = get_section_id(s);
				handle_section = !fast || section == si_basic || section == si_map;
			}
			else if (handle_section)
			{
				int pos = s.find('=');
				if (pos == -1)
					throw Cxcc_level_warning_ignored();
				string a = s.substr(0, pos), b = s.substr(pos + 1, s.npos);
				trim(a);
				trim(b);
				switch (section)
				{
				case si_basic:
					handle_basic_section_entry(a, b, basic_data);
					break;
				case si_map:
					handle_map_section_entry(a, b, map_data);
					break;
				case si_briefing:
					handle_briefing_section_entry(a, b, briefing_data);
					break;
				case si_goodguy:
				case si_badguy:
				case si_neutral:
				case si_special:
				case si_multi1:
				case si_multi2:
				case si_multi3:
				case si_multi4:
				case si_multi5:
				case si_multi6:
					handle_side_section_entry(a, b, side_data[section - si_goodguy]);
					break;
				case si_base:
					handle_base_section_entry(a, b, base_data);
					break;
				case si_infantry:
					handle_infantry_section_entry(a, b, infantry_data);
					break;
				case si_structures:
					handle_structures_section_entry(a, b, structure_data);
					break;
				case si_units:
					handle_units_section_entry(a, b, unit_data);
					break;
				case si_overlay:
					handle_overlay_section_entry(a, b, overlay_data, structure_data);
					break;
				case si_terrain:
					handle_terrain_section_entry(a, b, terrain_data);
					break;
				case si_celltriggers:
					handle_celltriggers_section_entry(a, b, celltrigger_data);
					break;
				case si_teamtypes:
					handle_teamtypes_section_entry(a, b, teamtype_data);
					break;
				case si_triggers:
					handle_triggers_section_entry(a, b, trigger_data);
					break;
				case si_waypoints:
					handle_waypoints_section_entry(a, b, waypoint_data);
					break;
				}
			}
		}
		catch (Cxcc_level_warning_ignored&)
		{
			xcc_log::write_line("Warning, line " + n(line_i) + " is ignored");
			xcc_log::write_line(static_cast<string>("    ") + (handle_section ? static_cast<string>("[") + section_code[section] + "] " : "") + s);
		}
		catch (Cxcc_level_warning_illegal_char&)
		{
			xcc_log::write_line("Warning, line " + n(line_i) + " contains an illegar character");
			xcc_log::write_line(static_cast<string>("    ") + (handle_section ? static_cast<string>("[") + section_code[section] + "] " : "")  + s);
		}
		catch (Cxcc_level_warning_out_of_range&)
		{
			xcc_log::write_line("Warning, line " + n(line_i) + " contains an value that's out of range");
			xcc_log::write_line(static_cast<string>("    ") + (handle_section ? static_cast<string>("[") + section_code[section] + "] " : "")  + s);
		}
	}
	return 0;
}

void Cxcc_level::save(Cvirtual_binary& bin, Cvirtual_binary& ini) const
{
	bin = save_bin();
	ini = save_ini();
}

Cvirtual_binary Cxcc_level::save_bin() const
{
	Cvirtual_binary d(NULL, 8192);
	memcpy(d.data_edit(), bin_data, d.size());
	deconvert_bin(reinterpret_cast<unsigned short*>(d.data_edit()));
	return d;
}

Cvirtual_binary Cxcc_level::save_ini() const
{
	Cvirtual_tfile_write f;

	f.write_line(static_cast<string>("[") + section_code[si_basic] + ']');
	if (!basic_data.action.empty())
		f.write_line(static_cast<string>(basic_data_code[bdt_action]) + '=' + basic_data.action);
	if (!basic_data.brief.empty())
	f.write_line(static_cast<string>(basic_data_code[bdt_brief])  + '=' + basic_data.brief);
	f.write_line(static_cast<string>(basic_data_code[bdt_build_level]) + '=' + n(basic_data.build_level));
	// f.write_line(static_cast<string>(basic_data_code[bdt_carry_over_cap]) + '=' + n(basic_data.carry_over_cap));
	f.write_line(static_cast<string>(basic_data_code[bdt_carry_over_money]) + '=' + n(basic_data.carry_over_money / 100l));
	if (!basic_data.intro.empty())
		f.write_line(static_cast<string>(basic_data_code[bdt_intro]) + '=' + basic_data.intro);
	if (!basic_data.lose.empty())
		f.write_line(static_cast<string>(basic_data_code[bdt_lose]) + '=' + basic_data.lose);
	if (!basic_data.name.empty())
		f.write_line(static_cast<string>(basic_data_code[bdt_name]) + '=' + basic_data.name);
	f.write_line(static_cast<string>(basic_data_code[bdt_percent]) + '=' + n(basic_data.percent));
	f.write_line(static_cast<string>(basic_data_code[bdt_player]) + '=' + side_code[basic_data.player]);
	if (!basic_data.theme.empty())
		f.write_line(static_cast<string>(basic_data_code[bdt_theme]) + '=' + basic_data.theme);
	if (!basic_data.win.empty())
		f.write_line(static_cast<string>(basic_data_code[bdt_win]) + '=' + basic_data.win);
	f.write_line("");

	f.write_line(static_cast<string>("[") + section_code[si_map] + ']');
	f.write_line(static_cast<string>(map_data_code[mdt_theater]) + '=' + theater_code[map_data.theater]);
	f.write_line(static_cast<string>(map_data_code[mdt_x]) + '=' + n(map_data.x));
	f.write_line(static_cast<string>(map_data_code[mdt_y]) + '=' + n(map_data.y));
	f.write_line(static_cast<string>(map_data_code[mdt_cx]) + '=' + n(map_data.cx));
	f.write_line(static_cast<string>(map_data_code[mdt_cy]) + '=' + n(map_data.cy));
	// f.write_line(static_cast<string>(map_data_code[mdt_tactical_pos] + '=' + map_data.tactical_pos);
	f.write_line("");

	if (!briefing_data.empty())
	{
		f.write_line(static_cast<string>("[") + section_code[si_briefing] + ']');
		f.write_line(static_cast<string>("1") + '=' + briefing_data);
		f.write_line("");
	}

	f.write_line(static_cast<string>("[") + section_code[si_celltriggers] + ']');
	for (t_celltrigger_data::const_iterator i = celltrigger_data.begin(); i != celltrigger_data.end(); i++)
	{
		f.write_line(n(i->first) + '=' + i->second);
	}
	f.write_line("");

	f.write_line(static_cast<string>("[") + section_code[si_teamtypes] + ']');
	for (t_teamtype_data::const_iterator i = teamtype_data.begin(); i != teamtype_data.end(); i++)
	{
		const t_teamtype_data_entry& d = i->second;
		f.write(i->first + '=' + side_code[d.side] + ',' + n(static_cast<bool>(d.flags & td_flags_link)) + ",0," +
			n(static_cast<bool>(d.flags & td_flags_force_move)) + ',' + n(static_cast<bool>(d.flags & td_flags_autocreate)) + ",0," +
			n(d.u1) + ',' + n(d.c_teams) + ",0,0," + n(d.c_objects) + ',');
		for (int i = 0; i < d.c_objects; i++)
		{
			int v = d.object_list[i];
			f.write(static_cast<string>(v & 0x8000 ? xcc_units::unit_data[v >> 8 & 0x7f].short_name : xcc_infantry::infantry_data[v >> 8].short_name) +
				':' + n(v & 0xff) + ',');
		}
		f.write(n(d.c_actions) + ',');
		for (int i = 0; i < d.c_actions; i++)
		{
			int v = d.action_list[i];
			f.write(static_cast<string>(action_code[v >> 8]) + ':' + n(v & 0xff) + ',');
		}
		f.write_line(n(static_cast<bool>(d.flags & td_flags_replace)) + ',' + n(static_cast<bool>(d.flags & td_flags_force_creation)));
	}
	f.write_line("");

	f.write_line(static_cast<string>("[") + section_code[si_triggers] + ']');
	for (t_trigger_data::const_iterator i = trigger_data.begin(); i != trigger_data.end(); i++)
	{
		const t_trigger_data_entry& d = i->second;
		f.write_line(i->first + '=' + cause_code[d.cause] + ',' + event_code[d.event] + ',' +
			n(d.count) + ',' + side_code[d.side == -1 ? s_none : d.side] + ',' +
			d.teamtype + ',' + n(d.loop));
	}
	f.write_line("");

	f.write_line(static_cast<string>("[") + section_code[si_waypoints] + ']');
	for (int i = 0; i < 100; i++)
	{
		if (waypoint_data[i] != -1)
			f.write_line(n(i) + '=' + n(waypoint_data[i]));
	}
	f.write_line("");

	{
		f.write_line(static_cast<string>("[") + section_code[si_base] + ']');
		int index = 0;
		for (t_structure_data::const_iterator i = structure_data.begin(); i < structure_data.end(); i++)
		{
			if (i->flags & sd_flags_replace)
			{
				f.write_line(nwzl(3, index++) + '=' + xcc_structures::structure_data[i->t].short_name
					+ ',' + n(static_cast<int>((i->cell.get_cc() & 0xfc0) << 18 | (i->cell.get_cc() & 0x3f) << 8)));
			}
		}
	}
	f.write_line("");
	{
		f.write_line(static_cast<string>("[") + section_code[si_infantry] + ']');
		int index = 0;
		for (t_infantry_data::const_iterator i = infantry_data.begin(); i < infantry_data.end(); i++)
		{
			f.write_line(nwzl(3, index++) + '=' + side_code[i->side] + ',' + xcc_infantry::infantry_data[i->t].short_name
				+ ',' + n(i->health) + ',' + n(i->cell.get_cc()) + ',' + n(i->cell.subcell())
				+ ',' + action_code[i->action] + ',' + n(i->angle) + ',' + i->trigger);
		}
		f.write_line("");
	}
	{
		f.write_line(static_cast<string>("[") + section_code[si_structures] + ']');
		int index = 0;
		for (t_structure_data::const_iterator i = structure_data.begin(); i < structure_data.end(); i++)
		{
			if (i->flags & sd_flags_start)
			{
				f.write_line(nwzl(3, index++) + '=' + side_code[i->side] + ',' + xcc_structures::structure_data[i->t].short_name
					+ ',' + n(i->health) + ',' + n(i->cell.get_cc()) + ',' + n(i->angle)  + ',' + i->trigger);

			}
		}
		f.write_line("");
	}
	f.write_line(static_cast<string>("[") + section_code[si_units] + ']');
	int index = 0;
	for (t_unit_data::const_iterator i = unit_data.begin(); i < unit_data.end(); i++)
	{
		f.write_line(nwzl(3, index++) + '=' + side_code[i->side] + ',' + xcc_units::unit_data[i->t].short_name
			+ ',' + n(i->health) + ',' + n(i->cell.get_cc()) + ',' + n(i->angle)
			+ ',' + action_code[i->action] + ',' + i->trigger);
	}
	f.write_line("");

for (int i = 0; i < c_side_id; i++)
	{
		f.write_line(static_cast<string>("[") + section_code[si_goodguy + i] + ']');
		f.write(static_cast<string>(side_data_code[sdt_allies]) + '=');
		bool first = true;
		for (int j = 0; j < c_side_id; j++)
		{
			if (side_data[i].allies >> j & 1)
			{
				if (!first)
					f.write(",");
				f.write(side_code[j]);
				first = false;
			}
		}
		f.write_line("");
		if (side_data[i].credits)
			f.write_line(static_cast<string>(side_data_code[sdt_credits]) + '=' + n(side_data[i].credits / 100l));
		f.write_line(static_cast<string>(side_data_code[sdt_edge]) + '=' + edge_code[side_data[i].edge]);
		// f.write_line(static_cast<string>(side_data_code[sdt_flag_home]) + '=' + side_data[i].flag_home);
		// f.write_line(static_cast<string>(side_data_code[sdt_flag_location]) + '=' + side_data[i].flag_location);
		/*
		if (side_data[i].c_max_building)
		f.write_line(static_cast<string>(side_data_code[sdt_max_building]) + '=' + n(side_data[i].c_max_building));
		if (side_data[i].c_max_unit)
		f.write_line(static_cast<string>(side_data_code[sdt_max_unit]) + '=' + n(side_data[i].c_max_unit));
		*/
		// f.write_line(static_cast<string>(side_data_code[sdt_quota]) + '=' + side_data[i].quota);
		f.write_line("");
	}

	f.write_line(static_cast<string>("[") + section_code[si_overlay] + ']');
	for (t_overlay_data::const_iterator i = overlay_data.begin(); i != overlay_data.end(); i++)
	{
		t_overlay_id v = static_cast<t_overlay_id>(i->second >> 8);
		if (is_tiberium(v))
			v = static_cast<t_overlay_id>((i->second & 0xff) + o_ti1);
		Cxcc_cell cell;
		cell.set_xcc(i->first);
		f.write_line(n(cell.get_cc()) + '=' + overlay_code[v]);
	}
	f.write_line("");

	f.write_line(static_cast<string>("[") + section_code[si_terrain] + ']');
	for (t_terrain_data::const_iterator i = terrain_data.begin(); i != terrain_data.end(); i++)
	{
		Cxcc_cell cell;
		cell.set_xcc(i->first);
		f.write_line(n(cell.get_cc()) + '=' + terrain_code[i->second >> 8] + ",none");
	}
	f.write_line("");
	return f.save();
}

void Cxcc_level::convert_bin(unsigned short* data) const
{
	Cxcc_templates::load_images(map_data.theater);
	for (int i = 0; i < 4096; i++)
	{
		unsigned short& v = data[i];
		if ((v & 0xff) > 0xd7 || !(v & 0xff))
		{
			int x = i & 0x3f;
			int y = i >> 6;
			v = x & 3 | (y & 3) << 2;
		}
		else
			v = Cxcc_templates::convert_bin_data(v);
	}
}

void Cxcc_level::deconvert_bin(unsigned short* data) const
{
	for (int i = 0; i < 4096; i++)
		data[i] = Cxcc_templates::deconvert_bin_data(data[i]);
}

void Cxcc_level::process()
{
	{
		for (int i = 0; i < 4096; i++)
		{
			int x = i & 0x3f;
			int y = i >> 6;
			unsigned short& v = bin_data[i];
			switch (v >> 8)
			{
			case 0:
				v = v & 0xff00 | x & 3 | (y & 3) << 2;
				break;
			case 2:
				v = v & 0xff00 | x & 1 | (y & 1) << 1;
				break;
			}
		}
	}
	{
		// overlay
		for (t_overlay_data::const_iterator i = overlay_data.begin(); i != overlay_data.end(); i++)
		{
			int cell = i->first;
			t_overlay_id v = static_cast<t_overlay_id>(i->second >> 8);
			int w = i->second & 0xff;
			if (is_wall(v))
			{
				t_overlay_data::const_iterator j;
				j = overlay_data.find(cell - 256);
				bool top = j != overlay_data.end() && j->second >> 8 == v;
				j = overlay_data.find(cell + 1);
				bool right = j != overlay_data.end() && j->second >> 8 == v;
				j = overlay_data.find(cell + 256);
				bool bottom = j != overlay_data.end() && j->second >> 8 == v;
				j = overlay_data.find(cell - 1);
				bool left = j != overlay_data.end() && j->second >> 8 == v;
				w = top | right << 1 | bottom << 2 | left << 3;
			}
			overlay_data[cell] = v << 8 | w;
		}
	}
	{
		// base
		for (t_base_data::const_iterator i = base_data.begin(); i != base_data.end(); i++)
		{
			t_structure_data::iterator j;
			for (j = structure_data.begin(); j < structure_data.end(); j++)
			{
				if (i->first == j->cell.get_xcc() && i->second == j->t)
				{
					j->flags |= sd_flags_replace;
					break;
				}
			}
			if (j == structure_data.end())
			{
				t_structure_data_entry d;
				d.side = basic_data.player != s_goodguy ? s_goodguy : s_badguy;
				d.t = i->second;
				d.health = 256;
				d.cell.set_xcc(i->first);
				d.angle = 0;
				d.flags = sd_flags_replace;
				d.trigger = "none";
				structure_data.push_back(d);
			}
		}
		base_data.clear();
	}
}

void Cxcc_level::clear()
{
	{
		for (int i = 0; i < 4096; i++)
		{
			int x = i & 0x3f;
			int y = i >> 6;
			bin_data[i] = x & 3 | (y & 3) << 2;
		}
	}

	basic_data.action.erase();
	basic_data.brief.erase();
	basic_data.build_level = 1;
	basic_data.carry_over_cap = -1;
	basic_data.carry_over_money = 0;
	basic_data.intro.erase();
	basic_data.lose.erase();
	basic_data.name.erase();
	basic_data.percent = 100;
	basic_data.player = s_goodguy;
	basic_data.theme.erase();
	basic_data.win.erase();

	map_data.theater = t_temperate;
	map_data.x = 1;
	map_data.y = 1;
	map_data.cx = 62;
	map_data.cy = 62;
	map_data.tactical_pos = 0;

	briefing_data.erase();

	{
		for (int i = 0; i < c_side_id; i++)
		{
			side_data[i].allies = 1 << i;
			side_data[i].credits = 0;
			side_data[i].edge = e_north;
		}
	}

	base_data.clear();
	infantry_data.clear();
	structure_data.clear();
	unit_data.clear();
	overlay_data.clear();
	terrain_data.clear();
	celltrigger_data.clear();
	teamtype_data.clear();
	trigger_data.clear();
	memset(waypoint_data, -1, sizeof(waypoint_data));

	process();
}