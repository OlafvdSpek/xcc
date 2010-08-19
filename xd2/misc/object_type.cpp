#include "stdafx.h"
#include "object_type.h"

Cobject_type::Cobject_type()
{
}

Cobject_type::Cobject_type(const map<string, string>& d)
{
	name = find_ref(d, "name", "");
	// @ = find_ref(d, "@", 0);
	body = find_ref(d, "body", 0);
	cameo = find_ref(d, "cameo", 0);
	cost = find_ref(d, "cost", 0);
	icon = find_ref(d, "icon", 0);
	sight = find_ref(d, "sight", 0);
	int size = find_ref(d, "size", 0);
	speed = find_ref(d, "speed", 0);
	strength = find_ref(d, "strength", 0);
	structure = find_ref(d, "class", "") == "structure";
	turret = find_ref(d, "turret", 0);

	cx = size == 0 || size == 2 ? 1 : size == 1 || size == 3 || size == 4 ? 2 : 3;
	cy = size == 0 || size == 1 ? 1 : size == 2 || size == 3 || size == 5 ? 2 : 3;
}
