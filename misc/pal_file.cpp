#include "stdafx.h"
#include "pal_file.h"

#include <fstream>

bool Cpal_file::is_valid() const
{
	if (get_size() != sizeof(t_palet))
		return false;
	const t_palet_entry* p = get_palet();
	for (int i = 0; i < 256; i++)
	{
		if ((p[i].r | p[i].g | p[i].b) & 0xc0)
			return false;
	}
	return true;
}

ostream& Cpal_file::extract_as_pal_jasc(ostream& os, bool shift_left) const
{
	os << "JASC-PAL" << endl
		<< "0100" << endl
		<< "256" << endl;
	t_palet palet;
	if (shift_left)
		convert_palet_18_to_24(get_palet(), palet);
	else
		memcpy(palet, get_palet(), sizeof(t_palet));
	for (int i = 0; i < 256; i++)
		os << static_cast<int>(palet[i].r) << ' ' << static_cast<int>(palet[i].g) << ' ' << static_cast<int>(palet[i].b) << endl;
	return os;
}
