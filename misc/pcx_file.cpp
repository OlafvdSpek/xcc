/*
    XCC Utilities and Library
    Copyright (C) 2000  Olaf van der Spek  <olafvdspek@gmail.com>

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
#include "pcx_file.h"

bool Cpcx_file::is_valid() const
{
	const t_pcx_header& h = header();
	int size = get_size();
	return !(sizeof(t_pcx_header) > size ||
		h.manufacturer != 10 ||
		h.version != 5 ||
		h.encoding != 1 ||
		h.cbits_pixel != 8 ||
		h.c_planes != 1 && h.c_planes != 3);
}

void Cpcx_file::decode(void* d) const
{
	pcx_decode(get_image(), reinterpret_cast<byte*>(d), header());
}

Cvirtual_image Cpcx_file::vimage() const
{
	Cvirtual_binary image;
	pcx_decode(get_image(), image.write_start(cb_image()), header());
	return Cvirtual_image(image, cx(), cy(), cb_pixel(), cb_pixel() == 1 ? *get_palet() : NULL);
}
