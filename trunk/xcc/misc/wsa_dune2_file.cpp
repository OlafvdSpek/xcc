// wsa_dune2_file.cpp: implementation of the Cwsa_dune2_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wsa_dune2_file.h"

#include "image_file.h"
#include "shp_decode.h"
#include "string_conversion.h"

int Cwsa_dune2_file::extract_as_pcx(const Cfname& name, t_file_type ft, const t_palet _palet) const
{
	t_palet palet;
	convert_palet_18_to_24(_palet, palet);
	Cvirtual_binary frame;
	Cvirtual_binary s;
	memset(frame.write_start(cb_image()), 0, cb_image());
	Cfname t = name;
	for (int i = 0; i < cf(); i++)
	{
		if (get_offset(i))
		{
			decode80(get_frame(i), s.data_edit());
			decode40(s, frame.data_edit());
		}
		t.set_title(name.get_ftitle() + " " + nwzl(4, i));
		int error = image_file_write(ft, frame, palet, cx(), cy()).export(t);
		if (error)
			return error;
	}
	return 0;
}