// image_file.cpp: implementation of the Cimage_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "image_file.h"

#include "jpeg_file.h"
#include "pcx_file_write.h"
#include "png_file.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cimage_file::Cimage_file()
{
}

Cimage_file::~Cimage_file()
{
}

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
	default:
#ifdef PNG_SUPPORT
		return png_file_write(name, image, palet, cx, cy);
#else
		return 1;
#endif
	}
}