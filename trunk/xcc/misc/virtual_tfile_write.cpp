#include "stdafx.h"
#include "virtual_tfile_write.h"

Cvirtual_binary Cvirtual_tfile_write::save()
{
	return Cvirtual_binary(m_v.str(), m_v.pcount());
}

void Cvirtual_tfile_write::write(const string& s)
{
	m_v << s;
}

void Cvirtual_tfile_write::write_line(const string& s)
{
	m_v << s << '\r' << endl;
}