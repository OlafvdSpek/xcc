// XCC TMP Editor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XCC TMP Editor.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "XCC TMP EditorDoc.h"
#include "LeftView.h"

#include "mix_cache.h"
#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCTMPEditorApp

BEGIN_MESSAGE_MAP(CXCCTMPEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCTMPEditorApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCTMPEditorApp construction

CXCCTMPEditorApp::CXCCTMPEditorApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXCCTMPEditorApp object

CXCCTMPEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXCCTMPEditorApp initialization

BOOL CXCCTMPEditorApp::InitInstance()
{
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
	mix_cache::load();

	// Register document templates

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_TMPTYPE,
		RUNTIME_CLASS(CXCCTMPEditorDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CLeftView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew) 
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CXCCTMPEditorApp message handlers

