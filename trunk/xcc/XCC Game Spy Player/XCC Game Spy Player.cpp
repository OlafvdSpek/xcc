// XCC Game Spy Player.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XCC Game Spy Player.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "XCC Game Spy PlayerDoc.h"
#include "XCC Game Spy PlayerView.h"

#include "dlg_open.h"
#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCGameSpyPlayerApp

BEGIN_MESSAGE_MAP(CXCCGameSpyPlayerApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCGameSpyPlayerApp)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCGameSpyPlayerApp construction

CXCCGameSpyPlayerApp::CXCCGameSpyPlayerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXCCGameSpyPlayerApp object

CXCCGameSpyPlayerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXCCGameSpyPlayerApp initialization

BOOL CXCCGameSpyPlayerApp::InitInstance()
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

	// Change the registry key under which our settings are stored.
	SetRegistryKey("XCC");

	LoadStdProfileSettings(16);  // Load standard INI file options (including MRU)

	xcc_dirs::load_from_registry();

	// Register document templates

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_XCCGAMTYPE,
		RUNTIME_CLASS(CXCCGameSpyPlayerDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CXCCGameSpyPlayerView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew) 
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CXCCGameSpyPlayerApp message handlers

void CXCCGameSpyPlayerApp::OnFileOpen() 
{
	Cdlg_open dlg;
	Cxif_key key;
	if (!key.load_key(Cvirtual_binary(data_fname())))
		dlg.import_cache(key);
	if (IDOK == dlg.DoModal())
		OpenDocumentFile(dlg.fname().c_str());
	dlg.export_cache().vdata().export(data_fname());
}

string CXCCGameSpyPlayerApp::data_fname()
{
	return xcc_dirs::get_data_dir() + "xgsp_data.xif";
}
