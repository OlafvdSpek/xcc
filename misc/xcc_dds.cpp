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
#include "xcc_dds.h"

int Cxcc_dds::create(Cxcc_dd&dd, int cx, int cy)
{
	dd_ = &dd;
	DDSURFACEDESC ddsdesc;
	ddsdesc.dwSize = sizeof(DDSURFACEDESC);
	ddsdesc.dwFlags = DDSD_CAPS;// | DDSD_HEIGHT | DDSD_WIDTH; 
	ddsdesc.dwWidth = cx;
	ddsdesc.dwHeight = cy;
	ddsdesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	if (DD_OK != dd_->get_p()->CreateSurface(&ddsdesc, &dds_, 0))
	{
		handle_error("CreateSurface failed");
		return 1;
	}
	return 0;		
}

void Cxcc_dds::handle_error(const string& s) const
{
	dd_->handle_error(s);
}