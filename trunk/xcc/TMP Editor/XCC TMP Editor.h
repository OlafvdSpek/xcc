#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

class CXCCTMPEditorApp : public CWinApp
{
public:
	CXCCTMPEditorApp();

	//{{AFX_VIRTUAL(CXCCTMPEditorApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXCCTMPEditorApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
