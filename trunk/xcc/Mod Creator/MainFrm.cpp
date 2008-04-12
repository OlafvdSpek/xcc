// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"

#include "MainFrm.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_COMMAND_RANGE(ID_LAUNCH_XAP, ID_LAUNCH_RAGE, OnLaunchApp)
	ON_UPDATE_COMMAND_UI_RANGE(ID_LAUNCH_XAP, ID_LAUNCH_RAGE, OnUpdateLaunchApp)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
};

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// cs.style |= WS_MAXIMIZE;
	return TRUE;
}

void CMainFrame::OnLaunchApp(UINT ID)
{
	t_app app = static_cast<t_app>(ID - ID_LAUNCH_XAP);
	ShellExecute(m_hWnd, NULL, m_apps.get_exe(app).c_str(), NULL, NULL, SW_SHOW);
}

void CMainFrame::OnUpdateLaunchApp(CCmdUI* pCmdUI)
{
	t_app app = static_cast<t_app>(pCmdUI->m_nID - ID_LAUNCH_XAP);
	pCmdUI->Enable(m_apps.is_available(app));
}

