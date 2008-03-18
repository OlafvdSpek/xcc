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
		return jpeg_file_write(f, image, palet, cx, cy);
#else
		return 1;
#endif
	case ft_pcx:
		pcx_file_write(f, image, palet, cx, cy);
		return 0;
	case ft_tga:
		f = palet
			? tga_file_write(image, cx, cy, palet)
			: tga_file_write(image, cx, cy, 3);
		return 0;
	default:
#ifdef PNG_SUPPORT
		return png_file_write(f, image, palet, cx, cy);
#else
		return 1;
#endif
	}
}

Cvirtual_file image_file_write(t_file_type ft, const byte* image, const t_palet_entry* palet, int cx, int cy)
{
	Cvirtual_file f;
	if (image_file_write(f, ft, image, palet, cx, cy))
		f.clear();
	return f;
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
		return palet
			? tga_file_write(image, cx, cy, palet).save(name)
			: tga_file_write(image, cx, cy, 3).save(name);
	default:
#ifdef PNG_SUPPORT
		return png_file_write(name, image, palet, cx, cy);
#else
		return 1;
#endif
	}
}