#pragma once

struct t_mix_map_list_entry
{
	string name;
	string fname;
	int id;
	int parent;
};

typedef map<int, t_mix_map_list_entry> t_mix_map_list;