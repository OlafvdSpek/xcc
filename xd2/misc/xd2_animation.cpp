#include "stdafx.h"
#include "xd2_animation.h"

Cxd2_animation::Cxd2_animation()
{
}

Cxd2_animation::Cxd2_animation(const shared_data& d, int cf, int cx, int cy)
{
	m_d = d;
	m_cf = cf;
	m_cx = cx;
	m_cy = cy;
}

enum
{
	vi_d,
	vi_cf,
	vi_cx,
	vi_cy,
};

Cxd2_animation::Cxd2_animation(const Cxif_key_r& key)
{
	m_d = key.get_value(vi_d).get_vdata();
	m_cf = key.get_value_int(vi_cf);
	m_cx = key.get_value_int(vi_cx);
	m_cy = key.get_value_int(vi_cy);
}

Cxif_key Cxd2_animation::save() const
{
	Cxif_key key;
	key.set_value_binary(vi_d, m_d);
	key.set_value_int(vi_cf, m_cf);
	key.set_value_int(vi_cx, m_cx);
	key.set_value_int(vi_cy, m_cy);
	return key;
}