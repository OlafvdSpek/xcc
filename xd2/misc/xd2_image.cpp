#include "stdafx.h"
#include "xd2_image.h"

Cxd2_image::Cxd2_image(const shared_data& d, int cx, int cy)
{
	m_d = d;
	m_cx = cx;
	m_cy = cy;
}

enum
{
	vi_d,
	vi_cx,
	vi_cy,
};

Cxd2_image::Cxd2_image(const Cxif_key_r& key)
{
	m_d = key.get_value(vi_d).get_vdata();
	m_cx = key.get_value_int(vi_cx);
	m_cy = key.get_value_int(vi_cy);
}

Cxif_key Cxd2_image::save() const
{
	Cxif_key key;
	key.set_value_binary(vi_d, m_d);
	key.set_value_int(vi_cx, m_cx);
	key.set_value_int(vi_cy, m_cy);
	return key;
}
