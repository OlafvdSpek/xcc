#include "stdafx.h"
#include "xcc_cell_manager.h"

xcc_cell_manager::t_cell_info cell_info[0x80][0x40];

void xcc_cell_manager::clear()
{
	ZeroMemory(cell_info, sizeof(cell_info));
}

void xcc_cell_manager::add(const Cxcc_cell& cell, dword v)
{
	t_cell_info* ci = &cell_info[cell.get_y() >> 10][cell.get_x() >> 10];
	while (ci->c_entries == 16)
	{
		if (!ci->next)
		{
			bool found = false;
			for (long j = 0; j < 0x40; j++)
			{
				for (long i = 0; i < 0x40; i++)
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
	for (long i = 0; i < 16; i++)
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
		// overlay
		for (t_overlay_data::const_iterator i = level.overlay_data.begin(); i != level.overlay_data.end(); i++)
		{
			Cxcc_cell cell;
			cell.set_xcc(i->first);
			add(cell, oi_overlay << 24 | (cell.get_y() & 0xff00) | (cell.get_x() >> 8));
		}
	}
	{
		// smudge
	}
	{
		// terrain
		for (t_terrain_data::const_iterator i = level.terrain_data.begin(); i != level.terrain_data.end(); i++)
		{
			Cxcc_cell cell;
			cell.set_cc(i->first);
			add(cell, oi_terrain << 24 | (cell.get_y() & 0xff00) | (cell.get_x() >> 8));
		}
	}
	{
		// infantry
		long index = 0;
		for (t_infantry_data::const_iterator i = level.infantry_data.begin(); i != level.infantry_data.end(); i++)
		{
			add(i->cell, oi_infantry << 24 | index++);
		}
	}
	{
		// structure
		long index = 0;
		for (t_structure_data::const_iterator i = level.structure_data.begin(); i != level.structure_data.end(); i++)
		{
			add(i->cell, oi_structure << 24 | index++);
		}
	}
	{
		// unit
		long index = 0;
		for (t_unit_data::const_iterator i = level.unit_data.begin(); i != level.unit_data.end(); i++)
		{
			add(i->cell, oi_unit << 24 | index++);
		}
	}
}

const xcc_cell_manager::t_cell_info* xcc_cell_manager::get_cell_info(const Cxcc_cell& cell)
{
	return &cell_info[cell.get_y() >> 10][cell.get_x() >> 10];
}

const xcc_cell_manager::t_cell_info* xcc_cell_manager::get_next(const t_cell_info* ci)
{
	if (!ci->next)
		return 0;
	return &cell_info[ci->next >> 8][ci->next & 0xff];
}
