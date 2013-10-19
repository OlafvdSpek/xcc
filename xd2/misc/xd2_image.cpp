#include "xd2_image.h"

Cxd2_image::Cxd2_image(const shared_data& d, int cx, int cy)
{
	d_ = d;
	cx_ = cx;
	cy_ = cy;
}

enum
{
	vi_d,
	vi_cx,
	vi_cy,
};

Cxd2_image::Cxd2_image(const Cxif_key_r& key)
{
	d_ = key.get_value(vi_d).get_vdata();
	cx_ = key.get_value_int(vi_cx);
	cy_ = key.get_value_int(vi_cy);
}

Cxif_key Cxd2_image::save() const
{
	Cxif_key key;
	key.set_value_binary(vi_d, d_);
	key.set_value_int(vi_cx, cx_);
	key.set_value_int(vi_cy, cy_);
	return key;
}
