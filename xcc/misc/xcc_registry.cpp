// xcc_registry.cpp: implementation of the Cxcc_registry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xcc_registry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int Cxcc_registry::get_base_key(HKEY& kh_base)
{
	dword disposition;
	return ERROR_SUCCESS != RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\XCC", 0, 0, 0, KEY_ALL_ACCESS, 0, &kh_base, &disposition);
}