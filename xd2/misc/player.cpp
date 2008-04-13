#include "stdafx.h"
#include "player.h"

Cplayer::Cplayer()
{

}

Cplayer::~Cplayer()
{

}

void Cplayer::load(t_player_data d)
{
	m_credits = d.credits;
	m_house = d.house;
	m_name = d.name;
}
