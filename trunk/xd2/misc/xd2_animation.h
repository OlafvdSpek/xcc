#pragma once

#include "xd2_file_map.h"

class Cxd2_animation
{
public:
	Cxif_key save() const;
	Cxd2_animation();
	Cxd2_animation(const Cvirtual_binary& d, int cf, int cx, int cy);
	Cxd2_animation(const Cxif_key_r& key);

	const byte* d(int i) const
	{
		return m_d + cx() * cy() * i;
	}

	int cf() const
	{
		return m_cf;
	}

	int cx() const
	{
		return m_cx;
	}

	int cy() const
	{
		return m_cy;
	}
private:
	Cvirtual_binary m_d;
	int m_cf;
	int m_cx;
	int m_cy;
};

typedef Cxd2_file_map<Cxd2_animation> Cxd2_animation_map;
