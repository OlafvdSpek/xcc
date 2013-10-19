#pragma once

#include "xd2_file_map.h"
#include "xd2_image.h"

class Cxd2_shape
{
public:
	Cxif_key save() const;
	Cxd2_shape() = default;
	Cxd2_shape(const Cxif_key_r& key);

	const Cxd2_image& operator[](int i) const
	{
		return map_[i];
	}

	void resize(int size)
	{
		map_.resize(size);
	}

	void set(int i, const Cxd2_image& d)
	{
		map_[i] = d;
	}

	int size() const
	{
		return map_.size();
	}
private:
	vector<Cxd2_image> map_;
};

typedef Cxd2_file_map<Cxd2_shape> Cxd2_shape_map;
