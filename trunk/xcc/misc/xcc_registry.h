#if !defined(AFX_XCC_REGISTRY_H__51A70A04_E223_11D2_B750_E1AB1A0B7577__INCLUDED_)
#define AFX_XCC_REGISTRY_H__51A70A04_E223_11D2_B750_E1AB1A0B7577__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "reg_key.h"

class Cxcc_registry  
{
public:
	static int get_base_key(Creg_key& kh_base);
};

#endif // !defined(AFX_XCC_REGISTRY_H__51A70A04_E223_11D2_B750_E1AB1A0B7577__INCLUDED_)
