// png_file.cpp: implementation of the Cpng_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "png_file.h"
#include "png.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int png_file_write(const string& name, const byte* image, const t_palet_entry* palet, int cx, int cy)
{
	int c_planes = palet ? 1 : 3;
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
		return 1;
	
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) 
	{
		png_destroy_write_struct(&png_ptr, NULL);
		return 1;
	}
	
	FILE* out_file = fopen(name.c_str(), "wb");
	if (!out_file)
		return 1;
	
	jmp_buf jmpbuf;
	if (setjmp(jmpbuf)) 
	{
		if (out_file)
			fclose(out_file);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return 1;
	}
	
	png_init_io(png_ptr, out_file);
	png_set_IHDR(png_ptr, info_ptr, cx, cy, 8, palet ? PNG_COLOR_TYPE_PALETTE : PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	if (palet)
		png_set_PLTE(png_ptr, info_ptr, const_cast<png_color*>(reinterpret_cast<const png_color*>(palet)), 256);
	png_write_info(png_ptr, info_ptr);
	
	const byte* r = image;
	for (int y = 0; y < cy; y++)
	{
		png_write_row(png_ptr, const_cast<byte*>(r));
		r += cx * c_planes;
	}
	png_write_end(png_ptr, NULL);
	png_destroy_write_struct(&png_ptr, &info_ptr);		
	fclose(out_file);
	return 0;
}