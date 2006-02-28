// XCC Map Encoder.h : main header file for the XCC MAP ENCODER application
//

#if !defined(AFX_XCCMAPENCODER_H__BF046208_FBA8_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XCCMAPENCODER_H__BF046208_FBA8_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXCCMapEncoderApp:
// See XCC Map Encoder.cpp for the implementation of this class
//

class CXCCMapEncoderApp : public CWinApp
{
public:
	CXCCMapEncoderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCMapEncoderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXCCMapEncoderApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCMAPENCODER_H__BF046208_FBA8_11D4_B606_0000B4936994__INCLUDED_)
