#pragma once

struct t_object_type_data
{
	const char* name;
	int cost;
	int health;
};

class Cobject_type
{
public:
	void load(const t_object_type_data&);
	Cobject_type();
	Cobject_type(const map<string, string>&);

	string name;
	int cost;
	int sight;
	int speed;
	int strength;
};
