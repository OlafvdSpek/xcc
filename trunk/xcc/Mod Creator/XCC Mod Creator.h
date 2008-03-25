#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

class CXCCModCreatorApp : public CWinApp
{
public:
	CXCCModCreatorApp();

	//{{AFX_VIRTUAL(CXCCModCreatorApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXCCModCreatorApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
