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
	file_put(xcc_dirs::get_data_dir() + "xd2 files.xif", files.save().vdata());
	shared_data exe = file_get(dir + "dune2.exe");
	if (!exe.size())
		return 1;
	const char* e = reinterpret_cast<const char*>(exe.data());
	auto bt = reinterpret_cast<const t_building_type*>(&exe[194010]);
	for (auto& i : boost::make_iterator_range(bt, bt + 19))
	{
		ofstream("../xd2 be/dune/objects/" + to_lower_copy(string(e + 229504 + i.name)) + ".ini")
			<< "cameo = " << i.cameo_shp_index << endl
			<< "class = structure" << endl
			<< "cost = " << i.cost << endl
			<< "cx = " << (i.size == 0 || i.size == 2 ? 1 : i.size == 1 || i.size == 3 || i.size == 4 ? 2 : 3) << endl
			<< "cy = " << (i.size == 0 || i.size == 1 ? 1 : i.size == 2 || i.size == 3 || i.size == 5 ? 2 : 3) << endl
			<< "icon = " << i.icon_index << endl
			<< "power = " << i.power_in << endl
			<< "sight = " << i.sight << endl
			<< "strength = " << i.strength << endl
			<< "techlevel = " << i.techlevel << endl
			<< "wsa = " << e + 229504 + i.wsa << endl
			;
	}
	auto ut = reinterpret_cast<const t_unit_type*>(&exe[195840]);
	for (auto& i : boost::make_iterator_range(ut, ut + 27))
	{
		ofstream("../xd2 be/dune/objects/" + to_lower_copy(string(e + 229504 + i.name)) + ".ini")
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
