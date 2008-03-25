#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

class CXCCRA2RadarCustomizerApp: public CWinApp
{
public:
	CXCCRA2RadarCustomizerApp();

	//{{AFX_VIRTUAL(CXCCRA2RadarCustomizerApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXCCRA2RadarCustomizerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
