#include "stdafx.h"
#include "XCC MIX Editor.h"
#include "XCC MIX EditorDlg.h"
#include "id_log.h"
#include "mix_cache.h"
#include "xcc_dirs.h"

BEGIN_MESSAGE_MAP(CXCCMIXEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCMIXEditorApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CXCCMIXEditorApp theApp;

BOOL CXCCMIXEditorApp::InitInstance()
{
	AfxEnableControlContainer();
	SetRegistryKey("XCC");

	CXCCMIXEditorDlg dlg;
	m_pMainWnd = &dlg;

	Cmix_file::enable_ft_support();
	xcc_dirs::load_from_registry();
	mix_database::load();
	mix_cache::load();
	dlg.DoModal();
	mix_cache::save();
	return false;
}
