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