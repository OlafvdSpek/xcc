#pragma once

#include <cc_structures.h>
#include <string>

namespace mix_database
{
	void add_name(t_game, const std::string& name, const std::string& description);
	std::string get_name(t_game, int id);
	std::string get_description(t_game, int id);
	int load();
};
