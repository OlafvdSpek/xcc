// xcc_apps.h: interface for the Cxcc_apps class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCC_APPS_H__B39A2121_E564_11D4_A95E_0050042229FC__INCLUDED_)
#define AFX_XCC_APPS_H__B39A2121_E564_11D4_A95E_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_XCC_APPS_H__B39A2121_E564_11D4_A95E_0050042229FC__INCLUDED_)
