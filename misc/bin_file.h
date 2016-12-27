#pragma once

#include <cc_file_small.h>

class Cbin_file: public Ccc_file_small  
{
public:
	bool is_valid() const
	{
		if (get_size() != 8192)
			return false;
		const byte* p = data();
		for (int i = 0; i < 64 * 64; i++)
		{
			int v = *p++;
			int w = *p++;
			if (v > 0xd7 && v != 0xff || w > 64)
				return false;
		}
		return true;
	}
};
