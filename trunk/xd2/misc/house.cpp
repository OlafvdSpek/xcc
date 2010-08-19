#include "stdafx.h"
#include "house.h"

Chouse::Chouse()
{
}

Chouse::Chouse(const map<string, string>& d)
{
	m_name = find_ref(d, "name", "");
}
