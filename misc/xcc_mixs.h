#pragma once

#include "mix_file.h"
#include "xcc_level.h"

class Cxcc_mixs  
{
public:
	static int open();
	static Cmix_file& conquer();
	static Cmix_file& general();
	static Cmix_file& theater(t_theater_id);
	static string theater_fname(t_theater_id);
	static string theater_fext(t_theater_id);
};
