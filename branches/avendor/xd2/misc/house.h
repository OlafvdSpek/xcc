// house.h: interface for the Chouse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOUSE_H__4EA6B6A6_2DFE_11D6_B861_0000B4936994__INCLUDED_)
#define AFX_HOUSE_H__4EA6B6A6_2DFE_11D6_B861_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct t_house_data
{
	const char* name;
};

class Chouse  
{
public:
	string name() const
	{
		return m_name;
	};

	void load(t_house_data d);
	Chouse();
	virtual ~Chouse();
private:
	string m_name;
};

#endif // !defined(AFX_HOUSE_H__4EA6B6A6_2DFE_11D6_B861_0000B4936994__INCLUDED_)
