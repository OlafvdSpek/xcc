// pcx_file.cpp: implementation of the Cpcx_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pcx_file.h"
#include "png_file.h"

void Cpcx_file::decode(void* d) const
{
	pcx_decode(get_image(), reinterpret_cast<byte*>(d), *get_header());
}

void Cpcx_file::decode(Cvirtual_image& d) const
{
	const int c_planes = get_c_planes();
	byte* image = new byte[cx() * cy() * c_planes];
	pcx_decode(get_image(), image, *get_header());
	d.load(image, cx(), cy(), c_planes, c_planes == 1 ? *get_palet() : NULL);
	delete[] image;
}
