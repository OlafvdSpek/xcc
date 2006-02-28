// ucr_container_simple.h: interface for the Cucr_container_simple class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UCR_CONTAINER_SIMPLE_H__33C1F37D_C2EF_4C58_9930_A95955E5D192__INCLUDED_)
#define AFX_UCR_CONTAINER_SIMPLE_H__33C1F37D_C2EF_4C58_9930_A95955E5D192__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ucr_container.h"

class Cucr_container_simple: public Cucr_container_template<Cucr_object>
{
public:
	int open(const Cvirtual_binary& d);
	Cucr_container_simple(const Cucr_format& format);
private:
	const Cucr_format& m_format;
};

#endif // !defined(AFX_UCR_CONTAINER_SIMPLE_H__33C1F37D_C2EF_4C58_9930_A95955E5D192__INCLUDED_)
