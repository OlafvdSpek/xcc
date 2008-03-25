#include "stdafx.h"
#include "3DS2VXL FE.h"
#include "3DS2VXL FEDlg.h"

BEGIN_MESSAGE_MAP(CMy3DS2VXLFEApp, CWinApp)
	//{{AFX_MSG_MAP(CMy3DS2VXLFEApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CMy3DS2VXLFEApp theApp;

BOOL CMy3DS2VXLFEApp::InitInstance()
{
	CMy3DS2VXLFEDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return false;
}
