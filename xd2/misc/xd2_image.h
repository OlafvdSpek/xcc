#pragma once

#include "xd2_file_map.h"

class Cxd2_image
{
public:
	Cxif_key save() const;
	Cxd2_image() = default;
	Cxd2_image(const shared_data& d, int cx, int cy);
	Cxd2_image(const Cxif_key_r& key);

	const byte* d() const
	{
		return m_d.data();
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
	shared_data m_d;
	int m_cx = 0;
	int m_cy = 0;
};

typedef Cxd2_file_map<Cxd2_image> Cxd2_image_map;
