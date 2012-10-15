#include "stdafx.h"
#include "xcc_level.h"

#include <sstream>
#include "xcc_log.h"
#include "xcc_infantry.h"
#include "xcc_structures.h"
#include "xcc_templates.h"
#include "xcc_units.h"

const char* section_code[] =
{
	"Basic",
	"Map",
	"Briefing",
	"Base",
	"Overlay",
	"Smudge",
	"Template",
	"Terrain",
	"Infantry",
	"Reinforcements",
	"Structures",
	"Units",
	"Celltriggers",
	"Teams",
	"Teamtypes",
	"Triggers",
	"Waypoints",
	"Goodguy",
	"Badguy",
	"Neutral",
	"Special",
	"Multi1",
	"Multi2",
	"Multi3",
	"Multi4",
	"Multi5",
	"Multi6",
	NULL
};

const char* basic_data_code[] =
{
	"Action",
	"Brief",
	"Buildlevel",
	"Carryovercap",
	"Carryovermoney",
	"Intro",
	"Lose",
	"Name",
	"Percent",
	"Player",
	"Theme",
	"Win",
	NULL
};

const char* map_data_code[] =
{
	"Theater",
	"X",
	"Y",
	"Width",
	"Height",
	"Tacticalpos",
	NULL
};

const char* side_data_code[] =
{
	"Allies",
	"Credits",
	"Edge",
	"Flaghome",
	"Flaglocation",
	"Maxbuilding",
	"Maxunit",
	"Quota",
	NULL
};

const char* edge_code[] =
{
	"north",
	"east",
	"south",
	"west",
	NULL
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
	"none",
	NULL
};

const char* theater_code[] =
{
	"desert",
	"temperate",
	"winter",
	"snow",
	NULL
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
	"ambush",
	"area guard",
	"attack",
	"attack base",
	"attack civil.",
	"attack tarcom",
	"attack units",
	"capture",
	"construction",
	"defend base",
	"enter",
	"guard",
	"harvest",
	"hunt",
	"missle",
	"loop",
	"move",
	"none",
	"rampage",
	"repair",
	"rescue",
	"retreat",
	"return",
	"sabotage",
	"selling",
	"sleep",
	"sticky",
	"stop",
	"timed hunt",
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
		if (iequals(t[i], s))
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
		if (iequals(t[i], s))
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
	return static_cast<t_section_id>(find_id(s, section_code));
}

t_basic_data_id get_basic_data_id(const string &s)
{
	return static_cast<t_basic_data_id>(find_id(s, basic_data_code));
}

t_map_data_id get_map_data_id(const string &s)
{
	return static_cast<t_map_data_id>(find_id(s, map_data_code));
}

t_side_data_id get_side_data_id(const string &s)
{
	return static_cast<t_side_data_id>(find_id(s, side_data_code));
}

t_edge_id get_edge_id(const string &s)
{
	return static_cast<t_edge_id>(find_id(s, edge_code));
}

t_overlay_id get_overlay_id(const string& s, bool allow_unknown = false)
{
	return static_cast<t_overlay_id>(find_id(s, overlay_code, allow_unknown));
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
	return static_cast<t_theater_id>(find_id(s, theater_code));
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
	switch (get_basic_data_id(a))
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
	default:
		throw Cxcc_level_warning_ignored();
	}
}

static void handle_map_section_entry(const string &a, const string &b, t_map_data &map_data)
{
	switch (get_map_data_id(a))
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
	case -1:
		throw Cxcc_level_warning_ignored();
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
	switch (get_side_data_id(a))
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
	case -1:
		throw Cxcc_level_warning_ignored();
	}
}

static void handle_base_section_entry(const string &a, const string &b, t_base_data &base_data)
{
	if (iequals(a, "count"))
		return;
	Cmulti_line line = b;
	auto t = xcc_structures::get_id(line.get_next_line());
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
	t_overlay_id v = get_overlay_id(b);
	Cxcc_cell cell;
	cell.set_cc(get_cell_value(a));
	int w = 0;
	if (is_tiberium(v))
	{
		w = v - o_ti1;
		v = static_cast<t_overlay_id>((cell.x >> 8  & 63 ^ cell.y >> 8) % 12 + o_ti1);
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
	for (int i = get_value(line.get_next_line(), 1, 16); i--; )
	{
		Cmulti_line c = line.get_next_line();
		const string t = c.get_next_line(':');
		const int n = get_value(c.get_next_line(), 1, 99);
		d.objects.push_back(make_pair(t, n));
	}
	for (int i = get_value(line.get_next_line(), 0, 64); i--; )
	{
		Cmulti_line c = line.get_next_line();
		const int z = get_action_id(c.get_next_line(':'));
		if (z == -1)
			assert(false);
		const int n = get_value(c.get_next_line(), 0, 99);
		d.actions.push_back(make_pair(z, n));
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
	memcpy(bin_data.data(), data.data(), 8192);
	convert_bin(bin_data.data());
	return 0;
}

int Cxcc_level::load_ini(const Cvirtual_binary& data, bool fast)
{
	Cvirtual_tfile f;
	f.load_data(data);
	t_section_id section;
	bool handle_section = false;
	for (int line_i = 1; !f.eof(); line_i++)
	{
		string s = f.read_line();
		int pos = s.find(';');
		if (pos != -1)
			s.erase(pos);
		boost::trim(s);
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
				string a = s.substr(0, pos);
				string b = s.substr(pos + 1, s.npos);
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
			xcc_log::write_line("Warning, line " + n(line_i) + " contains a value that's out of range");
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
	Cvirtual_binary d(bin_data.data(), 8192);
	deconvert_bin(reinterpret_cast<unsigned short*>(d.data_edit()));
	return d;
}

Cvirtual_binary Cxcc_level::save_ini() const
{
	stringstream os;

	os << '[' << section_code[si_basic] << "]\r\n";
	if (!basic_data.action.empty())
		os << basic_data_code[bdt_action] << '=' << basic_data.action << "\r\n";
	if (!basic_data.brief.empty())
		os << basic_data_code[bdt_brief]  << '=' << basic_data.brief << "\r\n";
	os << basic_data_code[bdt_build_level] << '=' << basic_data.build_level << "\r\n";
	os << basic_data_code[bdt_carry_over_money] << '=' << basic_data.carry_over_money / 100 << "\r\n";
	if (!basic_data.intro.empty())
		os << basic_data_code[bdt_intro] << '=' << basic_data.intro << "\r\n";
	if (!basic_data.lose.empty())
		os << basic_data_code[bdt_lose] << '=' << basic_data.lose << "\r\n";
	if (!basic_data.name.empty())
		os << basic_data_code[bdt_name] << '=' << basic_data.name << "\r\n";
	os << basic_data_code[bdt_percent] << '=' << basic_data.percent << "\r\n";
	os << basic_data_code[bdt_player] << '=' << side_code[basic_data.player] << "\r\n";
	if (!basic_data.theme.empty())
		os << basic_data_code[bdt_theme] << '=' << basic_data.theme << "\r\n";
	if (!basic_data.win.empty())
		os << basic_data_code[bdt_win] << '=' << basic_data.win << "\r\n";
	os << "\r\n";

	os << '[' << section_code[si_map] << "]\r\n"
		<< map_data_code[mdt_theater] << '=' << theater_code[map_data.theater] << "\r\n"
		<< map_data_code[mdt_x] << '=' << map_data.x << "\r\n"
		<< map_data_code[mdt_y] << '=' << map_data.y << "\r\n"
		<< map_data_code[mdt_cx] << '=' << map_data.cx << "\r\n"
		<< map_data_code[mdt_cy] << '=' << map_data.cy << "\r\n"
		<< "\r\n";

	if (!briefing_data.empty())
	{
		os << '[' << section_code[si_briefing] << "]\r\n";
		int index = 1;
		for (size_t i = 0, j; j = briefing_data.find("##", i); )
		{
			if (j == string::npos)
			{
				os << index++ << '=' << trim_copy(briefing_data.substr(i)) << "\r\n";
				break;
			}
			j += 2;
			os << index++ << '=' << trim_copy(briefing_data.substr(i, j - i)) << "\r\n";
			i = j;
		}
		os << "\r\n";
	}

	os << '[' << section_code[si_celltriggers] << "]\r\n";
	for (auto& i : celltrigger_data)
		os << i.first << '=' << i.second << "\r\n";
	os << "\r\n";

	os << '[' << section_code[si_teamtypes] << "]\r\n";
	for (auto& i : teamtype_data)
	{
		const t_teamtype_data_entry& d = i.second;
		os << i.first << '=' << side_code[d.side] << ',' << static_cast<bool>(d.flags & td_flags_link) << ",0," <<
			static_cast<bool>(d.flags & td_flags_force_move) << ',' << static_cast<bool>(d.flags & td_flags_autocreate) << ",0," <<
			d.u1 << ',' << d.c_teams << ",0,0," << d.objects.size() << ',';
		for (auto& i : d.objects)
			os << i.first << ':' << i.second << ',';
		os << d.actions.size() << ',';
		for (auto& i : d.actions)
			os << action_code[i.first] << ':' << i.second << ',';
		os << static_cast<bool>(d.flags & td_flags_replace) << ',' << static_cast<bool>(d.flags & td_flags_force_creation) << "\r\n";
	}
	os << "\r\n";

	os << '[' << section_code[si_triggers] << "]\r\n";
	for (auto& i : trigger_data)
	{
		const t_trigger_data_entry& d = i.second;
		os << i.first << '=' << cause_code[d.cause] << ',' << event_code[d.event] << ',' 
			<< d.count << ',' << side_code[d.side == -1 ? s_none : d.side] << ',' 
			<< d.teamtype << ',' << d.loop << "\r\n";
	}
	os << "\r\n";

	os << '[' << section_code[si_waypoints] << "]\r\n";
	for (int i = 0; i < 100; i++)
	{
		if (waypoint_data[i] != -1)
			os << i << '=' << waypoint_data[i] << "\r\n";
	}
	os << "\r\n";

	os << '[' << section_code[si_base] << "]\r\n";
	int index = 0;
	for (auto& i : structure_data)
	{
		if (i.flags & sd_flags_replace)
			os << nwzl(3, index++) << '=' << i.t->short_name << ',' << ((i.cell.get_cc() & 0xfc0) << 18 | (i.cell.get_cc() & 0x3f) << 8) << "\r\n";
	}
	os << "Count=" << index << "\r\n"
		<< "\r\n";

	os << '[' << section_code[si_infantry] << "]\r\n";
	index = 0;
	for (auto& i : infantry_data)
		os << index++ << '=' << side_code[i.side] << ',' << i.t->short_name << ',' << i.health << ',' << i.cell.get_cc() << ',' << i.cell.subcell() << ',' << action_code[i.action] << ',' << i.angle << ',' << i.trigger << "\r\n";
	os << "\r\n";

	os << '[' << section_code[si_structures] << "]\r\n";
	index = 0;
	for (auto& i : structure_data)
	{
		if (i.flags & sd_flags_start)
			os << index++ << '=' << side_code[i.side] << ',' << i.t->short_name << ',' << i.health << ',' << i.cell.get_cc() << ',' << i.angle << ',' << i.trigger << "\r\n";
	}
	os << "\r\n";

	os << '[' << section_code[si_units] << "]\r\n";
	index = 0;
	for (auto& i : unit_data)
		os << index++ << '=' << side_code[i.side] << ',' << i.t->short_name	<< ',' << i.health << ',' << i.cell.get_cc() << ',' << i.angle << ',' << action_code[i.action] << ',' << i.trigger << "\r\n";
	os << "\r\n";

	for (int i = 0; i < c_side_id; i++)
	{
		os << '[' << section_code[si_goodguy + i] << "]\r\n";
		os << side_data_code[sdt_allies] << '=';
		bool first = true;
		for (int j = 0; j < c_side_id; j++)
		{
			if (side_data[i].allies >> j & 1)
			{
				if (!first)
					os << ",";
				os << side_code[j];
				first = false;
			}
		}
		os << "\r\n";
		if (side_data[i].credits)
			os << side_data_code[sdt_credits] << '=' << side_data[i].credits / 100 << "\r\n";
		os << side_data_code[sdt_edge] << '=' << edge_code[side_data[i].edge] << "\r\n";
		os << "\r\n";
	}

	os << '[' << section_code[si_overlay] << "]\r\n";
	for (auto& i : overlay_data)
	{
		t_overlay_id v = static_cast<t_overlay_id>(i.second >> 8);
		if (is_tiberium(v))
			v = static_cast<t_overlay_id>((i.second & 0xff) << o_ti1);
		Cxcc_cell cell;
		cell.set_xcc(i.first);
		os << cell.get_cc() << '=' << overlay_code[v] << "\r\n";
	}
	os << "\r\n";

	os << '[' << section_code[si_terrain] << "]\r\n";
	for (auto& i : terrain_data)
	{
		Cxcc_cell cell;
		cell.set_xcc(i.first);
		os << cell.get_cc() << '=' << terrain_code[i.second >> 8] << ",none" << "\r\n";
	}
	os << "\r\n";
	return os.str();
}

void Cxcc_level::convert_bin(unsigned short* data) const
{
	Cxcc_templates::load_images(map_data.theater);
	for (int i = 0; i < 4096; i++)
		data[i] = Cxcc_templates::convert_bin_data((data[i] & 0xff) < 0xd8 ? data[i] : 0);
}

void Cxcc_level::deconvert_bin(unsigned short* data) const
{
	for (int i = 0; i < 4096; i++)
		data[i] = Cxcc_templates::deconvert_bin_data(data[i]);
}

bool Cxcc_level::has_overlay(int i, int x, int y, int v) const
{
	auto j = find_ptr(overlay_data, i + x + (y << 8));
	return j && *j >> 8 == v;
}

void Cxcc_level::process()
{
	for (int i = 0; i < 4096; i++)
	{
		int y = i >> 6;
		unsigned short& v = bin_data[i];
		switch (v >> 8)
		{
		case 0:
			v = i & 3 | (y & 3) << 2;
			break;
		case 2:
			v = 0x200 | i & 1 | (y & 1) << 1;
			break;
		}
	}
	for (auto& i : overlay_data)
	{
		t_overlay_id v = static_cast<t_overlay_id>(i.second >> 8);
		int cell = i.first;
		bool top = has_overlay(cell, 0, -1, v);
		bool bottom = has_overlay(cell, 0, 1, v);
		bool left = has_overlay(cell, -1, 0, v);
		bool right = has_overlay(cell, 1, 0, v);
		if (is_wall(v))
			overlay_data[cell] = v << 8 | left << 3 | bottom << 2 | right << 1 | top;
		else if (v == o_conc)
		{
			int w = cell & 1;
			if (w & 1)
			{
				if (top && right || has_overlay(cell,  1, -1, v) && right)
					w = bottom ? 3 : 10;
				else if (bottom && right)
					w = 8;
				else if (top && has_overlay(cell, 1, -1, v))
					w = 10;
			}
			else
			{
				if (top && left || has_overlay(cell, -1, -1, v) && left)
					w = bottom ? 2 : 11;
				else if (bottom && left || bottom && has_overlay(cell, -1, 1, v))
					w = 9;
				else if (top && has_overlay(cell, -1, -1, v))
					w = 11;
			}
			overlay_data[cell] = v << 8 | w;
		}
	}
	for (auto& i : base_data)
	{
		t_structure_data::iterator j;
		for (j = structure_data.begin(); j < structure_data.end(); j++)
		{
			if (i.first == j->cell.get_xcc() && i.second == j->t)
			{
				j->flags |= sd_flags_replace;
				break;
			}
		}
		if (j == structure_data.end())
		{
			t_structure_data_entry d;
			d.side = basic_data.player != s_goodguy ? s_goodguy : s_badguy;
			d.t = i.second;
			d.health = 256;
			d.cell.set_xcc(i.first);
			d.angle = 0;
			d.flags = sd_flags_replace;
			d.trigger = "none";
			structure_data.push_back(d);
		}
	}
	base_data.clear();
}

void Cxcc_level::clear()
{
	bin_data.assign(0);
	basic_data = t_basic_data();
	map_data = t_map_data();
	briefing_data.erase();

	for (int i = 0; i < c_side_id; i++)
	{
		side_data[i].allies = 1 << i;
		side_data[i].credits = 0;
		side_data[i].edge = e_north;
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
	waypoint_data.assign(-1);

	process();
}