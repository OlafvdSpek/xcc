// XCC RA2 Radar Customizer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XCC RA2 Radar Customizer.h"
#include "XCC RA2 Radar CustomizerDlg.h"

#include "mix_cache.h"
#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCRA2RadarCustomizerApp

BEGIN_MESSAGE_MAP(CXCCRA2RadarCustomizerApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCRA2RadarCustomizerApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCRA2RadarCustomizerApp construction

CXCCRA2RadarCustomizerApp::CXCCRA2RadarCustomizerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXCCRA2RadarCustomizerApp object

CXCCRA2RadarCustomizerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXCCRA2RadarCustomizerApp initialization

BOOL CXCCRA2RadarCustomizerApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	xcc_dirs::load_from_registry();
	mix_cache::load();

	CXCCRA2RadarCustomizerDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
