#include "stdafx.h"
#include "shp_file.h"

#include "image_file.h"
#include "shp_decode.h"
#include "shp_images.h"
#include "string_conversion.h"

int Cshp_file::extract_as_pcx(const Cfname& name, t_file_type ft, const t_palet _palet) const
{
	t_palet palet;
	memcpy(palet, _palet, sizeof(t_palet));
	convert_palet_18_to_24(palet);
	int error = 0;
	const int cx = get_cx();
	const int cy = get_cy();
	const int c_images = get_c_images();
	void* p;
	if (!shp_images::load_shp(*this, p))
	{
		Cfname t = name;
		for (int i = 0; i < c_images; i++)
		{
			// xcc_log::write_line("<tr><td>" + name.get_ftitle() + "</td><td><img src=td_icons/" + name.get_fname() + "></td></tr>");
			t.set_title(name.get_ftitle() + " " + nwzl(3, i));
			if (error = image_file_write(ft, shp_images::get_shp(p, i), palet, cx, cy).export(t))
				break;
		}
		shp_images::destroy_shp(p);
	}
	return error;
}

Cvirtual_binary shp_file_write(const byte* s, int cx, int cy, int c_images)
{
	Cvirtual_binary d;
	const byte* r = s;
	byte* w = d.write_start(sizeof(t_shp_ts_header) + (sizeof(t_shp_ts_image_header) + cx * cy) * c_images);
	t_shp_header& header = *reinterpret_cast<t_shp_header*>(w);
    header.c_images = c_images;
    header.unknown1 = 0;
    header.unknown2 = 0;
    header.cx = cx;
    header.cy = cy;
    header.unknown3 = 0;
	w += sizeof(t_shp_header);
	int* index = reinterpret_cast<int*>(w);
	w += 8 * (c_images + 2);
	for (int i = 0; i < c_images; i++)
	{
		*index++ = 0x80000000 | w - d;
		*index++ = 0;
		w += encode80(r, w, cx * cy);
		r += cx * cy;
	}
	*index++ = w - d;
	*index++ = 0;
	*index++ = 0;
	*index++ = 0;
	d.size(w - d);
	return d;
}