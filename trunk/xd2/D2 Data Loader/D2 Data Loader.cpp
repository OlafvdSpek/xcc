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
	BOOST_FOREACH(auto& i, files.building_types())
	{
		const char* e = reinterpret_cast<const char*>(files.exe().data());
		ofstream(string("../xd2 be/dune/objects/") + (e + 229504 + i.name) + ".ini")
			<< "cameo = " << i.cameo_shp_index << endl
			<< "class = structure" << endl
			<< "cost = " << i.cost << endl
			<< "icon = " << i.icon_index << endl
			<< "power = " << i.power_in << endl
			<< "sight = " << i.sight << endl
			<< "size = " << i.size << endl
			<< "strength = " << i.strength << endl
			<< "techlevel = " << i.techlevel << endl
			<< "wsa = " << e + 229504 + i.wsa << endl
			;

	}
	BOOST_FOREACH(auto& i, files.unit_types())
	{
		const char* e = reinterpret_cast<const char*>(files.exe().data());
		ofstream(string("../xd2 be/dune/objects/") + (e + 229504 + i.name) + ".ini")
			<< "body = " << i.body_shp_index << endl
			<< "cameo = " << i.cameo_shp_index << endl
			<< "cost = " << i.cost << endl
			<< "sight = " << i.sight << endl
			<< "speed = " << i.speed << endl
			<< "strength = " << i.strength << endl
			<< "turret = " << i.turret_shp_index << endl
			<< "wsa = " << e + 229504 + i.wsa << endl
			;

	}
	return 0;
}
