#include "stdafx.h"
#include "cps_file.h"

#include "shp_decode.h"

void Ccps_file::decode(void* d) const
{
	decode80(get_image(), reinterpret_cast<byte*>(d));
}

Cvirtual_file Ccps_file::extract_as_pcx(t_file_type ft, const t_palet _palet) const
{
	t_palet palet;
	if (has_palet())
		memcpy(palet, get_palet(), sizeof(t_palet));
	else
		memcpy(palet, _palet, sizeof(t_palet));
	convert_palet_18_to_24(palet);
	Cvirtual_binary image;
	decode80(get_image(), image.write_start(320 * 200));
	return image_file_write(ft, image, palet, 320, 200);
}

Cvirtual_binary cps_file_write(const byte* s, const t_palet_entry* palet)
{
	Cvirtual_binary d;
	byte* w = d.write_start(128 << 10);
	t_cps_header& header = *reinterpret_cast<t_cps_header*>(w);
	header.unknown = 4;
	header.image_size = 320 * 200;
	header.zero = 0;
	header.palet_size = palet ? sizeof(t_palet) : 0;
	w += sizeof(t_cps_header);
	if (palet)
	{
		memcpy(w, palet, sizeof(t_palet));
		w += sizeof(t_palet);
	}
	w += encode80(s, w, 320 * 200);
	header.size = w - d - 2;
	d.size(w - d);
	return d;
}