// virtual_tfile_write.cpp: implementation of the Cvirtual_tfile_write class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "virtual_tfile_write.h"

#include "string_conversion.h"

Cvirtual_binary Cvirtual_tfile_write::save()
{
	Cvirtual_binary d;
	memcpy(d.write_start(m_v.pcount()), m_v.str(), m_v.pcount());
	return d;
}

void Cvirtual_tfile_write::write(const string& s)
{
	m_v << to_upper(s);
}

void Cvirtual_tfile_write::write_line(const string& s)
{
	m_v << to_upper(s) << endl;
}