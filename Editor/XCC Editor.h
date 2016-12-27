#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

class CXCCEditorApp : public CWinApp
{
public:
	int ExitInstance();
	CXCCEditorApp();

	//{{AFX_VIRTUAL(CXCCEditorApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXCCEditorApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_save_data;
};
