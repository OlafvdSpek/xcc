#include "stdafx.h"
#include "XCC Editor.h"

#include "MainFrm.h"
#include "XCC EditorDoc.h"
#include "XCC EditorView.h"

#include "shp_images.h"
#include "xcc_mixs.h"

BEGIN_MESSAGE_MAP(CXCCEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCEditorApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CXCCEditorApp::CXCCEditorApp()
{
	m_save_data = false;
}

CXCCEditorApp theApp;

BOOL CXCCEditorApp::InitInstance()
{
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetRegistryKey("XCC");

	LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)

	xcc_dirs::use_external_files(false);
	xcc_dirs::load_from_registry();
	if (Cxcc_mixs::open())
	{
		AfxMessageBox("Unable to open all mix files, insert a C&C CD or see readme.txt for details", MB_ICONEXCLAMATION);
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
	
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CXCCEditorDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CXCCEditorView));
	AddDocTemplate(pDocTemplate);

	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

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
