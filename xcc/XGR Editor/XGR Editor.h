// XGR Editor.h : main header file for the XGR EDITOR application
//

#if !defined(AFX_XGREDITOR_H__0B28DE65_BBCE_4A65_B7B7_CA793166718B__INCLUDED_)
#define AFX_XGREDITOR_H__0B28DE65_BBCE_4A65_B7B7_CA793166718B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXGREditorApp:
// See XGR Editor.cpp for the implementation of this class
//

class CXGREditorApp : public CWinApp
{
public:
	CXGREditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXGREditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CXGREditorApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XGREDITOR_H__0B28DE65_BBCE_4A65_B7B7_CA793166718B__INCLUDED_)
