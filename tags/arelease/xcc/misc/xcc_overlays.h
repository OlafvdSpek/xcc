// xcc_overlays.h: interface for the Cxcc_overlays class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCC_OVERLAYS_H__059E27C5_FD8E_11D2_B601_964550F4BC6E__INCLUDED_)
#define AFX_XCC_OVERLAYS_H__059E27C5_FD8E_11D2_B601_964550F4BC6E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "shp_images.h"
#include "xcc_level.h"
#include "xcc_mixs.h"
#include "xif_key.h"

class Cxcc_overlays  
{
public:
	static bool terrain_blocked(dword v);
	static void terrain_switch_blocked(dword v);
	static const byte* get_overlay_image(dword v, int& x, int& y, int& cx, int& cy);
	static const byte* get_terrain_image(dword v, int& x, int& y, int& cx, int& cy);
	static bool terrain_in(dword v, t_theater_id theater);
	static void destroy();
	static int load_data();
	static int save_data();
	static int load_images(t_theater_id theater);

	static const byte* get_terrain_image(dword v, int& x, int& y, long& _cx, long& _cy)
	{
		int cx, cy;
		const byte* r = get_terrain_image(v, x, y, cx, cy);
		_cx = cx;
		_cy = cy;
		return r;
	}
};

#endif // !defined(AFX_XCC_OVERLAYS_H__059E27C5_FD8E_11D2_B601_964550F4BC6E__INCLUDED_)
