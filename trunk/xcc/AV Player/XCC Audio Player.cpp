#include "stdafx.h"
#include "XCC Audio Player.h"
#include "XCC Audio PlayerDlg.h"
#include "mix_cache.h"

BEGIN_MESSAGE_MAP(CXCCAudioPlayerApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCAudioPlayerApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CXCCAudioPlayerApp theApp;

BOOL CXCCAudioPlayerApp::InitInstance()
{
	AfxEnableControlContainer();
	SetRegistryKey("XCC");
	CXCCAudioPlayerDlg dlg;
	m_pMainWnd = &dlg;
	Cmix_file::enable_ft_support();
	xcc_dirs::load_from_registry();
	mix_cache::load();
	dlg.DoModal();
	mix_cache::save();
	xcc_dirs::save_to_registry();
	return false;
}
