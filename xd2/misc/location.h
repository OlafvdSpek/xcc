// location.h: interface for the Clocation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOCATION_H__DC5A4277_71FB_4773_A331_603A9D857AC6__INCLUDED_)
#define AFX_LOCATION_H__DC5A4277_71FB_4773_A331_603A9D857AC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	virtual ~Clocation();
private:
	int m_x;
	int m_y;
};

#endif // !defined(AFX_LOCATION_H__DC5A4277_71FB_4773_A331_603A9D857AC6__INCLUDED_)
