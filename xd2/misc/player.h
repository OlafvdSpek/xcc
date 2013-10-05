#pragma once

#include "house.h"

class Cplayer
{
public:
	Cplayer() = default;
	Cplayer(const map<string, string>&);

	Chouse* house;
	string name;
	int credits;
};
