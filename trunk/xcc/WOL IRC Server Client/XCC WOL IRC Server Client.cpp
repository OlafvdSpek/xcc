#include "stdafx.h"
#include "XCC WOL IRC Server Client.h"
#include "XCC WOL IRC Server ClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CXCCWOLIRCServerClientApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCWOLIRCServerClientApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CXCCWOLIRCServerClientApp theApp;

BOOL CXCCWOLIRCServerClientApp::InitInstance()
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 0), &wsadata);
#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif
	CXCCWOLIRCServerClientDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
