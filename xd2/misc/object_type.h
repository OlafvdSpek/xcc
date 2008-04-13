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
	string name() const
	{
		return m_name;
	};

	int speed() const
	{
		return m_speed;
	}

	void load(t_object_type_data d);
	Cobject_type();
	virtual ~Cobject_type();
private:
	int m_cost;
	int m_health;
	string m_name;
	int m_speed;
};
