#pragma once

struct t_mix_map_list_entry
{
	string name;
	string fname;
	int id;
	int parent;
};

using t_mix_map_list = map<int, t_mix_map_list_entry>;
