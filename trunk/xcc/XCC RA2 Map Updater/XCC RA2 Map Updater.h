// XCC RA2 Map Updater.h : main header file for the XCC RA2 MAP UPDATER application
//

#if !defined(AFX_XCCRA2MAPUPDATER_H__2F297D03_012A_11D5_B606_0000B4936994__INCLUDED_)
#define AFX_XCCRA2MAPUPDATER_H__2F297D03_012A_11D5_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXCCRA2MapUpdaterApp:
// See XCC RA2 Map Updater.cpp for the implementation of this class
//

class CXCCRA2MapUpdaterApp : public CWinApp
{
public:
	void create();
	int download_update(string link, string fname);
	int update();
	CXCCRA2MapUpdaterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCRA2MapUpdaterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXCCRA2MapUpdaterApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCRA2MAPUPDATER_H__2F297D03_012A_11D5_B606_0000B4936994__INCLUDED_)
