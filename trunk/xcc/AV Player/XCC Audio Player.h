#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "xcc_dirs.h"

class CXCCAudioPlayerApp : public CWinApp
{
public:
	//{{AFX_VIRTUAL(CXCCAudioPlayerApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXCCAudioPlayerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
