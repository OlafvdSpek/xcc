// INIMainFrm.cpp : implementation of the CINIMainFrame class
//

#include "stdafx.h"
#include "XCC INI Editor.h"

#include "INIMainFrm.h"

#include "editcmd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CINIMainFrame

IMPLEMENT_DYNAMIC(CINIMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CINIMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CINIMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_EDIT_INDICATOR_POSITION, OnUpdateIndicatorPosition)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_EDIT_INDICATOR_POSITION,	 
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CINIMainFrame construction/destruction

CINIMainFrame::CINIMainFrame()
{
}

CINIMainFrame::~CINIMainFrame()
{
}

int CINIMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	return 0;
}

BOOL CINIMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CINIMainFrame diagnostics

#ifdef _DEBUG
void CINIMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CINIMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CINIMainFrame message handlers

void CINIMainFrame::OnUpdateIndicatorPosition(CCmdUI* pCmdUI)
{
	pCmdUI->SetText("");
}
