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
		return d_.data();
	}

	int cx() const
	{
		return cx_;
	}

	int cy() const
	{
		return cy_;
	}
private:
	shared_data d_;
	int cx_ = 0;
	int cy_ = 0;
};

typedef Cxd2_file_map<Cxd2_image> Cxd2_image_map;
