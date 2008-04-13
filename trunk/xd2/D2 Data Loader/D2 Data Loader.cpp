#include "stdafx.h"

#include "mix_file.h"
#include "xcc_dirs.h"
#include "xd2_files.h"

int main()
{
	Cmix_file::enable_ft_support();
	xcc_dirs::load_from_registry();
	string dir = xcc_dirs::get_dir(game_dune2);

	Cxd2_files files;
	if (files.load(dir))
		return 1;
	files.save().vdata().save(xcc_dirs::get_data_dir() + "xd2 files.xif");
	return 0;
}