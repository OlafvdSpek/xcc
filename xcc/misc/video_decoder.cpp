// video_decoder.cpp: implementation of the Cvideo_decoder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "video_decoder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cvideo_decoder::~Cvideo_decoder()
{
}

const t_palet_entry* Cvideo_decoder::palet() const
{
	return NULL;
}
