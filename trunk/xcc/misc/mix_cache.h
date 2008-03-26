#pragma once

#include "virtual_binary.h"

namespace mix_cache
{
	int load();
	int save();
	Cvirtual_binary get_data(int crc);
	void set_data(int crc, const Cvirtual_binary&);
};
