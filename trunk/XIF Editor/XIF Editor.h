#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

class CXIFEditorApp : public CWinApp
{
public:
	//{{AFX_VIRTUAL(CXIFEditorApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXIFEditorApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
