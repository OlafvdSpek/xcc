// XCC Editor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XCC Editor.h"

#include "MainFrm.h"
#include "XCC EditorDoc.h"
#include "XCC EditorView.h"

#include "xcc_mixs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCEditorApp

BEGIN_MESSAGE_MAP(CXCCEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCEditorApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCEditorApp construction

CXCCEditorApp::CXCCEditorApp()
{
	m_save_data = false;
}

CXCCEditorApp::~CXCCEditorApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXCCEditorApp object

CXCCEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXCCEditorApp initialization

BOOL CXCCEditorApp::InitInstance()
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

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)

	xcc_dirs::use_external_files(false);
	xcc_dirs::load_from_registry();
	if (Cxcc_mixs::open())
	{
		AfxMessageBox("Unable to open all mix files, insert a C&C cd or see readme.txt for details", MB_ICONEXCLAMATION);
		return false;
	}
	if (Cxcc_overlays::load_data() ||
		Cxcc_templates::load_data() ||
		xcc_infantry::load_data() ||
		xcc_structures::load_data() ||
		xcc_units::load_data()) 
	{
		AfxMessageBox("Data load failed", MB_ICONEXCLAMATION);
		return false;
	}
	m_save_data = true;
	
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CXCCEditorDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CXCCEditorView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}

int CXCCEditorApp::ExitInstance()
{
	if (m_save_data)
	{
		Cxcc_overlays::save_data();
		Cxcc_templates::save_data();
		
		xcc_infantry::save_data();
		xcc_structures::save_data();
		xcc_units::save_data();
	}

	shp_images::destroy();
	xcc_infantry::destroy();
	xcc_structures::destroy();
	xcc_units::destroy();
	Cxcc_mixs::close();
	xcc_dirs::save_to_registry();
	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CXCCEditorApp commands

