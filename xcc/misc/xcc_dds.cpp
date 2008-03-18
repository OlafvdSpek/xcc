#include "stdafx.h"
#include "xcc_dds.h"

Cxcc_dds::Cxcc_dds()
{
	pdds = 0;
}

Cxcc_dds::~Cxcc_dds()
{
}

long Cxcc_dds::create(Cxcc_dd &dd, long cx, long cy)
{
	pdd = &dd;
	DDSURFACEDESC ddsdesc;
	ddsdesc.dwSize = sizeof(DDSURFACEDESC);
	ddsdesc.dwFlags = DDSD_CAPS;// | DDSD_HEIGHT | DDSD_WIDTH; 
	ddsdesc.dwWidth = cx;
	ddsdesc.dwHeight = cy;
	ddsdesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	if (DD_OK != pdd->get_p()->CreateSurface(&ddsdesc, &pdds, 0))
	{
		handle_error("CreateSurface failed");
		return 1;
	}
	return 0;		
}

void Cxcc_dds::handle_error(const string &s) const
{
	pdd->handle_error(s);
}