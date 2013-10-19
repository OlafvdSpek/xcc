#pragma once

class Csdl_rect : public SDL_Rect
{
public:
	Csdl_rect() = default;

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
