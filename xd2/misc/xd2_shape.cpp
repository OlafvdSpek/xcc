#include "stdafx.h"
#include "xd2_shape.h"

Cxd2_shape::Cxd2_shape()
{
}

Cxd2_shape::Cxd2_shape(const Cxif_key_r& key)
{
	BOOST_FOREACH(auto& i, key.keys())
		m_map.push_back(Cxd2_image(i.second));
}

Cxif_key Cxd2_shape::save() const
{
	Cxif_key key;
	BOOST_FOREACH(auto& i, m_map)
		key.open_key_write() = i.save();
	return key;
}