#include "stdafx.h"
#include "player.h"

void Cplayer::load(const t_player_data& d)
{
	m_credits = d.credits;
	m_house = d.house;
	m_name = d.name;
}
