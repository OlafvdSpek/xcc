// XCC Mod Creator.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XCC Mod Creator.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "XCC Mod CreatorDoc.h"
#include "LeftView.h"

#include "xcc_dirs.h"
#include "xcc_log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CXCCModCreatorApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCModCreatorApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CXCCModCreatorApp::CXCCModCreatorApp()
{
}

CXCCModCreatorApp theApp;

BOOL CXCCModCreatorApp::InitInstance()
{
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetRegistryKey("XCC");

	LoadStdProfileSettings(16);  // Load standard INI file options (including MRU)

	xcc_dirs::load_from_registry();
	xcc_log::attach_file("XCC Mod Creator log.txt");

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_XCCMODTYPE,
		RUNTIME_CLASS(CXCCModCreatorDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CLeftView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	m_pMainWnd->DragAcceptFiles();

	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	return TRUE;
}
