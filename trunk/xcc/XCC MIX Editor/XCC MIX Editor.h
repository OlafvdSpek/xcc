// XCC MIX Editor.h : main header file for the XCC MIX EDITOR application
//

#if !defined(AFX_XCCMIXEDITOR_H__A14B9B23_F2B7_11D3_B605_0000B4936994__INCLUDED_)
#define AFX_XCCMIXEDITOR_H__A14B9B23_F2B7_11D3_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXCCMIXEditorApp:
// See XCC MIX Editor.cpp for the implementation of this class
//

class CXCCMIXEditorApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCMIXEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXCCMIXEditorApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCMIXEDITOR_H__A14B9B23_F2B7_11D3_B605_0000B4936994__INCLUDED_)
