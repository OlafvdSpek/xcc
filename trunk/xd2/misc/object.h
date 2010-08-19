#pragma once

#include "location.h"
#include "object_type.h"
#include "player.h"

struct t_object_data
{
	int health;
	int x;
	int y;
	Cplayer* p;
	Cobject_type* t;
};

class Cobject
{
public:
	Clocation l() const
	{
		return m_l;
	}

	const Cplayer& p() const
	{
		return *m_p;
	}

	const Cobject_type& t() const
	{
		return *m_t;
	}

	bool valid() const
	{
		return m_p && m_t;
	}

	void dump(ostream&);
	void tick();
	Cobject();
	Cobject(const t_object_data&);
private:
	Clocation m_destination;
	int m_health;
	Clocation m_l;
	Cplayer* m_p;
	Cobject_type* m_t;
	Cobject* m_target;
};
