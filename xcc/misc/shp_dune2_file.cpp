#include "stdafx.h"
#include "shp_dune2_file.h"

#include "image_file.h"
#include "shp_decode.h"
#include "string_conversion.h"

bool Cshp_dune2_file::is_valid() const
{
	const t_shp_dune2_header& h = header();
	int size = get_size();
	if (sizeof(t_shp_dune2_header) + 4 > size || h.c_images < 1 || h.c_images > 1000 || sizeof(t_shp_dune2_header) + get_cb_ofs() * h.c_images > size)
		return false;
	for (int i = 0; i < get_c_images(); i++)
	{
		if (get_ofs(i) < 0 || get_ofs(i) + sizeof(t_shp_dune2_image_header) > min(size, 0xFFFF))
			return false;
		const t_shp_dune2_image_header& image_header = *get_image_header(i);
		if (image_header.compression & ~3 ||
			!image_header.cx || 
			!image_header.cy ||
			image_header.cy != image_header.cy2 ||
			image_header.size_in > size - get_ofs(i))
			return false;
	}
	return true;
}

int Cshp_dune2_file::extract_as_pcx(const Cfname& name, t_file_type ft, const t_palet _palet) const
{
	t_palet palet;
	convert_palet_18_to_24(_palet, palet);
	for (int i = 0; i < get_c_images(); i++)
	{
		const int cx = get_cx(i);
		const int cy = get_cy(i);
		Cvirtual_binary image;
		if (is_compressed(i))
		{
			byte* d = new byte[get_image_header(i)->size_out];
			decode2(d, image.write_start(cx * cy), decode80(get_image(i), d), get_reference_palet(i));
			delete[] d;
		}
		else
			decode2(get_image(i), image.write_start(cx * cy), get_image_header(i)->size_out, get_reference_palet(i));
		Cfname t = name;
		t.set_title(name.get_ftitle() + " " + nwzl(4, i));
		if (int error = image_file_write(t, ft, image.data(), palet, cx, cy))
			return error;
	}
	return 0;
}
