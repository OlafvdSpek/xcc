// XCC Cheat Reporter.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XCC Cheat Reporter.h"
#include "XCC Cheat ReporterDlg.h"

#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCCheatReporterApp

BEGIN_MESSAGE_MAP(CXCCCheatReporterApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCCheatReporterApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCCheatReporterApp construction

CXCCCheatReporterApp::CXCCCheatReporterApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXCCCheatReporterApp object

CXCCCheatReporterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXCCCheatReporterApp initialization

BOOL CXCCCheatReporterApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetRegistryKey("XCC");

	xcc_dirs::load_from_registry();

	CXCCCheatReporterDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return false;
}
