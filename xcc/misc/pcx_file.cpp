// pcx_file.cpp: implementation of the Cpcx_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pcx_file.h"

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
