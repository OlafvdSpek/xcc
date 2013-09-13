#pragma once

class Csdl_color: public SDL_Color
{
public:
	Csdl_color() = default;

	Csdl_color(int _r, int _g, int _b)
	{
		r = _r;
		g = _g;
		b = _b;
	}
};
