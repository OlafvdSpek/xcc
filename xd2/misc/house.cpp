#include "stdafx.h"
#include "house.h"

Chouse::Chouse()
{
}

Chouse::~Chouse()
{
}

void Chouse::load(t_house_data d)
{
	m_name = d.name;
}
