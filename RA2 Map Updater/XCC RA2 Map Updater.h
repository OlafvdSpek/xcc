#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

class CXCCRA2MapUpdaterApp : public CWinApp
{
public:
	void create();
	int download_update(string link, string fname);
	int update();
	CXCCRA2MapUpdaterApp();

	//{{AFX_VIRTUAL(CXCCRA2MapUpdaterApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXCCRA2MapUpdaterApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
