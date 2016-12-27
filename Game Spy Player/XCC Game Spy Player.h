#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

class CXCCGameSpyPlayerApp : public CWinApp
{
public:
	static string data_fname();

	//{{AFX_VIRTUAL(CXCCGameSpyPlayerApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXCCGameSpyPlayerApp)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
