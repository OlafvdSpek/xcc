// object_type.cpp: implementation of the Cobject_type class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "object_type.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cobject_type::Cobject_type()
{

}

Cobject_type::~Cobject_type()
{

}

void Cobject_type::load(t_object_type_data d)
{
	m_cost = d.cost;
	m_health = d.health;
	m_name = d.name;
	m_speed = 1 << 7;
}
