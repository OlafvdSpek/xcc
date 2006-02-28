// XCC RA2 Radar Customizer.h : main header file for the XCC RA2 RADAR CUSTOMIZER application
//

#if !defined(AFX_XCCRA2RADARCUSTOMIZER_H__5043C083_05B3_11D5_A95E_0050042229FC__INCLUDED_)
#define AFX_XCCRA2RADARCUSTOMIZER_H__5043C083_05B3_11D5_A95E_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXCCRA2RadarCustomizerApp:
// See XCC RA2 Radar Customizer.cpp for the implementation of this class
//

class CXCCRA2RadarCustomizerApp : public CWinApp
{
public:
	CXCCRA2RadarCustomizerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCRA2RadarCustomizerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXCCRA2RadarCustomizerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCRA2RADARCUSTOMIZER_H__5043C083_05B3_11D5_A95E_0050042229FC__INCLUDED_)
