// XCC Audio Player.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XCC Audio Player.h"
#include "XCC Audio PlayerDlg.h"
#include "mix_cache.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCAudioPlayerApp

BEGIN_MESSAGE_MAP(CXCCAudioPlayerApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCAudioPlayerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCAudioPlayerApp construction

CXCCAudioPlayerApp::CXCCAudioPlayerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXCCAudioPlayerApp object

CXCCAudioPlayerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXCCAudioPlayerApp initialization

BOOL CXCCAudioPlayerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetRegistryKey("XCC");

	CXCCAudioPlayerDlg dlg;
	m_pMainWnd = &dlg;
	Cmix_file::enable_ft_support();
	xcc_dirs::load_from_registry();
	mix_cache::load();
	dlg.DoModal();
	mix_cache::save();
	xcc_dirs::save_to_registry();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
