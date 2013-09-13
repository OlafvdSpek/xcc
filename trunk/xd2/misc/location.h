#pragma once

class Clocation
{
public:
	Clocation() = default;

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

	void assign(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	int x;
	int y;
};
