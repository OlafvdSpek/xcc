// XCC WOL IRC Server Client.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XCC WOL IRC Server Client.h"
#include "XCC WOL IRC Server ClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCWOLIRCServerClientApp

BEGIN_MESSAGE_MAP(CXCCWOLIRCServerClientApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCWOLIRCServerClientApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCWOLIRCServerClientApp construction

CXCCWOLIRCServerClientApp::CXCCWOLIRCServerClientApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXCCWOLIRCServerClientApp object

CXCCWOLIRCServerClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXCCWOLIRCServerClientApp initialization

BOOL CXCCWOLIRCServerClientApp::InitInstance()
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 0), &wsadata);

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CXCCWOLIRCServerClientDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
