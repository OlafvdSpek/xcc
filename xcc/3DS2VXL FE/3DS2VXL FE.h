#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

class CMy3DS2VXLFEApp : public CWinApp
{
public:
	//{{AFX_VIRTUAL(CMy3DS2VXLFEApp)
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMy3DS2VXLFEApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
