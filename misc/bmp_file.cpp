#include "stdafx.h"
#include "bmp_file.h"

bool Cbmp_file::is_valid() const
{
	const byte* s = data();
	return !(size() < 2 
		|| s[0] != 'B'
		|| s[1] != 'M');
}

