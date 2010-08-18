#pragma once

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

	void load(const t_player_data&);
private:
	int m_credits;
	Chouse* m_house;
	string m_name;
};
