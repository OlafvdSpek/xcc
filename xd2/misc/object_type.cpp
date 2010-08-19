#include "stdafx.h"
#include "object_type.h"

Cobject_type::Cobject_type()
{
}

Cobject_type::Cobject_type(const map<string, string>& d)
{
	name = find_ref(d, "name", "");
	cost = find_ref(d, "cost", 0);
	sight = find_ref(d, "sight", 0);
	speed = find_ref(d, "speed", 0);
	strength = find_ref(d, "strength", 0);
}

void Cobject_type::load(const t_object_type_data& d)
{
	cost = d.cost;
	strength = d.health;
	name = d.name;
	speed = 1 << 7;
}
