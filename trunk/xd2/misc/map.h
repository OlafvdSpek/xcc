#pragma once

#include "cell.h"
#include "location.h"

class Cmap
{
public:
	Ccell& cell(Clocation location);
	void object(Cobject* object);
private:
	int cx_;
	int cy_;
	Ccell* map_ = NULL;
};
