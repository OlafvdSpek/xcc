#pragma once

class Clocation
{
public:
	int x() const
	{
		return m_x;
	}

	int y() const
	{
		return m_y;
	}

	int xh() const
	{
		return x() >> 8;
	}

	int yh() const
	{
		return y() >> 8;
	}

	void x(int x)
	{
		m_x = x;
	}

	void y(int y)
	{
		m_y = y;
	}

	Clocation();
	Clocation(int x, int y);
private:
	int m_x;
	int m_y;
};
