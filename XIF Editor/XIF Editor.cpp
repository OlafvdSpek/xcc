#include "stdafx.h"
#include "XIF Editor.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "XIF EditorDoc.h"

BEGIN_MESSAGE_MAP(CXIFEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CXIFEditorApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CXIFEditorApp theApp;

BOOL CXIFEditorApp::InitInstance()
{
	AfxEnableControlContainer();

	SetRegistryKey("Spek Soft");
	LoadStdProfileSettings(16);  // Load standard INI file options (including MRU)

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_XIFTYPE,
		RUNTIME_CLASS(CXIFEditorDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		NULL);
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
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew) 
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	return TRUE;
}
