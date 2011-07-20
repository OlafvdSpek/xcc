#pragma once

class Clocation
{
public:
	Clocation()
	{
	}

	Clocation(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	int xh() const
	{
		return x >> 8;
	}

	int yh() const
	{
		return y >> 8;
	}

	int x;
	int y;
};
