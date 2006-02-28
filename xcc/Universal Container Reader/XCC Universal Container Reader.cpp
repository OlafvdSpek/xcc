// XCC Universal Container Reader.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XCC Universal Container Reader.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "XCC Universal Container ReaderDoc.h"
#include "XCC Universal Container ReaderView.h"
#include "formats_dlg.h"

#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCUniversalContainerReaderApp

BEGIN_MESSAGE_MAP(CXCCUniversalContainerReaderApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCUniversalContainerReaderApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCUniversalContainerReaderApp construction

CXCCUniversalContainerReaderApp::CXCCUniversalContainerReaderApp()
{
	m_mru_format = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXCCUniversalContainerReaderApp object

CXCCUniversalContainerReaderApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXCCUniversalContainerReaderApp initialization

enum
{
	ki_formats,
	ki_library,
};

BOOL CXCCUniversalContainerReaderApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("XCC"));

	LoadStdProfileSettings(16);  // Load standard INI file options (including MRU)

	xcc_dirs::load_from_registry();

	// Register document templates

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_XCCUNITYPE,
		RUNTIME_CLASS(CXCCUniversalContainerReaderDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CXCCUniversalContainerReaderView));
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
	{
		Cxif_key key;
		if (!key.load_key(Cvirtual_binary(data_fname())))
		{
			// m_formats.import(key.open_key_read(ki_formats));
			m_library.import(key.open_key_read(ki_library));
		}
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CXCCUniversalContainerReaderApp message handlers


string CXCCUniversalContainerReaderApp::data_fname()
{
	return xcc_dirs::get_data_dir() + "xucr_data.xif";
}

int CXCCUniversalContainerReaderApp::ExitInstance() 
{
	{
		Cxif_key key;
		key.open_key_write(ki_formats) = formats().export();
		key.open_key_write(ki_library) = library().export();
		key.vdata().save(data_fname());
	}
	return CWinApp::ExitInstance();
}

CDocument* CXCCUniversalContainerReaderApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	Cformats_dlg dlg(formats());
	{
		const char* p = strrchr(lpszFileName, '.');
		if (p)
			dlg.hint_extension(p + 1);
	}
	if (IDOK != dlg.DoModal())
		return NULL;
	m_mru_format = &dlg.format();
	return CWinApp::OpenDocumentFile(lpszFileName);
}
