// XCC Mod Creator.h : main header file for the XCC MOD CREATOR application
//

#if !defined(AFX_XCCMODCREATOR_H__CA392AE6_CC6E_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XCCMODCREATOR_H__CA392AE6_CC6E_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXCCModCreatorApp:
// See XCC Mod Creator.cpp for the implementation of this class
//

class CXCCModCreatorApp : public CWinApp
{
public:
	CXCCModCreatorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCModCreatorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CXCCModCreatorApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCMODCREATOR_H__CA392AE6_CC6E_11D4_B606_0000B4936994__INCLUDED_)
