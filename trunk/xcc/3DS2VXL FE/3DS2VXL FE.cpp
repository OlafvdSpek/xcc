// 3DS2VXL FE.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "3DS2VXL FE.h"
#include "3DS2VXL FEDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3DS2VXLFEApp

BEGIN_MESSAGE_MAP(CMy3DS2VXLFEApp, CWinApp)
	//{{AFX_MSG_MAP(CMy3DS2VXLFEApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// The one and only CMy3DS2VXLFEApp object

CMy3DS2VXLFEApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMy3DS2VXLFEApp initialization

BOOL CMy3DS2VXLFEApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CMy3DS2VXLFEDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return false;
}
