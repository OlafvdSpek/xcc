// XCC Map Encoder.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XCC Map Encoder.h"
#include "XCC Map EncoderDlg.h"

#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCMapEncoderApp

BEGIN_MESSAGE_MAP(CXCCMapEncoderApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCMapEncoderApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCMapEncoderApp construction

CXCCMapEncoderApp::CXCCMapEncoderApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXCCMapEncoderApp object

CXCCMapEncoderApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXCCMapEncoderApp initialization

BOOL CXCCMapEncoderApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	xcc_dirs::load_from_registry();

	CXCCMapEncoderDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return false;
}
