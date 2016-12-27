#pragma once

#include <cc_structures.h>

namespace mix_database
{
	void add_name(t_game, const string& name, const string& description);
	string get_name(t_game, int id);
	string get_description(t_game, int id);
	int load();
};
