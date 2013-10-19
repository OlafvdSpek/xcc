#include "object.h"

Cobject::Cobject(int x, int y, Cplayer& p, Cobject_type& t)
{
	m_destination = m_l = Clocation(x << 8 | 0x80, y << 8 | 0x80);
	m_health = t.strength;
	m_p = &p;
	m_t = &t;
	m_target = NULL;

	m_destination = Clocation(0x3f80, 0x3f80);
}

void Cobject::tick()
{
	if (m_destination.x != m_l.x || m_destination.y != m_l.y)
	{
		int dx = m_destination.x - m_l.x;
		int dy = m_destination.y - m_l.y;
		int d;
		if (dy > 0)
			d = 2;
		else if (dx < 0)
			d = 4;
		else if (dx > 0)
			d = 6;
		else
			d = 8;
		Clocation old_l = m_l;
		switch (d)
		{
		case 2:
			m_l.y = min(m_destination.y, m_l.y + m_t->speed);
			break;
		case 4:
			m_l.x = min(m_destination.x, m_l.x - m_t->speed);
			break;
		case 6:
			m_l.x = min(m_destination.x, m_l.x + m_t->speed);
			break;
		case 8:
			m_l.y = max(m_destination.y, m_l.y - m_t->speed);
			break;
		}
		if (m_l.xh() != old_l.xh() || m_l.yh() != old_l.yh())
		{
		}
	}
}
