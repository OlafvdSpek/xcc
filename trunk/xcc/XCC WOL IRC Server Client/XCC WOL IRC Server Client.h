// XCC WOL IRC Server Client.h : main header file for the XCC WOL IRC SERVER CLIENT application
//

#if !defined(AFX_XCCWOLIRCSERVERCLIENT_H__FF89AE47_A3EA_4F6C_8341_64E344EC6D64__INCLUDED_)
#define AFX_XCCWOLIRCSERVERCLIENT_H__FF89AE47_A3EA_4F6C_8341_64E344EC6D64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXCCWOLIRCServerClientApp:
// See XCC WOL IRC Server Client.cpp for the implementation of this class
//

class CXCCWOLIRCServerClientApp : public CWinApp
{
public:
	CXCCWOLIRCServerClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCWOLIRCServerClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXCCWOLIRCServerClientApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCWOLIRCSERVERCLIENT_H__FF89AE47_A3EA_4F6C_8341_64E344EC6D64__INCLUDED_)
