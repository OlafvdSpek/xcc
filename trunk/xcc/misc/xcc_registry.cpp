#include "stdafx.h"
#include "xcc_registry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int Cxcc_registry::get_base_key(Creg_key& kh_base)
{
	return ERROR_SUCCESS != kh_base.create(HKEY_LOCAL_MACHINE, "Software\\XCC");
}