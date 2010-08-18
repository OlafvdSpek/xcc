#pragma once

#include "xd2_file_map.h"
#include "xd2_image.h"

class Cxd2_shape
{
public:
	Cxif_key save() const;
	Cxd2_shape();
	Cxd2_shape(const Cxif_key_r& key);

	const Cxd2_image& operator[](int i) const
	{
		return m_map[i];
	}

	void resize(int size)
	{
		m_map.resize(size);
	}

	void set(int i, const Cxd2_image& d)
	{
		m_map[i] = d;
	}

	int size() const
	{
		return m_map.size();
	}
private:
	typedef vector<Cxd2_image> t_map;

	t_map m_map;
};

typedef Cxd2_file_map<Cxd2_shape> Cxd2_shape_map;
