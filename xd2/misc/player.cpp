#include "stdafx.h"
#include "player.h"

extern map<string, Chouse> g_houses;

Cplayer::Cplayer()
{
}

Cplayer::Cplayer(const map<string, string>& d)
{
	house = &find_ref(g_houses, find_ref(d, "house", ""));
	name = find_ref(d, "name", "");
	credits = find_ref(d, "credits", 1000);
}
