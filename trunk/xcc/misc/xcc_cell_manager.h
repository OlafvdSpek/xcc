#pragma once

#include "xcc_cell.h"
#include "xcc_level.h"

namespace xcc_cell_manager
{
	struct t_cell_info
	{
		dword c_entries;
		dword entry[16];
		dword next;
	};

	void clear();
	void add(const Cxcc_cell& cell, dword v);
	void add_all(const Cxcc_level& level);
	const t_cell_info* get_cell_info(const Cxcc_cell& cell);
	const t_cell_info* get_next(const t_cell_info* ci);
}