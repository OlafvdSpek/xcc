// MF Tester.h : main header file for the MF TESTER application
//

#if !defined(AFX_MFTESTER_H__D4C04590_D6A9_472D_9A0F_40E9D8B9C20E__INCLUDED_)
#define AFX_MFTESTER_H__D4C04590_D6A9_472D_9A0F_40E9D8B9C20E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFTesterApp:
// See MF Tester.cpp for the implementation of this class
//

class CMFTesterApp : public CWinApp
{
public:
	CMFTesterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFTesterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMFTesterApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFTESTER_H__D4C04590_D6A9_472D_9A0F_40E9D8B9C20E__INCLUDED_)
