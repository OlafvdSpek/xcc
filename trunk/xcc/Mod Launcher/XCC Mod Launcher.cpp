// XCC Mod Launcher.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XCC Mod Launcher.h"
#include "XCC Mod LauncherDlg.h"
#include "XMLCommandLineInfo.h"

#include "xcc_dirs.h"
#include "xcc_log.h"
#include "xcc_mod.h"

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
	xcc_log::attach_file("XCC Mod Launcher log.txt");

	CXMLCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	string fname = cmdInfo.m_strFileName;
	if (fname.empty())
	{
		Cfname exe_fname = GetModuleFileName();
		Cvirtual_binary s(GetModuleFileName());
		if (s && s.size() > 8)
		{
			int cb_mod = reinterpret_cast<const int*>(s.data_end())[-1];
			if (cb_mod > 4 && cb_mod + 4 < s.size())
			{
				Cvirtual_binary mod = s.sub_bin(s.size() - 4 - cb_mod, cb_mod);
				if (!memcmp(mod, "XIF\x1a", 4))
				{
					if (cmdInfo.m_activate)
					{
						Cxif_key key;
						if (!key.load_key(mod))
							Cxcc_mod().activate(key, false, -1);
					}
					else
					{
						CXCCModLauncherDlg dlg;
						dlg.set_mod(mod);
						dlg.set_mod_fname(exe_fname);
						m_pMainWnd = &dlg;
						dlg.DoModal();
					}
					return false;
				}
			}
		}
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
