#pragma once

#include <cc_file_sh.h>
#include <cc_structures.h>

class Cfnt_file: public Ccc_file_sh<t_fnt_header>
{
public:
	bool is_valid() const
	{
		const t_fnt_header& header = *get_header();
		int size = get_size();
		if (sizeof(t_fnt_header) > size || 
			header.size != size ||
			header.id2 != 0x000e ||
			header.id3 != 0x0014 ||
			header.zero)
			return false;
		return get_version() == game_td ? 
			header.id1 == 0x0500 && header.id4 == 0x1012 : 
			header.id1 == 0x0002 && !header.id4;
	}

	t_game get_version() const
	{
		return get_header()->id1 == 0x0500 ? game_td : game_ts;
	}

	int get_c_chars() const
	{
		return get_header()->c_chars + 1;
	}

	int get_cmax_x() const
	{
		return get_header()->cmax_x;
	}

	int get_cy() const
	{
		return get_header()->cy;
	}

	int get_y(int i) const
	{
		return reinterpret_cast<const unsigned short*>(get_data() + get_header()->cy_ofs)[i] & 0xff;
	}

	int get_cx(int i) const
	{
		return (get_data() + get_header()->cx_ofs)[i];
	}

	int get_cy(int i) const
	{
		return reinterpret_cast<const unsigned short*>(get_data() + get_header()->cy_ofs)[i] >> 8;
	}

	const byte* get_image(int i) const
	{
		return get_data() + reinterpret_cast<const unsigned short*>(get_data() + sizeof(t_fnt_header))[i];
	}
};
