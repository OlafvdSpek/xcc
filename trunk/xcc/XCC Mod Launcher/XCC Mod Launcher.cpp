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

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	string fname = cmdInfo.m_strFileName;
	if (fname.empty())
	{
		Cfname exe_fname = GetModuleFileName();
		exe_fname.set_ext(".xmlf");
		if (exe_fname.exists())
			fname = exe_fname;
	}
	if (fname.empty())
	{
		const char* xmlf_filter = "XMLF files (*.xmlf)|*.xmlf|";
		CFileDialog file_dlg(true, NULL, 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, xmlf_filter, NULL);
		if (IDOK == file_dlg.DoModal())
			fname = file_dlg.GetPathName();
	}
	if (!fname.empty())
	{
		CXCCModLauncherDlg dlg;
		dlg.set_mod_fname(fname);
		m_pMainWnd = &dlg;
		dlg.DoModal();
	}
	return false;
}
