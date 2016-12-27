#include "stdafx.h"
#include "xcc_registry.h"

int Cxcc_registry::get_base_key(Creg_key& kh_base)
{
	return ERROR_SUCCESS != kh_base.create(HKEY_LOCAL_MACHINE, "Software\\XCC");
}