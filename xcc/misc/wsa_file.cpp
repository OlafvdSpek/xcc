#include "stdafx.h"
#include "wsa_file.h"

#include "image_file.h"
#include "shp_decode.h"
#include "string_conversion.h"

int Cwsa_file::extract_as_pcx(const Cfname& name, t_file_type ft) const
{
	t_palet palet;
	memcpy(palet, get_palet(), sizeof(t_palet));
	convert_palet_18_to_24(palet);
	const int cx = get_cx();
	const int cy = get_cy();
	const int c_frames = get_c_frames();
	Cvirtual_binary frame;
	Cvirtual_binary s;
	memset(frame.write_start(cx * cy), 0, cx * cy);
	Cfname t = name;
	for (int i = 0; i < c_frames; i++)
	{
		if (get_offset(i))
		{
			decode80(get_frame(i), s.write_start(64 << 10));
			decode40(s, frame.data_edit());
		}
		t.set_title(name.get_ftitle() + " " + nwzl(4, i));
		int error = image_file_write(ft, frame, palet, cx, cy).export(t);
		if (error)
			return error;
	}
	return 0;
}