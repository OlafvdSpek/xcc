#include "object_type.h"

Cobject_type::Cobject_type(const map<string, string>& d)
{
	body = find_ref(d, "body", 0);
	cameo = find_ref(d, "cameo", 0);
	clas = to_object_clas(find_ref(d, "class", ""));
	code = find_ref(d, "code");
	cost = find_ref(d, "cost", 0);
	cx = find_ref(d, "cx", 0);
	cy = find_ref(d, "cy", 0);
	icon = find_ref(d, "icon", 0);
	name = find_ref(d, "code", "");
	sight = find_ref(d, "sight", 0);
	speed = find_ref(d, "speed", 0);
	strength = find_ref(d, "strength", 0);
	turret = find_ref(d, "turret", 0);
}

object_clas_e to_object_clas(const string& v)
{
	if (v == "structure")
		return oc_structure;
	if (v == "infantry")
		return oc_infantry;
	if (v == "light")
		return oc_light;
	if (v == "heavy")
		return oc_heavy;
	if (v == "hitech")
		return oc_hitech;
	return oc_null;
}