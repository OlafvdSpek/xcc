#pragma once

#include "cc_file_small.h"

class Cbink_file : public Ccc_file_small
{
public:
	bool is_valid() const
	{
		return get_size() >= 4
			&& !memcmp(data(), "BIKi", 4);
	}
};
