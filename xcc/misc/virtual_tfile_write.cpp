#include "stdafx.h"
#include "virtual_tfile_write.h"

#include <boost/algorithm/string.hpp>

using namespace boost;

Cvirtual_binary Cvirtual_tfile_write::save()
{
	return Cvirtual_binary(m_v.str(), m_v.pcount());
}

void Cvirtual_tfile_write::write(const string& s)
{
	m_v << to_upper_copy(s);
}

void Cvirtual_tfile_write::write_line(const string& s)
{
	m_v << to_upper_copy(s) << endl;
}