// xcl_database.cpp: implementation of the Cxcl_database class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xcl_database.h"

#include <cmath>

int Cxcl_database::pid(const string& name)
{
	Csql_query q(*this);
	q.write("select pid from xcl_players where name = %s");
	q.pe(name);
	Csql_result result = q.execute();
	Csql_row row;
	if (row = result.fetch_row())
		return row.f_int(0);
	q.write("insert into xcl_players (name) values (lcase(%s))");
	q.pe(name);
	q.execute();
	return mysql_insert_id(&handle());
}

int Cxcl_database::update_player(int pid, int cmp, const Cxcl_player& a, const Cxcl_player& b)
{
	int points_win = 64 * (1 - 1 / (powf(10, static_cast<float>(b.points - a.points) / 400) + 1));
	int points_loss = min(64 - points_win, a.points / 10);
	Csql_query q(*this);
	switch (cmp)
	{
	case 0x100:
		q.write("update xcl_players set win_count = win_count + 1, points = points + %s where pid = %s");
		q.p(points_win);
		q.p(pid);
		q.execute();
		return points_win;
	case 0x200:
	case 0x210:
		q.write("update xcl_players set loss_count = loss_count + 1, points = points - %s where pid = %s");
		q.p(points_loss);
		q.p(pid);
		q.execute();
		return -points_loss;
	}
	return 0;
}

void Cxcl_database::insert_game(const Cgame_result& gr)
{
	if (gr.get_int("dura") < 90
		|| !gr.get_int("trny"))
		return;
	Csql_query q(*this);
	q.write("select count(*) from xcl_games where ws_gid = %s");
	q.p(gr.get_int("idno"));
	if (q.execute().fetch_row())
		return;
	int pids[4];
	Cxcl_player players[4];
	int pc[4];
	int i;
	pids[0] = pid(gr.get_string("nam0"));
	pids[1] = pid(gr.get_string("nam1"));
	for (i = 0; i < 2; i++)
		players[i] = player(pids[i]);
	for (i = 0; i < 2; i++)
		pc[i] = gr.get_int("oosy") ? update_player(pids[i], gr.get_int("cmp", i), players[i], players[1 - i]) : 0;
	q.write("insert into xcl_games (afps, dura, gsku, oosy, scen, trny, a_pid, a_cmp, a_col, a_cty, a_pc, b_pid, b_cmp, b_col, b_cty, b_pc, ws_gid) values (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)");
	q.p(gr.get_int("afps"));
	q.p(gr.get_int("dura"));
	q.p(gr.get_int("gsku"));
	q.p(gr.get_int("oosy"));
	q.pe(gr.get_string("scen"));
	q.p(gr.get_int("trny"));
	for (i = 0; i < 2; i++)
	{
		q.p(pids[i]);
		q.p(gr.get_int("cmp", i));
		q.p(gr.get_int("col", i));
		q.p(gr.get_int("cty", i));
		q.p(pc[i]);
	}
	q.p(gr.get_int("idno"));
	q.execute();
}

void Cxcl_database::insert_game(const Cvirtual_binary& s)
{
	Cgame_result gr;
	if (!gr.write(s))
		insert_game(gr);
}

Cxcl_player Cxcl_database::player(int pid)
{
	Csql_query q(*this);
	q.write("select * from xcl_players where pid = %s");
	q.p(pid);
	return Cxcl_player(q.execute().fetch_row());
}

void Cxcl_database::create_tables()
{
	query("create table if not exists xcl_games(gid int auto_increment primary key, afps int not null, dura int not null, gsku int not null, oosy int not null, scen varchar(32) not null, trny int not null, a_pid int not null, a_cmp int not null, a_col int not null, a_cty int not null, a_pc int not null, b_pid int not null, b_cmp int not null, b_col int not null, b_cty int not null, b_pc int not null, ws_gid int not null, mtime timestamp, key(a_pid), key(b_pid))");
	query("create table if not exists xcl_input (iid int auto_increment primary key, d blob not null, ipa varchar(15) not null, mtime timestamp)");
	query("create table if not exists xcl_maps (mid int auto_increment primary key, fname varchar(32) not null, name varchar(32) not null, unique (fname))");
	query("create table if not exists xcl_players(pid int auto_increment primary key, name varchar(9) not null, rank int not null, win_count int not null, loss_count int not null, points int not null, mtime timestamp, unique(name), key(rank))");
}

void Cxcl_database::drop_tables()
{
	query("drop table if exists xcl_games");
	query("drop table if exists xcl_input");
	query("drop table if exists xcl_maps");
	query("drop table if exists xcl_players");
}

void Cxcl_database::insert_maps()
{
	struct t_key
	{
		const char* name;
		const char* value;
	};
	t_key map_names[] = 
	{
		"mp01du.map", "South Pacific",
		"mp01t4.map", "South Pacific",
		"mp02t2.map", "Isle of War",
		"mp03t4.map", "Anytown, Amerika",
		"mp05du.map", "Heartland",
		"mp05mw.map", "Heartland",
		"mp05t4.map", "Heartland",
		"mp06mw.map", "Urban Rush",
		"mp06t2.map", "Urban Rush",
		"mp08mw.map", "Little Big Lake",
		"mp08t2.map", "Little Big Lake",
		"mp09du.map", "Canyon Fodder",
		"mp09t3.map", "Canyon Fodder",
		"mp10s4.map", "Depth Charge",
		"mp11t2.map", "Pinch Point",
		"mp12s4.map", "Lake Blitzen",
		"mp13du.map", "Montana DMZ",
		"mp13mw.map", "Montana DMZ",
		"mp13s4.map", "Montana DMZ",
		"mp14mw.map", "El Dorado",
		"mp14t2.map", "El Dorado",
		"mp15du.map", "Snow Valley",
		"mp15mw.map", "Snow Valley",
		"mp15s4.map", "Snow Valley",
		"mp16mw.map", "Snowball's Chance",
		"mp16s4.map", "Snowball's Chance",
		"mp17du.map", "Malibu Cliffs",
		"mp17mw.map", "Malibu Cliffs",
		"mp17t6.map", "Malibu Cliffs",
		"mp18du.map", "Cold War",
		"mp18s3.map", "Cold War",
		"mp19t4.map", "Golden State Fwy",
		"mp20t6.map", "Wild Animal Park",
		"mp21s2.map", "Alaskan Oil Spill",
		"mp22mw.map", "Arctic Circle",
		"mp22s8.map", "Arctic Circle",
		"mp23mw.map", "Hammer and Sickle",
		"mp23t4.map", "Hammer and Sickle",
		"mp24du.map", "Bonanza",
		"mp25du.map", "DEFCON 6",
		"mp25mw.map", "DEFCON 6",
		"mp25t6.map", "DEFCON 6",
		"mp26s6.map", "Bering Strait",
		"mp27du.map", "A Path Beyond II",
		"mp27mw.map", "A Path Beyond II",
		"mp27t8.map", "A Path Beyond II",
		"mp29mw.map", "The Alamo",
		"mp29u2.map", "The Alamo",
		"mp30mw.map", "Siberian Wastes",
		"mp30s6.map", "Siberian Wastes",
		"mp31s2.map", "May Day",
		"mp32du.map", "Heck Freezes Over",
		"mp32mw.map", "Heck Freezes Over",
		"mp32s8.map", "Heck Freezes Over",
		"mp33u4.map", "Paris Revisited",
		"mp34u4.map", "DC Uprising",
		"tn01mw.map", "Official Tournament Map A",
		"tn01t2.map", "Official Tournament Map A",
		"tn02mw.map", "Official Tournament Map",
		"tn02s4.map", "Official Tournament Map",
		"tn04mw.map", "Official Tournament Map B",
		"tn04t2.map", "Official Tournament Map B",

		"2peaks.map", "Twin Peaks",
		"arena33forever.map", "Arena 33 Forever",
		"austintx.map", "Austin, TX",
		"bldfeud.map", "Blood Feud",
		"bridgegap.map", "Bridging the Gap",
		"c1a01md.map", "Campaign 1 Map 1",
		"c1a02md.map", "Campaign 1 Map 2",
		"c1a03md.map", "Campaign 1 Map 3",
		"c2s01md.map", "Campaign 2 Map 1",
		"c2s02md.map", "Campaign 2 Map 2",
		"c2s03md.map", "Campaign 2 Map 3",
		"c3y01md.map", "Campaign 3 Map 1",
		"c3y02md.map", "Campaign 3 Map 2",
		"c3y03md.map", "Campaign 3 Map 3",
		"c4w01md.map", "Campaign 4 Map 1",
		"deathvalleygirl.map", "Death Valley Girl",
		"deathvalleygirlmw.map", "Death Valley Girl",
		"doubletrouble.map", "Double Trouble",
		"downtown.map", "Downtown, Cityville",
		"dryheat.map", "Dry Heat",
		"dryheatmw.map", "Dry Heat",
		"dunepatr.map", "Dune Patrol",
		"eastvsbest.map", "East vs Best",
		"facedown.map", "Face Down",
		"fight.map", "Let There Be Fight",
		"fourcorners.map", "Four Corners",
		"fourcornersmw.map", "Four Corners",
		"frstbite.map", "Frostbite",
		"groundze.map", "Ground Zero",
		"groundzemw.map", "Ground Zero",
		"hidvally.map", "Hidden Valley",
		"hillbtwn.map", "A Hill Between",
		"isleofoades.map", "Isle Of Oades",
		"manhatta.map", "Manhattan Mayhem",
		"monumentvalley.map", "Monument Valley",
		"monumentvalleymw.map", "Monument Valley",
		"mountmoras.map", "Mount Rush More",
		"nearoref.map", "Near Ore Far",
		"nowimps.map", "No Wimps",
		"offensedefense.map", "Offense Defense",
		"ottersrevenge.map", "Otters Revenge",
		"pcofdune.map", "Little Piece of Dune",
		"rushhr.map", "Rush Hour",
		"saharami.map", "Sahara Mirage",
		"saharamimw.map", "Sahara Mirage",
		"sedonapass.map", "Sedona Pass",
		"sedonapassmw.map", "Sedona Pass",
		"topothehill.map", "Top o'the Hill",
		"tourofegypt.map", "Tour Of Egypt",
		"trailerpark.map", "Trailer Park",
		"triplecrossed.map", "Triple Crossed",
		"turfwar.map", "Turfwar",
		"xamazon01.map", "Stormy Weather",
		"xarena.map", "Arena",
		"xbarrel.map", "Loaded Barrel",
		"xbayopigs.map", "Bay of Pigs",
		"xbermuda.map", "Bermuda Triangle",
		"xbreak.map", "Breakaway",
		"xcarville.map", "Carville's Convoy",
		"xdeadman.map", "Deadman's Ridge",
		"xdeath.map", "Death trap",
		"xdisaster.map", "Brink of Disaster",
		"xdustbowl.map", "Dustbowl",
		"xdustbowlmw.map", "Dustbowl",
		"xeb1.map", "City Under Siege",
		"xeb1mw.map", "City Under Siege",
		"xeb2.map", "Sinkhole",
		"xeb3.map", "Sovereign Land",
		"xeb4.map", "Country Swing",
		"xeb5.map", "Mount Olympus",
		"xgoldst.map", "Streets of Gold",
		"xgrinder.map", "Meat Grinder",
		"xhailmary.map", "Hail Mary",
		"xhills.map", "Head for the Hills",
		"xinvasion.map", "Invasion Confirmed",
		"xkaliforn.map", "Kalifornia",
		"xkiller.map", "Killer Instinct",
		"xlostlake.map", "Lost Lake",
		"xmp01du.map", "South Pacific",
		"xmp01t4.map", "South Pacific",
		"xmp02t2.map", "Isle of War",
		"xmp03t4.map", "Anytown, Amerika",
		"xmp05du.map", "Heartland",
		"xmp05mw.map", "Heartland",
		"xmp05t4.map", "Heartland",
		"xmp06mw.map", "Urban Rush",
		"xmp06t2.map", "Urban Rush",
		"xmp08mw.map", "Little Big Lake",
		"xmp08t2.map", "Little Big Lake",
		"xmp09du.map", "Canyon Fodder",
		"xmp09t3.map", "Canyon Fodder",
		"xmp10s4.map", "Depth Charge",
		"xmp11t2.map", "Pinch Point",
		"xmp12s4.map", "Lake Blitzen",
		"xmp13du.map", "Montana DMZ",
		"xmp13mw.map", "Montana DMZ",
		"xmp13s4.map", "Montana DMZ",
		"xmp14mw.map", "El Dorado",
		"xmp14t2.map", "El Dorado",
		"xmp15du.map", "Snow Valley",
		"xmp15mw.map", "Snow Valley",
		"xmp15s4.map", "Snow Valley",
		"xmp16mw.map", "Snowball's Chance",
		"xmp16s4.map", "Snowball's Chance",
		"xmp17du.map", "Malibu Cliffs",
		"xmp17mw.map", "Malibu Cliffs",
		"xmp17t6.map", "Malibu Cliffs",
		"xmp18du.map", "Cold War",
		"xmp18s3.map", "Cold War",
		"xmp19t4.map", "Golden State Fwy",
		"xmp20t6.map", "Wild Animal Park",
		"xmp21s2.map", "Alaskan Oil Spill",
		"xmp22mw.map", "Arctic Circle",
		"xmp22s8.map", "Arctic Circle",
		"xmp23mw.map", "Hammer and Sickle",
		"xmp23t4.map", "Hammer and Sickle",
		"xmp24du.map", "Bonanza",
		"xmp25du.map", "DEFCON 6",
		"xmp25mw.map", "DEFCON 6",
		"xmp25t6.map", "DEFCON 6",
		"xmp26s6.map", "Bering Strait",
		"xmp27du.map", "A Path Beyond II",
		"xmp27mw.map", "A Path Beyond II",
		"xmp27t8.map", "A Path Beyond II",
		"xmp29mw.map", "The Alamo",
		"xmp29u2.map", "The Alamo",
		"xmp30mw.map", "Siberian Wastes",
		"xmp30s6.map", "Siberian Wastes",
		"xmp31s2.map", "May Day",
		"xmp32du.map", "Heck Freezes Over",
		"xmp32mw.map", "Heck Freezes Over",
		"xmp32s8.map", "Heck Freezes Over",
		"xmp33u4.map", "Paris Revisited",
		"xmp34u4.map", "DC Uprising",
		"xnewhghts.map", "New Heights",
		"xnorest.map", "No Rest for the Wicked",
		"xoceansid.map", "Oceanside",
		"xpacific.map", "Pacific Heights",
		"xpacificmw.map", "Pacific Heights",
		"xpotomac.map", "Army of the Potomac",
		"xpowdrkeg.map", "Powder Keg",
		"xrockets.map", "Rockets Red Glare",
		"xroulette.map", "Russian Roulette",
		"xround.map", "Roundhouse Kick",
		"xseaofiso.map", "Sea of Isolation",
		"xshrapnel.map", "Shrapnel Mountain",
		"xtanyas.map", "Tanya's Training Grounds",
		"xterritor.map", "Territorial Imperative",
		"xtn01mw.map", "Official Tournament Map A",
		"xtn01t2.map", "Official Tournament Map A",
		"xtn02mw.map", "Official Tournament Map",
		"xtn02s4.map", "Official Tournament Map",
		"xtn04mw.map", "Official Tournament Map B",
		"xtn04t2.map", "Official Tournament Map B",
		"xtower.map", "Tower of Power",
		"xtowermw.map", "Tower of Power",
		"xtsunami.map", "Tsunami",
		"xvalley.map", "Valley of Gems",
		"xvalleymw.map", "Valley of Gems",
		"xxmas.map", "Happy Trails",
		"xyuriplot.map", "Yuri's Plot",
		NULL
	};
	t_key* i = map_names;
	while (i->name)
	{
		Csql_query q(*this);
		q.write("insert into xcl_maps (fname, name) values (%s, %s)");
		q.pe(i->name);
		q.pe(i->value);
		q.execute();
		i++;
	}
}
