#pragma once

#include "cc_file_sh.h"
#include "cc_structures.h"

class Cjpeg_file: public Ccc_file_sh<t_jpeg_header>
{
public:
	bool is_valid() const
	{
		return !(get_size() < sizeof(t_jpeg_header) || memcmp(get_header()->id, jpeg_id, 4));
	}
};
