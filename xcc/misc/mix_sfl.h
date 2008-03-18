#pragma once

#include "cc_structures.h"

namespace mix_sfl
{
	void clear(t_game game);
	bool contains(t_game game, int id);
	void erase(t_game game, int id);
	void insert(t_game game, int id);
	int load();
	int save();
};
