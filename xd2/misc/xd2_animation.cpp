#include "stdafx.h"
#include "xd2_animation.h"

Cxd2_animation::Cxd2_animation(const shared_data& d, int cf, int cx, int cy)
{
	d_ = d;
	cf_ = cf;
	cx_ = cx;
	cy_ = cy;
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
	d_ = key.get_value(vi_d).get_vdata();
	cf_ = key.get_value_int(vi_cf);
	cx_ = key.get_value_int(vi_cx);
	cy_ = key.get_value_int(vi_cy);
}

Cxif_key Cxd2_animation::save() const
{
	Cxif_key key;
	key.set_value_binary(vi_d, d_);
	key.set_value_int(vi_cf, cf_);
	key.set_value_int(vi_cx, cx_);
	key.set_value_int(vi_cy, cy_);
	return key;
}