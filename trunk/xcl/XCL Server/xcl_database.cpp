// xcl_database.cpp: implementation of the Cxcl_database class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xcl_database.h"

#include <cmath>
#include "string_conversion.h"

static int gsku2lid(int gsku)
{
	switch (gsku & ~0xff)
	{
	case 0x1200:
		return 7;
	case 0x1f00:
		return 5;
	case 0x2100:
		return 1;
	case 0x2900:
		return 3;
	}
	return 0;
}

int Cxcl_database::pid(int lid, const string& name)
{
	Csql_query q(*this);
	q.write("select pid from xcl_players where lid = %s and name = %s");
	q.p(lid);
	q.pe(name);
	Csql_result result = q.execute();
	Csql_row row;
	if (row = result.fetch_row())
		return row.f_int(0);
	q.write("insert into xcl_players (lid, name) values (%s, lcase(%s))");
	q.p(lid);
	q.pe(name);
	q.execute();
	return insert_id();
}

int Cxcl_database::update_player(int cmp, int cty, const Cxcl_player& a, const Cxcl_player& b)
{
	int points_win = static_cast<int>(64 * (1 - 1 / (powf(10, static_cast<float>(b.points - a.points) / 400) + 1)) + 0.5);
	int points_loss = min(64 - points_win, a.points / 10);
	Csql_query q(*this);
	switch (cmp)
	{
	case 0x100:
		q.write("update xcl_players set win_count = win_count + 1, points = points + %s, points_max = greatest(points_max, points), countries = countries | %s where pid = %s");
		q.p(points_win);
		q.p(cty);
		q.p(a.pid);
		q.execute();
		return points_win;
	case 0x200:
	case 0x210:
	case 0x220:
		q.write("update xcl_players set loss_count = loss_count + 1, points = points - %s, countries = countries | %s where pid = %s");
		q.p(points_loss);
		q.p(cty);
		q.p(a.pid);
		q.execute();
		return -points_loss;
	}
	q.write("update xcl_players set countries = countries | %s where pid = %s");
	q.p(cty);
	q.p(a.pid);
	q.execute();
	return 0;
}

void Cxcl_database::insert_game(const Cgame_result& gr)
{
	int gid;
	int lid = gsku2lid(gr.get_int("gsku"));
	int trny = gr.get_int("trny");
	if (gr.plrs() < 2 || gr.plrs() > (trny == 1 ? 2 : 8)
		|| trny < 0 || trny > 2)
		return;
	switch (lid)
	{
	case 0:
		return;
	case 5:
	case 6:
		if (gr.get_int("dura") < 90)
			return;
		break;
	case 7:
	case 8:
		if (gr.get_int("dura") < 180
			|| trny < 1)
			return;
		break;
	default:
		if (!gr.get_int("afps")
			|| gr.get_int("dura") < 5 
			|| gr.get_int("dura") > 30 && gr.get_int("dura") < (gr.get_int("afps") < 45 ? 4050 / gr.get_int("afps") : 0)
			|| trny < 1)
			return;
	}
	Csql_query q(*this);
	q.write("select sid from xwi_serials where serial = md5(%s)");
	q.pe(gr.get_string("ser#"));
	Csql_row row = q.execute().fetch_row();
	if (!row)
		return;
	int sid = row.f_int(0);
	if (trny == 2)
		lid++;
	q.write("select gid from xcl_games where ws_gid = %s");
	q.p(gr.idno());
	Csql_result result = q.execute();
	if (row = result.fetch_row())
		gid = row.f_int(0);
	else
	{
		bool reject = false;
		int cmp[8];
		Cxcl_player players[8];
		int pc[8];
		int i;
		for (i = 0; i < gr.plrs(); i++)
		{
			if (trny == 2 && !gr.cid(i))
				return;
			q.write("select count(*) from bl where name = %s");
			q.pe(gr.nam(i));
			reject |= q.execute().fetch_row().f_int(0) > 0;
		}
		for (i = 0; i < gr.plrs(); i++)
		{
			cmp[i] = gr.oosy() ? 0 : gr.cmp(i);
			players[i] = trny == 2 ? player(lid, gr.cid(i)) : player(lid, gr.nam(i));
		}
		if (gr.plrs() > 2)
		{
			int won = -1;
			int lost = -1;
			int won_cty = 0;
			int lost_cty = 0;
			for (i = 0; i < gr.plrs(); i++)
				(gr.cmp(i) == 0x100 ? won : lost) = i;
			if (won == -1 || lost == -1)
				return;
			for (lost = 0; lost < gr.plrs() && gr.cid(lost) == gr.cid(won); lost++)
				;
			for (i = 0; i < gr.plrs(); i++)
				(gr.cid(i) == gr.cid(won) ? won_cty : lost_cty) |= 1 << gr.cty(i);
			q.write("select count(distinct a.gid) from xcl_games_players a inner join xcl_games_players b using (gid) where a.pc > 0 and a.cid = %s and b.cid = %s");
			q.p(players[won].pid);
			q.p(players[lost].pid);
			reject |= q.execute().fetch_row().f_int(0) >= 10;
			pc[won] = update_player(reject ? 0 : cmp[won], won_cty, players[won], players[lost]);
			pc[lost] = update_player(reject ? 0 : cmp[lost], lost_cty, players[lost], players[won]);
			for (i = 0; i < gr.plrs(); i++)
				pc[i] = gr.cid(i) == gr.cid(won) ? pc[won] : pc[lost];
		}
		else 
		{
			if (cmp[0] == 2 && cmp[1] == 2)
			{
				if (gr.get_int("spid"))
				{
					cmp[0] = 0x220;
					cmp[1] = 0x100;
				}
				else
				{
					cmp[0] = 0x100;
					cmp[1] = 0x220;
				}
			}
			else if (cmp[0] == cmp[1])
				reject = true;
			q.write(trny == 2
				? "select count(distinct a.gid) from xcl_games_players a inner join xcl_games_players b using (gid) where a.pc > 0 and a.cid = %s and b.cid = %s"
				: "select count(*) from xcl_games_players a inner join xcl_games_players b using (gid) where a.pc > 0 and a.pid = %s and not a.cid and b.pid = %s");
			q.p(players[cmp[0] != 0x100].pid);
			q.p(players[cmp[0] == 0x100].pid);
			reject |= q.execute().fetch_row().f_int(0) >= 10;
			for (i = 0; i < gr.plrs(); i++)
				pc[i] = update_player(reject ? 0 : cmp[i], 1 << gr.cty(i), players[i], players[1 - i]);
		}
		q.write("insert into xcl_games (afps, dura, gsku, oosy, scen, trny, ws_gid) values (%s, %s, %s, %s, lcase(%s), %s, %s)");
		q.p(gr.get_int("afps"));
		q.p(gr.get_int("dura"));
		q.p(gr.get_int("gsku") & ~0xff);
		q.p(gr.oosy());
		q.pe(gr.get_string("scen"));
		q.p(trny);
		q.p(gr.idno());
		q.execute();
		gid = insert_id();
		for (i = 0; i < gr.plrs(); i++)
		{
			q.write("insert into xcl_games_players (gid, pid, cid, cmp, col, cty, pc, ipa, sid, inb, unb, plb, blb, inl, unl, pll, bll, ink, unk, plk, blk, blc) values (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)");
			q.p(gid);
			q.p(trny == 2 ? pid(lid - 1, gr.nam(i)) : players[i].pid);
			q.p(trny == 2 ? players[i].pid : 0);
			q.p(cmp[i]);
			q.p(gr.get_int("col", i));
			q.p(gr.cty(i));
			q.p(pc[i]);
			q.p(gr.get_int("ipa", i)); 
			q.p(gr.get_int("spid") == i ? sid : 0);
			q.p(gr.get_int("inb", i)); 
			q.p(gr.get_int("unb", i)); 
			q.p(gr.get_int("plb", i)); 
			q.p(gr.get_int("blb", i)); 
			q.p(gr.get_int("inl", i)); 
			q.p(gr.get_int("unl", i)); 
			q.p(gr.get_int("pll", i)); 
			q.p(gr.get_int("bll", i)); 
			q.p(gr.get_int("ink", i)); 
			q.p(gr.get_int("unk", i)); 
			q.p(gr.get_int("plk", i)); 
			q.p(gr.get_int("blk", i)); 
			q.p(gr.get_int("blc", i)); 
			q.execute();
		}
	}
	q.write("insert into xcl_sid_input (gid, spid, sid) values (%s, %s, md5(%s))");
	q.p(gid);
	q.p(gr.get_int("spid"));
	q.pe(gr.get_string("ser#"));
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

Cxcl_player Cxcl_database::player(int lid, const string& name)
{
	Csql_query q(*this);
	q.write("select * from xcl_players where lid = %s and name = %s");
	q.p(lid);
	q.pe(name);
	Csql_result result = q.execute();
	Csql_row row;
	if (row = result.fetch_row())
		return Cxcl_player(row);
	q.write("insert into xcl_players (lid, name) values (%s, lcase(%s))");
	q.p(lid);
	q.pe(name);
	q.execute();
	return player(insert_id());
}

Cxcl_player Cxcl_database::player(int lid, int cid)
{
	Csql_query q(*this);
	q.write("select xcl_players.* from xcl_clans inner join xcl_players using (pid) where lid = %s and cid = %s");
	q.p(lid);
	q.p(cid);
	Csql_row row;
	if (row = q.execute().fetch_row())
		return Cxcl_player(row);
	q.write("select name from xwi_clans where cid = %s");
	q.p(cid);
	row = q.execute().fetch_row();
	q.write("insert into xcl_players (lid, name) values (%s, %s)");
	q.p(lid);
	if (row)
		q.pe(row.f(0));
	else
		q.p(cid);
	q.execute();
	int pid = insert_id();
	q.write("insert into xcl_clans (pid, cid) values (%s, %s)");
	q.p(pid);
	q.p(cid);
	q.execute();
	return player(pid);
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
	query("drop table if exists xcl_clans");
	query("drop table if exists xcl_games");
	query("drop table if exists xcl_games_players");
	query("drop table if exists xcl_input");
	query("drop table if exists xcl_maps");
	query("drop table if exists xcl_players");
	query("drop table if exists xcl_sid_input");
}

void Cxcl_database::update_ranks()
{
	for (int lid = 1; lid < 9; lid++)
	{
		Csql_query q(*this);
		q.write("select pid, rank from xcl_players where lid = %d order by points desc");
		q.p(lid);
		Csql_result result = q.execute();
		Csql_row row;
		for (int rank = 1; row = result.fetch_row(); rank++)
		{
			if (row.f_int(1) == rank)
				continue;
			q.write("update xcl_players set rank = %d, mtime = mtime where pid = %d");
			q.p(rank);
			q.p(row.f_int(0));
			q.execute();
		}
	}
}