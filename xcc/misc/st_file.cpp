#include "stdafx.h"
#include <fstream>
#include "st_file.h"

int Cst_file::extract_as_text(const string& name) const
{
	ofstream f(name.c_str());
	for (int i = 0; i < get_c_strings(); i++)
		f << get_string(i) << endl;
	return f.fail();
}

