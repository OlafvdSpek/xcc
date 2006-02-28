// ucr_container_ws_ra_mix.h: interface for the Cucr_container_ws_ra_mix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UCR_CONTAINER_WS_RA_MIX_H__9C053B52_F648_49B3_AFAC_C2A7B43B30FB__INCLUDED_)
#define AFX_UCR_CONTAINER_WS_RA_MIX_H__9C053B52_F648_49B3_AFAC_C2A7B43B30FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ucr_container.h"

class Cucr_container_ws_ra_mix: public Cucr_container_template<Cucr_object>
{
public:
	int open(const Cvirtual_binary& d);
};

class Cucr_object_ws_ts_shp: public Cucr_object
{
public:
	Cvirtual_binary d() const;
	Cucr_object_ws_ts_shp(const Cvirtual_binary& d, int i);
private:
	struct t_header
	{
		__int16 x;
		__int16 y;
		__int16 cx;
		__int16 cy;
		__int32 compression;
		__int32 unknown;
		__int32 zero;
		__int32 offset;
	};

	const t_header& h() const;
};

class Cucr_container_ws_ts_shp: public Cucr_container_template<Cucr_object_ws_ts_shp>
{
public:
	int open(const Cvirtual_binary& d);
};

#endif // !defined(AFX_UCR_CONTAINER_WS_RA_MIX_H__9C053B52_F648_49B3_AFAC_C2A7B43B30FB__INCLUDED_)
