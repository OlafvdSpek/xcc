#include "stdafx.h"
#include "ucr_object.h"

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
