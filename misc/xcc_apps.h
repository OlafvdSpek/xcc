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
	typedef map<t_app, string> t_map;

	void init();
	void set_exe(t_app app, string exe);

	t_map m_map;
};
