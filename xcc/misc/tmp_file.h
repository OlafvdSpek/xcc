#pragma once

#include <cc_file_sh.h>
#include <cc_structures.h>

class Ctmp_file: public Ccc_file_sh<t_tmp_header>  
{
public:
	bool is_valid() const
	{
		const t_tmp_header& header = *get_header();
		int size = get_size();
		return !(sizeof(t_tmp_header) > size || 
			header.cx != 24 || 
			header.cy != 24 || 
			header.c_tiles > 64 ||
			header.zero1 ||
			header.size != size ||
			header.image_offset > size ||
			header.zero2 ||
			header.id != 0x0d1affff);
	}

	int get_c_tiles() const
	{
		return get_header()->c_tiles;
	}

	const byte* get_image(int i) const
	{
		return get_data() + get_header()->image_offset + 576 * get_index1()[i];
	}

	const byte* get_index1() const
	{
		return get_data() + get_header()->index1;
	}
};
