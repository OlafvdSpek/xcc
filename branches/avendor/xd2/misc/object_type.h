// object_type.h: interface for the Cobject_type class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECT_TYPE_H__4EA6B6A9_2DFE_11D6_B861_0000B4936994__INCLUDED_)
#define AFX_OBJECT_TYPE_H__4EA6B6A9_2DFE_11D6_B861_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct t_object_type_data
{
	const char* name;
	int cost;
	int health;
};

class Cobject_type  
{
public:
	string name() const
	{
		return m_name;
	};

	int speed() const
	{
		return m_speed;
	}

	void load(t_object_type_data d);
	Cobject_type();
	virtual ~Cobject_type();
private:
	int m_cost;
	int m_health;
	string m_name;
	int m_speed;
};

#endif // !defined(AFX_OBJECT_TYPE_H__4EA6B6A9_2DFE_11D6_B861_0000B4936994__INCLUDED_)
