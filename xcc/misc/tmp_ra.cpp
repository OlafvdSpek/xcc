// tmp_ra_file.cpp: implementation of the Ctmp_ra_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pcx_decode.h"
#include "pcx_file_write.h"
#include "tmp_ra_file.h"

int Ctmp_ra_file::extract_as_pcx(const Cfname& name, const t_palet _palet) const
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
	byte* image = new byte[cb_image];
	memset(image, 0, cb_image);
	int i = 0;
	for (int ty = 0; ty < cy; ty++)
	{
		for (int tx = 0; tx < cx; tx++)
		{
			if (get_index1()[i] != 0xff)
			{
				const byte* r = get_image(i);
				byte* w = image + 24 * (tx + 24 * cx * ty);
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
	byte* d = new byte[cb_image * 2];
	int cb_d = pcx_encode(image, d, 24 * cx, 24 * cy, 1);
	Cpcx_file_write f;
	int error = f.open_write(name);
	if (!error)
	{
		f.set_size(24 * cx, 24 * cy, 1);
		error = f.write_header();
		if (!error)
			error = f.write_image(d, cb_d);
		if (!error)
			error = f.write_palet(palet);
		f.close();
	}
	delete[] d;
	delete[] image;
	return error;
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