#include "stdafx.h"
#include <fstream>
#include "pal_file.h"

int Cpal_file::extract_as_pal_jasc(const string& name) const
{
	ofstream f(name.c_str());
	f << "JASC-PAL" << endl
		<< "0100" << endl
		<< "256" << endl;
	t_palet palet;
	convert_palet_18_to_24(get_palet(), palet);
	for (int i = 0; i < 256; i++)
		f << static_cast<int>(palet[i].r) << ' ' << static_cast<int>(palet[i].g) << ' ' << static_cast<int>(palet[i].b) << endl;
	return f.fail();
}
