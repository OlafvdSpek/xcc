// sdl_rect.h: interface for the Csdl_rect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDL_RECT_H__98074340_70C5_11D7_B607_0000C006A2C2__INCLUDED_)
#define AFX_SDL_RECT_H__98074340_70C5_11D7_B607_0000C006A2C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Csdl_rect: public SDL_Rect
{
public:
	Csdl_rect()
	{
	}

	Csdl_rect(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	Csdl_rect(int _x, int _y, int _w, int _h)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}
};

#endif // !defined(AFX_SDL_RECT_H__98074340_70C5_11D7_B607_0000C006A2C2__INCLUDED_)
