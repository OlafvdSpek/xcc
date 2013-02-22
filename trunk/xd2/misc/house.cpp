#include "stdafx.h"
#include "house.h"

Chouse::Chouse()
{
}

Chouse::Chouse(const map<string, string>& d)
{
	name_ = find_ref(d, "name", "");
}
