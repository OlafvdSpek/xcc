// sdl_color.h: interface for the Csdl_color class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDL_COLOR_H__98074341_70C5_11D7_B607_0000C006A2C2__INCLUDED_)
#define AFX_SDL_COLOR_H__98074341_70C5_11D7_B607_0000C006A2C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Csdl_color: public SDL_Color
{
public:
	Csdl_color()
	{
	}

	Csdl_color(int _r, int _g, int _b)
	{
		r = _r;
		g = _g;
		b = _b;
	}
};

#endif // !defined(AFX_SDL_COLOR_H__98074341_70C5_11D7_B607_0000C006A2C2__INCLUDED_)
