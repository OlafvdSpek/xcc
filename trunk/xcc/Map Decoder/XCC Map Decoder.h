#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

class CXCCMapDecoderApp : public CWinApp
{
public:
	CXCCMapDecoderApp();

	//{{AFX_VIRTUAL(CXCCMapDecoderApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXCCMapDecoderApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
