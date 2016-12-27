#include "stdafx.h"
#include "XCC Game Spy Player.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "XCC Game Spy PlayerDoc.h"
#include "XCC Game Spy PlayerView.h"

#include "dlg_open.h"
#include "xcc_dirs.h"

BEGIN_MESSAGE_MAP(CXCCGameSpyPlayerApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCGameSpyPlayerApp)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CXCCGameSpyPlayerApp theApp;

BOOL CXCCGameSpyPlayerApp::InitInstance()
{
	SetRegistryKey("XCC");
	LoadStdProfileSettings(16);
	xcc_dirs::load_from_registry();
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_XCCGAMTYPE,
		RUNTIME_CLASS(CXCCGameSpyPlayerDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CXCCGameSpyPlayerView));
	AddDocTemplate(pDocTemplate);
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	m_pMainWnd->DragAcceptFiles();
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew) 
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();
	return TRUE;
}

void CXCCGameSpyPlayerApp::OnFileOpen() 
{
	Cdlg_open dlg;
	Cxif_key key;
	if (!key.load_key(Cvirtual_binary(data_fname())))
		dlg.import_cache(key);
	if (IDOK == dlg.DoModal())
		OpenDocumentFile(dlg.fname().c_str());
	dlg.export_cache().vdata().save(data_fname());
}

string CXCCGameSpyPlayerApp::data_fname()
{
	return xcc_dirs::get_data_dir() + "xgsp_data.xif";
}
