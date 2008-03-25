#include "stdafx.h"
#include "XCC TMP Editor.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "XCC TMP EditorDoc.h"
#include "LeftView.h"

#include "mix_cache.h"
#include "xcc_dirs.h"

BEGIN_MESSAGE_MAP(CXCCTMPEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCTMPEditorApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CXCCTMPEditorApp::CXCCTMPEditorApp()
{
}

CXCCTMPEditorApp theApp;

BOOL CXCCTMPEditorApp::InitInstance()
{
	SetRegistryKey("XCC");
	LoadStdProfileSettings(16);  // Load standard INI file options (including MRU)
	xcc_dirs::load_from_registry();
	mix_cache::load();

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

	return true;
}
