// image_file.cpp: implementation of the Cimage_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "image_file.h"

#include "jpeg_file.h"
#include "pcx_file_write.h"
#include "png_file.h"
#include "tga_file.h"

int image_file_write(Cvirtual_file& f, t_file_type ft, const byte* image, const t_palet_entry* palet, int cx, int cy)
{
	switch (ft)
	{
#ifdef JPEG_SUPPORT
	case ft_jpeg:
		return jpeg_file_write(f, image, palet, cx, cy);;
#else
		return 1;
#endif
	case ft_pcx:
		pcx_file_write(f, image, palet, cx, cy);
		return 0;
	case ft_tga:
		f = tga_file_write(image, cx, cy, palet ? 1 : 3);
		return 0;
	default:
#ifdef PNG_SUPPORT
		return png_file_write(f, image, palet, cx, cy);;
#else
		return 1;
#endif
	}
}

int image_file_write(const string& name, t_file_type ft, const byte* image, const t_palet_entry* palet, int cx, int cy)
{
	switch (ft)
	{
#ifdef JPEG_SUPPORT
	case ft_jpeg:
		return jpeg_file_write(name, image, palet, cx, cy);
#else
		return 1;
#endif
	case ft_pcx:
		return pcx_file_write(name, image, palet, cx, cy);
	case ft_tga:
		return tga_file_write(name, image, cx, cy, palet ? 1 : 3);
	default:
#ifdef PNG_SUPPORT
		return png_file_write(name, image, palet, cx, cy);
#else
		return 1;
#endif
	}
}