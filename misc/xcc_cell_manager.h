/*
    XCC Utilities and Library
    Copyright (C) 2000  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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