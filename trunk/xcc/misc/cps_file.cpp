#include "stdafx.h"
#include "cps_file.h"

#include "shp_decode.h"

bool Ccps_file::is_valid() const
{
	const t_cps_header& h = header();
	int size = get_size();
	if (sizeof(t_cps_header) > size ||
		h.image_size != 320 * 200 ||
		h.palet_size && h.palet_size != 0x300 ||
		h.zero)
		return false;
	switch (h.unknown)
	{
	/*
	case 3:
		return header.size == size;
	*/
	case 4:
		return 2 + h.size == size;
	default:
		return false;
	}
}

void Ccps_file::decode(void* d) const
{
	decode80(get_image(), reinterpret_cast<byte*>(d));
}

Cvirtual_image Ccps_file::vimage() const
{
	Cvirtual_binary image;
	decode(image.write_start(cx() * cy()));
	return Cvirtual_image(image, cx(), cy(), cb_pixel(), palet(), true);
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
	header.size = w - d.data() - 2;
	d.size(w - d.data());
	return d;
}