/*
    XCC Utilities and Library
    Copyright (C) 2001  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
	case ft_jpeg:
		return jpeg_file_write(f, image, palet, cx, cy);
	case ft_pcx:
		pcx_file_write(f, image, palet, cx, cy);
		return 0;
	case ft_tga:
		f = palet
			? tga_file_write(image, cx, cy, palet)
			: tga_file_write(image, cx, cy, 3);
		return 0;
	default:
		return png_file_write(f, image, palet, cx, cy);
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
	case ft_jpeg:
		return jpeg_file_write(name, image, palet, cx, cy);
	case ft_pcx:
		return pcx_file_write(name, image, palet, cx, cy);
	case ft_tga:
		return palet
			? tga_file_write(image, cx, cy, palet).save(name)
			: tga_file_write(image, cx, cy, 3).save(name);
	default:
		return png_file_write(name, image, palet, cx, cy);
	}
}