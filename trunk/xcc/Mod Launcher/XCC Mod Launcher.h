#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

class CXCCModLauncherApp : public CWinApp
{
public:
	//{{AFX_VIRTUAL(CXCCModLauncherApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXCCModLauncherApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
