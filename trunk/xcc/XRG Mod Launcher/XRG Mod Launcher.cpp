// XRG Mod Launcher.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XRG Mod Launcher.h"
#include "XRG Mod LauncherDlg.h"

#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXRGModLauncherApp

BEGIN_MESSAGE_MAP(CXRGModLauncherApp, CWinApp)
	//{{AFX_MSG_MAP(CXRGModLauncherApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXRGModLauncherApp construction

CXRGModLauncherApp::CXRGModLauncherApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXRGModLauncherApp object

CXRGModLauncherApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXRGModLauncherApp initialization

BOOL CXRGModLauncherApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	xcc_dirs::load_from_registry();

	CXRGModLauncherDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return false;
}
