#pragma once

#include "location.h"
#include "object_type.h"
#include "player.h"

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

	void tick();
	Cobject();
	Cobject(int x, int y, Cplayer&, Cobject_type&);
private:
	Clocation m_destination;
	int m_health;
	Clocation m_l;
	Cplayer* m_p;
	Cobject_type* m_t;
	Cobject* m_target;
};
