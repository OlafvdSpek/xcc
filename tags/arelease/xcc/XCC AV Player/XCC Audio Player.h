// XCC Audio Player.h : main header file for the XCC AUDIO PLAYER application
//

#if !defined(AFX_XCCAUDIOPLAYER_H__D87F6A0C_DFB1_11D2_B750_ADF86D0B2966__INCLUDED_)
#define AFX_XCCAUDIOPLAYER_H__D87F6A0C_DFB1_11D2_B750_ADF86D0B2966__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "xcc_dirs.h"

/////////////////////////////////////////////////////////////////////////////
// CXCCAudioPlayerApp:
// See XCC Audio Player.cpp for the implementation of this class
//

class CXCCAudioPlayerApp : public CWinApp
{
public:
	CXCCAudioPlayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCAudioPlayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXCCAudioPlayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCAUDIOPLAYER_H__D87F6A0C_DFB1_11D2_B750_ADF86D0B2966__INCLUDED_)
