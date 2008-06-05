#include "stdafx.h"
#include "XCC WOL IRC Server Client.h"
#include "XCC WOL IRC Server ClientDlg.h"

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
	CXCCWOLIRCServerClientDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
