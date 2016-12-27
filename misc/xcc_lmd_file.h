#pragma once

#include "xcc_file_sh.h"

class Cxcc_lmd_file: public Cxcc_file_sh<t_xcc_lmd_header>
{
public:
	bool is_valid() const
	{
		return Cxcc_file_sh<t_xcc_lmd_header>::is_valid() && get_ft() == xcc_ft_lmd;
	}

	t_game get_game() const
	{
		return static_cast<t_game>(header().game);
	}

	int get_c_fnames() const
	{
		return header().c_fnames;
	}

	const char* get_fnames() const
	{
		return reinterpret_cast<const char*>(data() + sizeof(t_xcc_header) + sizeof(t_xcc_lmd_header));
	}
};
