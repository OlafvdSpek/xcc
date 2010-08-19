#pragma once

class Cobject_type
{
public:
	Cobject_type();
	Cobject_type(const map<string, string>&);

	string name;
	int body;
	int cameo;
	int cost;
	int sight;
	int speed;
	int strength;
	int turret;
	bool structure;
};
