// XCC Editor.h : main header file for the XCC EDITOR application
//

#if !defined(AFX_XCCEDITOR_H__4E596E26_F686_11D2_B601_D35C3DCCB8F1__INCLUDED_)
#define AFX_XCCEDITOR_H__4E596E26_F686_11D2_B601_D35C3DCCB8F1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXCCEditorApp:
// See XCC Editor.cpp for the implementation of this class
//

class CXCCEditorApp : public CWinApp
{
public:
	int ExitInstance();
	CXCCEditorApp();
	~CXCCEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXCCEditorApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_save_data;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCEDITOR_H__4E596E26_F686_11D2_B601_D35C3DCCB8F1__INCLUDED_)
