// XCC MIX Editor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XCC MIX Editor.h"
#include "XCC MIX EditorDlg.h"
#include "id_log.h"
#include "mix_cache.h"
#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCMIXEditorApp

BEGIN_MESSAGE_MAP(CXCCMIXEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCMIXEditorApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCMIXEditorApp construction

CXCCMIXEditorApp::CXCCMIXEditorApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXCCMIXEditorApp object

CXCCMIXEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXCCMIXEditorApp initialization

BOOL CXCCMIXEditorApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetRegistryKey("XCC");

	CXCCMIXEditorDlg dlg;
	m_pMainWnd = &dlg;

	xcc_dirs::load_from_registry();
	mix_database::load();
	mix_cache::load();
	dlg.DoModal();
	mix_cache::save();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
