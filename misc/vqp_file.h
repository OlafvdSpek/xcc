#pragma once

// #include "cc_file.h"
#include "cc_structures.h"

class Cvqp_file : public Ccc_file_sh<t_vqp_header>    
{
public:
	bool is_valid() const
	{
		const t_vqp_header& h = header();
		int size = get_size();
		return !(sizeof(t_vqp_header) > size || 
			sizeof(t_vqp_header) + 32896 * h.c_tables != size);
	}
};
