// XCC Mod Launcher.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XCC Mod Launcher.h"
#include "XCC Mod LauncherDlg.h"

#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCModLauncherApp

BEGIN_MESSAGE_MAP(CXCCModLauncherApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCModLauncherApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCModLauncherApp construction

CXCCModLauncherApp::CXCCModLauncherApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXCCModLauncherApp object

CXCCModLauncherApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXCCModLauncherApp initialization

BOOL CXCCModLauncherApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	xcc_dirs::load_from_registry();

	CXCCModLauncherDlg dlg;

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if (0)
	{
		CXCCModLauncherDlg dlg;
		dlg.set_mod_fname("redstorm.xmlf");		
		m_pMainWnd = &dlg;
		dlg.DoModal();
		return false;
	}
	string fname = cmdInfo.m_strFileName;
	if (cmdInfo.m_strFileName.IsEmpty())
	{
		const char* xmlf_filter = "XMLF files (*.xmlf)|*.xmlf|";
		CFileDialog file_dlg(true, NULL, 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, xmlf_filter, NULL);
		if (IDOK == file_dlg.DoModal())
		{
			dlg.set_mod_fname(static_cast<string>(file_dlg.GetPathName()));		
			m_pMainWnd = &dlg;
			dlg.DoModal();
		}
	}
	else
	{
		dlg.set_mod_fname(static_cast<string>(cmdInfo.m_strFileName));
		m_pMainWnd = &dlg;
		dlg.DoModal();
	}
	return false;
}
