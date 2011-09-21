#include "stdafx.h"
#include "cc_file.h"
#include "mix_sfl.h"
#include "xcc_dirs.h"

typedef set<int> t_file_list;

t_file_list ts_fl, ra2_fl;

static string get_fname()
{
	return xcc_dirs::get_data_dir() + "standard file list.dat";
}

void read(const int*& r, t_file_list& fl)
{
	int count = *r++;
	while (count--)
		fl.insert(*r++);
}

int mix_sfl::load()
{
  Ccc_file f(true);
  if (f.open(get_fname()))
    return 1;
  if (f.get_size() < 8)
    return 1;
  const int* r = reinterpret_cast<const int*>(f.get_data());
  read(r, ts_fl);
  read(r, ra2_fl);
  return 0;
}

void write(int*& w, const t_file_list& fl)
{
	*w++ = fl.size();
	for (t_file_list::const_iterator j = fl.begin(); j != fl.end(); j++)
		*w++ = *j;
}

int mix_sfl::save()
{
	int* d = new int[2 + ts_fl.size() + ra2_fl.size()];
	int* w = d;
	write(w, ts_fl);
	write(w, ra2_fl);
	int error = file32_write(get_fname(), d, w - d << 2);
	delete[] d;
	return error;
}

void mix_sfl::clear(t_game game)
{
	switch (game)
	{
	case game_ts:
		ts_fl.clear();
		break;
	case game_ra2:
		ra2_fl.clear();
		break;
	}
}

void mix_sfl::insert(t_game game, int id)
{
	switch (game)
	{
	case game_ts:
		ts_fl.insert(id);
		break;
	case game_ra2:
		ra2_fl.insert(id);
		break;
	}
}

void mix_sfl::erase(t_game game, int id)
{
	switch (game)
	{
	case game_ts:
		ts_fl.erase(id);
		break;
	case game_ra2:
		ra2_fl.erase(id);
		break;
	}
}

bool mix_sfl::contains(t_game game, int id)
{
	switch (game)
	{
	case game_ts:
		return ts_fl.count(id);
	case game_ra2:
		return ra2_fl.count(id);
	default:
		return false;
	}
}