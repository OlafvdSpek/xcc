#pragma once

enum object_clas_e
{
	oc_null,
	oc_structure,
	oc_infantry,
	oc_light,
	oc_heavy,
	oc_hitech,
};

class Cobject_type
{
public:
	Cobject_type() = default;
	Cobject_type(const map<string, string>&);

	string code;
	string name;
	int body;
	int cameo;
	int cost;
	int cx;
	int cy;
	int icon;
	int sight;
	int speed;
	int strength;
	int turret;
	object_clas_e clas;
};

object_clas_e to_object_clas(const string&);
