// XCC Game Spy Player.h : main header file for the XCC GAME SPY PLAYER application
//

#if !defined(AFX_XCCGAMESPYPLAYER_H__72CB31BF_E395_4D07_A315_34386845C964__INCLUDED_)
#define AFX_XCCGAMESPYPLAYER_H__72CB31BF_E395_4D07_A315_34386845C964__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXCCGameSpyPlayerApp:
// See XCC Game Spy Player.cpp for the implementation of this class
//

class CXCCGameSpyPlayerApp : public CWinApp
{
public:
	static string data_fname();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCGameSpyPlayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CXCCGameSpyPlayerApp)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCGAMESPYPLAYER_H__72CB31BF_E395_4D07_A315_34386845C964__INCLUDED_)
