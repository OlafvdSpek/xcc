// XRG Mod Launcher.h : main header file for the XRG MOD LAUNCHER application
//

#if !defined(AFX_XRGMODLAUNCHER_H__41EEDC9D_B099_43A4_A8D9_E50D2ECF6B42__INCLUDED_)
#define AFX_XRGMODLAUNCHER_H__41EEDC9D_B099_43A4_A8D9_E50D2ECF6B42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXRGModLauncherApp:
// See XRG Mod Launcher.cpp for the implementation of this class
//

class CXRGModLauncherApp : public CWinApp
{
public:
	CXRGModLauncherApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXRGModLauncherApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXRGModLauncherApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XRGMODLAUNCHER_H__41EEDC9D_B099_43A4_A8D9_E50D2ECF6B42__INCLUDED_)
