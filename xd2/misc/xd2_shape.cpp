#include "stdafx.h"
#include "xd2_shape.h"

Cxd2_shape::Cxd2_shape()
{
}

Cxd2_shape::Cxd2_shape(const Cxif_key_r& key)
{
	for (Cxif_key_r::t_key_map::const_iterator i = key.keys().begin(); i != key.keys().end(); i++)
		m_map.push_back(Cxd2_image(i->second));
}

Cxif_key Cxd2_shape::save() const
{
	Cxif_key key;
	for (t_map::const_iterator i = m_map.begin(); i != m_map.end(); i++)
		key.open_key_write() = i->save();
	return key;
}