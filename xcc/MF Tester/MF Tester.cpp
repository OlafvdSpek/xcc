// MF Tester.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MF Tester.h"
#include "MF TesterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFTesterApp

BEGIN_MESSAGE_MAP(CMFTesterApp, CWinApp)
	//{{AFX_MSG_MAP(CMFTesterApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFTesterApp construction

CMFTesterApp::CMFTesterApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMFTesterApp object

CMFTesterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMFTesterApp initialization

BOOL CMFTesterApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CMFTesterDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return false;
}
