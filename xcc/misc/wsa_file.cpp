#include "stdafx.h"
#include "pcx_decode.h"
#include "pcx_file_write.h"
#include "shp_decode.h"
#include "string_conversion.h"
#include "wsa_file.h"

int Cwsa_file::extract_as_pcx(const Cfname& name) const
{
	t_palet palet;
	memcpy(palet, get_palet(), sizeof(t_palet));
	convert_palet_18_to_24(palet);
	int error = 0;
	const int cx = get_cx();
	const int cy = get_cy();
	const int c_frames = get_c_frames();
	byte* frame = new byte[cx * cy];
	byte* s = new byte[64 << 10];
	byte* d = new byte[cx * cy * 2];
	memset(frame, 0, cx * cy);
	for (int i = 0; i < c_frames; i++)
	{
		if (get_offset(i))
		{
			decode80(get_frame(i), s);
			decode40(s, frame);
		}
		int cb_d = pcx_encode(frame, d, cx, cy, 1);
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
		if (error)
			break;
	}
	delete[] d;
	delete[] s;
	delete[] frame;
	return error;
}