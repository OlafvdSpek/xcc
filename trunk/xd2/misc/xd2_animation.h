#pragma once

#include "xd2_file_map.h"

class Cxd2_animation
{
public:
	Cxif_key save() const;
	Cxd2_animation() = default;
	Cxd2_animation(const shared_data& d, int cf, int cx, int cy);
	Cxd2_animation(const Cxif_key_r& key);

	const byte* d(int i) const
	{
		return d_.data() + cx() * cy() * i;
	}

	int cf() const
	{
		return cf_;
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
	int cf_;
	int cx_;
	int cy_;
};

typedef Cxd2_file_map<Cxd2_animation> Cxd2_animation_map;
