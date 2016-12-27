#pragma once

#include "xcc_cell.h"
#include "xcc_level.h"

namespace xcc_cell_manager
{
	struct t_cell_info
	{
		int c_entries;
		int entry[16];
		int next;
	};

	void clear();
	void add(const Cxcc_cell& cell, int v);
	void add_all(const Cxcc_level& level);
	const t_cell_info* get_cell_info(const Cxcc_cell& cell);
	const t_cell_info* get_next(const t_cell_info* ci);
}