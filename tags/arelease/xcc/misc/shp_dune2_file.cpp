// shp_dune2_file.cpp: implementation of the Cshp_dune2_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pcx_decode.h"
#include "pcx_file_write.h"
#include "shp_decode.h"
#include "shp_dune2_file.h"
#include "string_conversion.h"

int Cshp_dune2_file::extract_as_pcx(const Cfname& name, const t_palet _palet) const
{
	t_palet palet;
	convert_palet_18_to_24(_palet, palet);
	int error = 0;
	const int c_images = get_c_images();
	for (int i = 0; i < c_images; i++)
	{
		const int cx = get_cx(i);
		const int cy = get_cy(i);
		byte* d = new byte[cx * cy * 2];
		byte* image = new byte[cx * cy];
		if (is_compressed(i))
		{
			byte* d = new byte[get_image_header(i)->size_out];
			decode2(d, image, decode80(get_image(i), d));
			delete[] d;
		}
		else
			decode2(get_image(i), image, get_image_header(i)->size_out);
		int cb_d = pcx_encode(image, d, cx, cy, 1);
		delete[] image;
		Cpcx_file_write f;
		Cfname t = name;
		t.set_title(name.get_ftitle() + " " + nwzl(4, i));
		error = f.open_write(t);
		if (error)
			break;
		f.set_size(cx, cy, 1);
		error = f.write_header();
		if (!error)
			error = f.write_image(d, cb_d);
		if (!error)
			error = f.write_palet(palet);
		f.close();
		delete[] d;
		if (error)
			break;
	}
	return error;
}
