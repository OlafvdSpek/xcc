#include "stdafx.h"
#include "pcx_decode.h"
#include "pcx_file_write.h"
#include "shp_decode.h"
#include "shp_ts_file.h"
#include "string_conversion.h"
#include "xcc_log.h"

int Cshp_ts_file::extract_as_pcx(const Cfname& name, const t_palet _palet) const
{
	t_palet palet;
	memcpy(palet, _palet, sizeof(t_palet));
	convert_palet_18_to_24(palet);
	int error = 0;
	const int global_cx = get_cx();
	const int global_cy = get_cy();
	const int c_images = get_c_images();
	/*
	if (cx != 60 || cy != 48 || c_images != 1)
		return 1;
	*/
	byte* image = new byte[global_cx * global_cy];
	byte* s = new byte[global_cx * global_cy];
	byte* d = new byte[global_cx * global_cy * 2];
	for (int i = 0; i < c_images; i++)
	{
		const int cx = get_cx(i);
		const int cy = get_cy(i);
		const byte* r;
		if (is_compressed(i))
		{
			decode3(get_image(i), image, cx, cy);
			r = image;
		}
		else
			r = get_image(i);
		memset(s, 0, global_cx * global_cy);
		byte* w = s + get_x(i) + global_cx * get_y(i);
		for (int y = 0; y < cy; y++)
		{
			memcpy(w, r, cx);
			r += cx;
			w += global_cx;
		}
		// xcc_log::write_line("<tr><td>" + name.get_ftitle() + "</td><td><img src=" + name.get_fname() + "></td></tr>");
		int cb_d = pcx_encode(s, d, global_cx, global_cy, 1);
		Cpcx_file_write f;
		Cfname t = name;
		t.set_title(name.get_ftitle() + " " + nwzl(4, i));
		error = f.open_write(t);
		if (error)
			break;
		f.set_size(global_cx, global_cy, 1);
		error = f.write_header();
		if (!error)
			error = f.write_image(d, cb_d);
		if (!error)
			error = f.write_palet(palet);
		f.close();
		if (error)
			break;
	}
	delete[] d;
	delete[] s;
	delete[] image;
	return error;
}