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

#include "stdafx.h"
#include "xcc_cell_manager.h"

xcc_cell_manager::t_cell_info cell_info[0x80][0x40];

void xcc_cell_manager::clear()
{
	ZeroMemory(cell_info, sizeof(cell_info));
}

void xcc_cell_manager::add(const Cxcc_cell& cell, int v)
{
	t_cell_info* ci = &cell_info[cell.y >> 10][cell.x >> 10];
	while (ci->c_entries == 16)
	{
		if (!ci->next)
		{
			bool found = false;
			for (int j = 0; j < 0x40; j++)
			{
				for (int i = 0; i < 0x40; i++)
				{
					if (!cell_info[64 | j][i].c_entries)
					{
						ci->next = i | (64 | j) << 8;
						found = true;
						break;
					}
				}
				if (found)
					break;
			}
		}
		ci = &cell_info[ci->next >> 8][ci->next & 0xff];
	}
	for (int i = 0; i < 16; i++)
	{
		if (!ci->entry[i])
		{
			ci->entry[i] = v;
			break;
		}
	}
	ci->c_entries++;
}

void xcc_cell_manager::add_all(const Cxcc_level& level)
{
	clear();
	{
		int index = 0;
		for (auto& i : level.infantry_data)
			add(i.cell, oi_infantry << 24 | index++);
	}
	{
		int index = 0;
		for (auto& i : level.structure_data)
			add(i.cell, oi_structure << 24 | index++);
	}
	{
		int index = 0;
		for (auto& i : level.unit_data)
			add(i.cell, oi_unit << 24 | index++);
	}
	for (auto& i : level.terrain_data)
	{
		Cxcc_cell cell;
		cell.set_xcc(i.first);
		add(cell, oi_terrain << 24 | (cell.y & 0xff00) | (cell.x >> 8));
	}
	for (auto& i : level.overlay_data)
	{
		Cxcc_cell cell;
		cell.set_xcc(i.first);
		add(cell, oi_overlay << 24 | (cell.y & 0xff00) | (cell.x >> 8));
	}
}

const xcc_cell_manager::t_cell_info* xcc_cell_manager::get_cell_info(const Cxcc_cell& cell)
{
	return &cell_info[cell.y >> 10][cell.x >> 10];
}

const xcc_cell_manager::t_cell_info* xcc_cell_manager::get_next(const t_cell_info* ci)
{
	return ci->next ? &cell_info[ci->next >> 8][ci->next & 0xff] : NULL;
}
