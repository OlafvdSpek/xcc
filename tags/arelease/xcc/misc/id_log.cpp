// id_log.cpp: implementation of the id_log class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <cc_file.h>
#include <fstream>
#include <id_log.h>
#include <map>
#include <mix_file.h>
#include <string_conversion.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

struct t_idinfo
{
	string name;
	string description;
};

typedef map<int, t_idinfo, less<int> > t_id_list;

t_id_list td_list, ra_list, ts_list, dune2_list, ra2_list;

static t_id_list& get_list(t_game game)
{
	switch (game)
	{
	case game_ra:
		return ra_list;
	case game_ts:
		return ts_list;
	case game_dune2:
		return dune2_list;
	case game_ra2:
		return ra2_list;
	default:
		return td_list;
	}
}

static void read_list(t_game game, const char*& s)
{
	t_id_list& d = get_list(game);
	int count = *reinterpret_cast<const int*>(s);
	s += 4;
	t_idinfo idinfo;
	while (count--)
	{
		idinfo.name = s;
		s += idinfo.name.length() + 1;
		idinfo.description = s;
		s += idinfo.description.length() + 1;
		d[Cmix_file::get_id(game, idinfo.name)] = idinfo;
	}
}

int id_log::open_binary(const string& fname)
{
	if (!td_list.empty() || !ra_list.empty() || !ts_list.empty())
		return 0;
	Ccc_file f(true);
	if (f.open(fname))
		return 1;
	if (f.get_size() < 12)
	{
		f.close();
		return 1;
	}
	const char* data = reinterpret_cast<const char*>(f.get_data());
	read_list(game_td, data);
	read_list(game_ra, data);
	read_list(game_ts, data);
	read_list(game_ra2, data);
	f.close();
	if (0)
	{
		ofstream log_f("c:\\log.txt");
		for (t_id_list::const_iterator i = ts_list.begin(); i != ts_list.end(); i++)
			log_f << i->second.name << '\t' << i->second.description << endl;
	}
	return 0;
	char name[12] = "scg00ea.bin";
	const char char1[] = "bgjm";
	const char char2[] = "ew";
	const char char3[] = "abc";
	for (long i = 0; i < 2; i++)
	{
		if (i)
			strcpy(name + 8, "ini");
		for (long j = 0; j < 4; j++)
		{
			name[2] = char1[j];
			for (long k = 0; k < 100; k++)
			{
				memcpy(name + 3, nwzl(2, k).c_str(), 2);
				for (long l = 0; l < 2; l++)
				{
					name[5] = char2[l];
					for (long m = 0; m < 3; m++)
					{
						name[6] = char3[m];
						add_name(game_td, name, "");
						add_name(game_ra, name, "");
						add_name(game_ts, name, "");
					}
				}
			}
		}
	}
	return 0;
}

void id_log::add_name(t_game game, const string& name, const string& description)
{
	t_idinfo idinfo;
	idinfo.name = name;
	idinfo.description = description;
	get_list(game)[Cmix_file::get_id(game, name)] = idinfo;
}

string id_log::get_name(t_game game, int id)
{
	t_id_list& list = get_list(game);
	t_id_list::iterator i = list.find(id);
	/*
	if (game == game_ts && i == list.end())
		return get_name(game_ra2, id);
	*/
	return i == list.end() ? "" : i->second.name;
}

string id_log::get_description(t_game game, int id)
{
	t_id_list& list = get_list(game);
	t_id_list::iterator i = list.find(id);
	return i == list.end() ? "" : i->second.description;
}