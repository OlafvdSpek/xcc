// xcc_registry.h: interface for the Cxcc_registry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCC_REGISTRY_H__51A70A04_E223_11D2_B750_E1AB1A0B7577__INCLUDED_)
#define AFX_XCC_REGISTRY_H__51A70A04_E223_11D2_B750_E1AB1A0B7577__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "vartypes.h"
#include "windows.h"

class Cxcc_registry  
{
public:
	static long get_base_key(HKEY &kh_base);
};

#endif // !defined(AFX_XCC_REGISTRY_H__51A70A04_E223_11D2_B750_E1AB1A0B7577__INCLUDED_)
