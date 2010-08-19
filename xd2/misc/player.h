#pragma once

#include "house.h"

class Cplayer
{
public:
	Cplayer();
	Cplayer(const map<string, string>&);

	Chouse* house;
	string name;
	int credits;
};
