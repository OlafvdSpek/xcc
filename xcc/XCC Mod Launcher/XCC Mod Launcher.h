// XCC Mod Launcher.h : main header file for the XCC MOD LAUNCHER application
//

#if !defined(AFX_XCCMODLAUNCHER_H__A69C40C3_D1B9_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_XCCMODLAUNCHER_H__A69C40C3_D1B9_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXCCModLauncherApp:
// See XCC Mod Launcher.cpp for the implementation of this class
//

class CXCCModLauncherApp : public CWinApp
{
public:
	CXCCModLauncherApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCModLauncherApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXCCModLauncherApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCMODLAUNCHER_H__A69C40C3_D1B9_11D4_A95D_0050042229FC__INCLUDED_)
