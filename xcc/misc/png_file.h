#pragma once

#include "cc_file_sh.h"
#include "cc_structures.h"

class Cpng_file: public Ccc_file_sh<t_png_header>
{
public:
	bool is_valid() const
	{
		return !(get_size() < sizeof(t_png_header) || memcmp(get_header(), png_id, sizeof(t_png_header)));
	}
};
