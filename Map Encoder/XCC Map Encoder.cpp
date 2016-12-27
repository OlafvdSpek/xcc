#include "stdafx.h"
#include "XCC Map Encoder.h"
#include "XCC Map EncoderDlg.h"

#include "xcc_dirs.h"

BEGIN_MESSAGE_MAP(CXCCMapEncoderApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCMapEncoderApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CXCCMapEncoderApp::CXCCMapEncoderApp()
{
}

CXCCMapEncoderApp theApp;

BOOL CXCCMapEncoderApp::InitInstance()
{
	xcc_dirs::load_from_registry();
	CXCCMapEncoderDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return false;
}
