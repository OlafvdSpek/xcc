// player.h: interface for the Cplayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYER_H__4EA6B6A7_2DFE_11D6_B861_0000B4936994__INCLUDED_)
#define AFX_PLAYER_H__4EA6B6A7_2DFE_11D6_B861_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "house.h"

struct t_player_data
{
	int credits;
	Chouse* house;
	const char* name;
};

class Cplayer  
{
public:
	const Chouse& house() const
	{
		return *m_house;
	}

	string name() const
	{
		return m_name;
	};

	void load(t_player_data d);
	Cplayer();
	virtual ~Cplayer();
private:
	int m_credits;
	Chouse* m_house;
	string m_name;
};

#endif // !defined(AFX_PLAYER_H__4EA6B6A7_2DFE_11D6_B861_0000B4936994__INCLUDED_)
