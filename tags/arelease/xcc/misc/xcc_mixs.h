// xcc_mixs.h: interface for the Cxcc_mixs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCC_MIXS_H__CAA61D63_FF01_11D2_B601_F02205D95EEC__INCLUDED_)
#define AFX_XCC_MIXS_H__CAA61D63_FF01_11D2_B601_F02205D95EEC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

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
	static int close();
	static Cmix_file& open_mix(t_mix t);
	static void close_mix(t_mix t);
	static Cmix_file& get_conquer_mix();
	static Cmix_file& get_general_mix();
	static Cmix_file& get_theater_mix(t_theater_id theater);
	static string get_theater_fname(t_theater_id theater);
};

#endif // !defined(AFX_XCC_MIXS_H__CAA61D63_FF01_11D2_B601_F02205D95EEC__INCLUDED_)
