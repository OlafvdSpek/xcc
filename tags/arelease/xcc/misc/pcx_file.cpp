// pcx_file.cpp: implementation of the Cpcx_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pcx_decode.h"
#include "pcx_file.h"
#include "png_file.h"

int Cpcx_file::extract_as_png(const string& name) const
{
	const int cx = get_cx();
	const int cy = get_cy();
	const int c_planes = get_c_planes();
	byte* image = new byte[cx * cy * c_planes];
	pcx_decode(get_image(), image, *get_header());
	int error = png_file_write(name, image, c_planes == 1 ? *get_palet() : NULL, cx, cy);
	delete[] image;
	return error;
}
