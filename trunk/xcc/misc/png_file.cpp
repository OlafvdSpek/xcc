#include "stdafx.h"
#include "png_file.h"

#include <cstdint>
#include <setjmp.h>
#include "fname.h"
#include "png.h"

#if 1 // def PNG_SUPPORT
#pragma comment(lib, "libpng.lib")

void user_error_fn(png_structp png_ptr, png_const_charp error_msg)
{
	longjmp(png_jmpbuf(png_ptr), 1);
}

int Cpng_file::decode(Cvirtual_image& d) const
{
	string name = get_temp_fname();
	int error = file32_write(name, data(), size());
	if (!error)
	{
		png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, user_error_fn, NULL);
		png_infop info_ptr = NULL;
		png_infop end_ptr = NULL;
		if (!png_ptr)
			error = 1;
		else
		{
			info_ptr = png_create_info_struct(png_ptr);
			if (!info_ptr) 
				error = 1;
			else
			{
				end_ptr = png_create_info_struct(png_ptr);
				if (!end_ptr) 
					error = 1;
				else
				{
					FILE* f = fopen(name.c_str(), "rb");
					if (!f)
						error = 1;
					else
					{
						if (setjmp(png_jmpbuf(png_ptr))) 
							error = 1;
						else
						{
							png_init_io(png_ptr, f);
							png_read_info(png_ptr, info_ptr);
							uint32_t cx;
							uint32_t cy;
							int cbits_pixel;
							int color_type;
							png_get_IHDR(png_ptr, info_ptr, &cx, &cy, &cbits_pixel, &color_type, NULL, NULL, NULL);
							png_set_interlace_handling(png_ptr);
							if (cbits_pixel == 16)
								png_set_strip_16(png_ptr);
							if (cbits_pixel < 8)
								png_set_packing(png_ptr);
							if (color_type & PNG_COLOR_MASK_ALPHA)
								png_set_strip_alpha(png_ptr);
							if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
								png_set_gray_to_rgb(png_ptr);
							png_read_update_info(png_ptr, info_ptr);
							int cb_pixel = color_type == PNG_COLOR_TYPE_PALETTE ? 1 : 3;
							byte* image = new byte[cx * cy * cb_pixel];
							png_bytep* row_pointers = new png_bytep[cy];
							for (int y = 0; y < cy; y++)
								row_pointers[y] = image + cx * cb_pixel * y;
							png_read_image(png_ptr, row_pointers);
							delete[] row_pointers;
							if (cb_pixel == 1)
							{
								if (!png_get_valid(png_ptr, info_ptr, PNG_INFO_PLTE))
									error = 2;
								else
								{
									int c_colors = 256;
									png_colorp palet;
									png_get_PLTE(png_ptr, info_ptr, &palet, &c_colors);
									d.load(image, cx, cy, cb_pixel, reinterpret_cast<t_palet_entry*>(palet));
								}
							}
							else
								d.load(image, cx, cy, cb_pixel, NULL);
							delete[] image;
						}
						fclose(f);
					}
				}
			}
		}
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);					
		delete_file(name);
	}
	return error;
}

int png_file_write(Cvirtual_file& f, const byte* image, const t_palet_entry* palet, int cx, int cy)
{
	string temp_fname = get_temp_fname();
	int error = png_file_write(temp_fname, image, palet, cx, cy);
	if (!error)
	{
		error = f.load(temp_fname);
	}
	delete_file(temp_fname);
	return error;
}

int png_file_write(const string& name, const byte* image, const t_palet_entry* palet, int cx, int cy)
{
	if (!cx || !cy)
		return 1;

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
	
	FILE* f = fopen(name.c_str(), "wb");
	if (!f)
		return 1;
	
	jmp_buf jmpbuf;
	if (setjmp(jmpbuf)) 
	{
		fclose(f);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return 1;
	}
	
	png_init_io(png_ptr, f);
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
	fclose(f);
	return 0;
}
#else
int Cpng_file::decode(Cvirtual_image& d) const
{
	return 1;
}

int png_file_write(Cvirtual_file& f, const byte* image, const t_palet_entry* palet, int cx, int cy)
{
	return 1;
}

int png_file_write(const string& name, const byte* image, const t_palet_entry* palet, int cx, int cy)
{
	return 1;
}
#endif