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
#include "tmp_ra_file.h"

#include "image_file.h"

void Ctmp_ra_file::decode(void* d) const
{
	int cx = get_cblocks_x();
	int cy = get_cblocks_y();
	int c_tiles = get_c_tiles();
	if (cx == 1 && cy == 1)
		cy = c_tiles;
	memset(d, 0, cb_image());
	int i = 0;
	for (int ty = 0; ty < cy; ty++)
	{
		for (int tx = 0; tx < cx; tx++)
		{
			if (get_index1()[i] != 0xff)
			{
				const byte* r = get_image(i);
				byte* w = reinterpret_cast<byte*>(d) + 24 * (tx + 24 * cx * ty);
				for (int y = 0; y < 24; y++)
				{
					memcpy(w, r, 24);
					r += 24;
					w += 24 * cx;
				}
			}
			i++;
		}
	}
}

int tmp_ra_file_write(const byte* s, byte* d, int cx, int cy)
{
	if (cx % 24 || cy % 24)
		return 0;
	const byte* r = s;
	byte* w = d;
	t_tmp_ra_header& header = *reinterpret_cast<t_tmp_ra_header*>(w);
	header.cx = 24;
	header.cy = 24;
	header.c_tiles;
	header.zero1 = 0;
	header.cblocks_x = cx / 24;
	header.cblocks_y = cy / 24;
	header.size;
	header.image_offset;
	header.zero2 = 0;
	header.unknown1;
	header.index2;
	header.unknown2;
	header.index1;
	w += sizeof(t_tmp_ra_header);
	return w - d;
}