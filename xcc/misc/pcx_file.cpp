// pcx_file.cpp: implementation of the Cpcx_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pcx_file.h"

bool Cpcx_file::is_valid() const
{
	const t_pcx_header& header = *get_header();
	int size = get_size();
	return !(sizeof(t_pcx_header) > size ||
		header.manufacturer != 10 ||
		header.version != 5 ||
		header.encoding != 1 ||
		header.cbits_pixel != 8 ||
		header.c_planes != 1 && header.c_planes != 3);
}

void Cpcx_file::decode(void* d) const
{
	pcx_decode(get_image(), reinterpret_cast<byte*>(d), *get_header());
}

Cvirtual_image Cpcx_file::vimage() const
{
	Cvirtual_binary image;
	pcx_decode(get_image(), image.write_start(cb_image()), *get_header());
	return Cvirtual_image(image, cx(), cy(), cb_pixel(), cb_pixel() == 1 ? *get_palet() : NULL);
}
