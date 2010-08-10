#include "stdafx.h"
#include "pcx_file.h"

bool Cpcx_file::is_valid() const
{
	const t_pcx_header& h = header();
	int size = get_size();
	return !(sizeof(t_pcx_header) > size ||
		h.manufacturer != 10 ||
		h.version != 5 ||
		h.encoding != 1 ||
		h.cbits_pixel != 8 ||
		h.c_planes != 1 && h.c_planes != 3);
}

void Cpcx_file::decode(void* d) const
{
	pcx_decode(get_image(), reinterpret_cast<byte*>(d), header());
}

Cvirtual_image Cpcx_file::vimage() const
{
	Cvirtual_binary image;
	pcx_decode(get_image(), image.write_start(cb_image()), header());
	return Cvirtual_image(image, cx(), cy(), cb_pixel(), cb_pixel() == 1 ? *get_palet() : NULL);
}
