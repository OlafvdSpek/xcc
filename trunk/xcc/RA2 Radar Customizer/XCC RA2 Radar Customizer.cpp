#include "stdafx.h"
#include "XCC RA2 Radar Customizer.h"
#include "XCC RA2 Radar CustomizerDlg.h"

#include "mix_cache.h"
#include "xcc_dirs.h"

BEGIN_MESSAGE_MAP(CXCCRA2RadarCustomizerApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCRA2RadarCustomizerApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CXCCRA2RadarCustomizerApp::CXCCRA2RadarCustomizerApp()
{
}

CXCCRA2RadarCustomizerApp theApp;

BOOL CXCCRA2RadarCustomizerApp::InitInstance()
{
	xcc_dirs::load_from_registry();
	mix_cache::load();
	CXCCRA2RadarCustomizerDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return false;
}
