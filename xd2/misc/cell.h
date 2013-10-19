#pragma once

#include "object.h"

class Ccell
{
public:
	Cobject* object()
	{
		return m_object;
	}

	void object(Cobject* object)
	{
		m_object = object;
	}
private:
	Cobject* m_object = NULL;
};
