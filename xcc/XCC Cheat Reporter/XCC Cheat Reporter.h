// XCC Cheat Reporter.h : main header file for the XCC CHEAT REPORTER application
//

#if !defined(AFX_XCCCHEATREPORTER_H__DDCDF143_1315_11D5_A95E_0050042229FC__INCLUDED_)
#define AFX_XCCCHEATREPORTER_H__DDCDF143_1315_11D5_A95E_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXCCCheatReporterApp:
// See XCC Cheat Reporter.cpp for the implementation of this class
//

class CXCCCheatReporterApp : public CWinApp
{
public:
	CXCCCheatReporterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCCheatReporterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXCCCheatReporterApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCCHEATREPORTER_H__DDCDF143_1315_11D5_A95E_0050042229FC__INCLUDED_)
