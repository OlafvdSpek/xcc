// 3DS2VXL FE.h : main header file for the 3DS2VXL FE application
//

#if !defined(AFX_3DS2VXLFE_H__C75E5C03_EFC6_11D4_A95E_0050042229FC__INCLUDED_)
#define AFX_3DS2VXLFE_H__C75E5C03_EFC6_11D4_A95E_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy3DS2VXLFEApp:
// See 3DS2VXL FE.cpp for the implementation of this class
//

class CMy3DS2VXLFEApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DS2VXLFEApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy3DS2VXLFEApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DS2VXLFE_H__C75E5C03_EFC6_11D4_A95E_0050042229FC__INCLUDED_)
