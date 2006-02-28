// ucr_object.cpp: implementation of the Cucr_object class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ucr_object.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cucr_object::Cucr_object()
{
}

Cucr_object::Cucr_object(const Cvirtual_binary& d, const string& name, int offset, int size)
{
	m_d = d;
	m_name = name;
	m_offset = offset;
	m_size = size;
}

Cucr_object::~Cucr_object()
{
}
