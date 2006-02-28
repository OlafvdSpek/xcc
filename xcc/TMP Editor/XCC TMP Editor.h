// XCC TMP Editor.h : main header file for the XCC TMP EDITOR application
//

#if !defined(AFX_XCCTMPEDITOR_H__64DA813B_F21A_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XCCTMPEDITOR_H__64DA813B_F21A_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXCCTMPEditorApp:
// See XCC TMP Editor.cpp for the implementation of this class
//

class CXCCTMPEditorApp : public CWinApp
{
public:
	CXCCTMPEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCTMPEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CXCCTMPEditorApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCTMPEDITOR_H__64DA813B_F21A_11D4_B606_0000B4936994__INCLUDED_)
