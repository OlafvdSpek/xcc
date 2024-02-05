/*
    XCC Utilities and Library
    Copyright (C) 2001  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

enum t_app
{
	app_xap,
	app_xed,
	app_xmr,
	app_xme,
	app_xmc,
	app_xml,
	app_fs,
	app_fa,
	app_se,
	app_semm,
	app_rage,
	app_xcr,
	app_xrc,
	app_xrmu,
	app_xgs,
	app_xgsp,
	app_unknown
};

class Cxcc_apps  
{
public:
	bool is_available(t_app app) const;
	string get_exe(t_app app) const;
	Cxcc_apps();
private:
	using t_map = map<t_app, string>;

	void init();
	void set_exe(t_app app, string exe);

	t_map m_map;
};
