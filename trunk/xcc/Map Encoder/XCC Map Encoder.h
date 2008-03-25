#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

class CXCCMapEncoderApp : public CWinApp
{
public:
	CXCCMapEncoderApp();

	//{{AFX_VIRTUAL(CXCCMapEncoderApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXCCMapEncoderApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
