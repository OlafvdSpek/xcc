// tmp_ra_file.cpp: implementation of the Ctmp_ra_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tmp_ra_file.h"

#include "image_file.h"

Cvirtual_file Ctmp_ra_file::extract_as_pcx(t_file_type ft, const t_palet _palet) const
{
	t_palet palet;
	memcpy(palet, _palet, sizeof(t_palet));
	convert_palet_18_to_24(palet);
	int cx = get_cblocks_x();
	int cy = get_cblocks_y();
	int c_tiles = get_c_tiles();
	if (cx == 1 && cy == 1)
		cy = c_tiles;
	int cb_image = 24 * cx * 24 * cy;
	Cvirtual_binary image;
	memset(image.write_start(cb_image), 0, cb_image);
	int i = 0;
	for (int ty = 0; ty < cy; ty++)
	{
		for (int tx = 0; tx < cx; tx++)
		{
			if (get_index1()[i] != 0xff)
			{
				const byte* r = get_image(i);
				byte* w = image.data_edit() + 24 * (tx + 24 * cx * ty);
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
	return image_file_write(ft, image, palet, 24 * cx, 24 * cy);
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