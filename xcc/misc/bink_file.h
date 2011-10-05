#pragma once

#include "cc_file_small.h"

class Cbink_file: public Ccc_file_small
{
public:
	bool is_valid() const
	{
		int size = get_size();
		if (4 > size)
			return false;
		return *reinterpret_cast<const __int32*>(data()) == *reinterpret_cast<const __int32*>("BIKi");
	}
};
