#pragma once

#include "cell.h"
#include "location.h"

class Cmap
{
public:
	Ccell& cell(Clocation location);
	void object(Cobject* object);

	Cmap();
	virtual ~Cmap();
private:
	int m_cx;
	int m_cy;
	Ccell* m_map;
};
