#include "stdafx.h"
#include "xd2_shape.h"

Cxd2_shape::Cxd2_shape(const Cxif_key_r& key)
{
	for (auto& i : key.keys())
		map_.emplace_back(i.second);
}

Cxif_key Cxd2_shape::save() const
{
	Cxif_key key;
	for (auto& i : map_)
		key.open_key_write() = i.save();
	return key;
}