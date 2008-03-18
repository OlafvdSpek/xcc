#include "stdafx.h"
#include "tga_file.h"

bool Ctga_file::is_valid() const
{
	const t_tga_header& header = *get_header();
	int size = get_size();
	return !(sizeof(t_tga_header) > size
		|| header.map_t
		|| header.image_t != 2 && header.image_t != 3
		|| header.map_first
		|| header.map_size
		|| header.cb_pixel != 8 && header.cb_pixel != 16 && header.cb_pixel != 24 && header.cb_pixel != 32
		|| get_header()->horizontal
		|| sizeof(t_tga_header) + cx() * cy() * cb_pixel() > size);
}

int Ctga_file::decode(Cvirtual_image& d) const
{
	switch (cb_pixel())
	{
	case 1:
		{
			t_palet palet;
			for (int i = 0; i < 0x100; i++)
				palet[i].r = palet[i].g = palet[i].b = i;
			d.load(image(), cx(), cy(), cb_pixel(), palet);
		}
		break;
	case 2:
		{
			d.load(NULL, cx(), cy(), 3, NULL);
			const __int16* r = reinterpret_cast<const __int16*>(image());
			t_palet_entry* w = reinterpret_cast<t_palet_entry*>(d.image_edit());
			for (int i = 0; i < cx() * cy(); i++)
			{
				int v = *r++;
				w->r = (v >> 10 & 0x1f) * 255 / 31;
				w->g = (v >> 5 & 0x1f) * 255 / 31;
				w->b = (v & 0x1f) * 255 / 31;
				w++;
			}
		}
		break;
	default:
		d.load(image(), cx(), cy(), cb_pixel(), NULL);
		switch (d.cb_pixel())
		{
		case 4:
			d.remove_alpha();
		case 3:
			d.swap_rb();
			break;			
		}		

	}
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

Cvirtual_file tga_file_write(const byte* image, int cx, int cy, const t_palet_entry* palet)
{
	Cvirtual_image vi;
	vi.load(image, cx, cy, 1, palet);
	vi.increase_color_depth(3);
	return vi.save(ft_tga);
}
