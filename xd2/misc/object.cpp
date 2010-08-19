#include "stdafx.h"
#include "object.h"

Cobject::Cobject()
{
	m_t = NULL;
}

void Cobject::load(const t_object_data& d)
{
	m_destination = m_l = Clocation(d.x << 8 | 0x80, d.y << 8 | 0x80);
	m_health = d.health;
	m_p = d.p;
	m_t = d.t;
	m_target = NULL;

	m_destination = Clocation(d.x << 8 | 0x80, d.y + 2 << 8 | 0x80);
}

void Cobject::tick()
{
	if (!valid())
		return;
	if (m_destination.x() != m_l.x() || m_destination.y() != m_l.y())
	{
		int dx = m_destination.x() - m_l.x();
		int dy = m_destination.y() - m_l.y();
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
			m_l.y(min(m_destination.y(), m_l.y() + m_t->speed));
			break;
		case 4:
			m_l.x(min(m_destination.x(), m_l.x() - m_t->speed));
			break;
		case 6:
			m_l.x(min(m_destination.x(), m_l.x() + m_t->speed));
			break;
		case 8:
			m_l.y(max(m_destination.y(), m_l.y() - m_t->speed));
			break;
		}
		if (m_l.xh() != old_l.xh() || m_l.yh() != old_l.yh())
		{
		}
	}
}

void Cobject::dump(ostream& os)
{
	os << hex << m_l.x() << ',' << m_l.y() << dec;
}
