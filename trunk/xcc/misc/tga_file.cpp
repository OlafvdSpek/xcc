// tga_file.cpp: implementation of the Ctga_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tga_file.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int Ctga_file::decode(Cvirtual_image& d) const
{
	if (cb_pixel() == 1)
	{
		t_palet palet;
		for (int i = 0; i < 0x100; i++)
			palet[i].r = palet[i].g = palet[i].b = i;
		d.load(image(), cx(), cy(), cb_pixel(), palet);
	}
	else
		d.load(image(), cx(), cy(), cb_pixel(), NULL);
	if (d.cb_pixel() == 4)
		d.remove_alpha();
	if (d.cb_pixel() == 3)
		d.swap_rb();
	if (!get_header()->vertical)
		d.flip();
	
	return 0;
}

Cvirtual_file tga_file_write(const byte* image, int cx, int cy, int cb_pixel)
{
	Cvirtual_binary d;
	byte* w = d.write_start(sizeof(t_tga_header) + cx * cy * cb_pixel);
	t_tga_header& header = *reinterpret_cast<t_tga_header*>(w);
	memset(&header, 0, sizeof(t_tga_header));
	header.image_t = cb_pixel == 1 ? 3 : 2;
	header.cx = cx;
	header.cy = cy;
	header.cb_pixel = cb_pixel << 3;
	header.alpha = cb_pixel == 4 ? 8 : 0;
	header.vertical = true;
	w += sizeof(t_tga_header);
	if (cb_pixel == 1)
		memcpy(w, image, cx * cy * cb_pixel);
	else
	{
		const t_palet_entry* r = reinterpret_cast<const t_palet_entry*>(image);
		for (int i = 0; i < cx * cy; i++)
		{
			*w++ = r->b;
			*w++ = r->g;
			*w++ = r->r;
			r++;
		}
	}
	return d;
}

int tga_file_write(const string& name, const byte* image, int cx, int cy, int cb_pixel)
{
	return tga_file_write( image, cx, cy, cb_pixel).export(name);
}