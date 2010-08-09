#pragma once

#include "mix_file.h"
#include "xcc_level.h"

enum t_mix
{
	conquer_mix,
	desert_mix,
	general_mix,
	temperate_mix,
	winter_mix
};

const int c_mix = winter_mix + 1;

class Cxcc_mixs  
{
public:
	static int open();
	static void close();
	static Cmix_file& conquer();
	static Cmix_file& general();
	static Cmix_file& theater(t_theater_id);
	static string theater_fname(t_theater_id);
	static string theater_fext(t_theater_id);
};
