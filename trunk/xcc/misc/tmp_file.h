#pragma once

#include <cc_file_sh.h>
#include <cc_structures.h>

class Ctmp_file: public Ccc_file_sh<t_tmp_header>  
{
public:
	bool is_valid() const
	{
		const t_tmp_header& h = header();
		int size = get_size();
		return !(sizeof(t_tmp_header) > size || 
			h.cx != 24 || 
			h.cy != 24 || 
			h.c_tiles > 128 ||
			h.zero1 ||
			h.size != size ||
			h.image_offset > size ||
			h.zero2 ||
			h.id != 0x0d1affff);
	}

	int get_c_tiles() const
	{
		return header().c_tiles;
	}

	const byte* get_image(int i) const
	{
		return data() + header().image_offset + 576 * get_index1()[i];
	}

	const byte* get_index1() const
	{
		return data() + header().index1;
	}
};
