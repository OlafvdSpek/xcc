#include "stdafx.h"
#include "XCC Map Decoder.h"
#include "XCC Map DecoderDlg.h"

#include "xcc_dirs.h"

BEGIN_MESSAGE_MAP(CXCCMapDecoderApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCMapDecoderApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CXCCMapDecoderApp::CXCCMapDecoderApp()
{
}

CXCCMapDecoderApp theApp;

BOOL CXCCMapDecoderApp::InitInstance()
{
	xcc_dirs::load_from_registry();
	CXCCMapDecoderDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return false;
}
