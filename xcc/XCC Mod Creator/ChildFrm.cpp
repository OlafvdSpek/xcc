// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "XCC Mod Creator.h"

#include "ChildFrm.h"
#include "LeftView.h"
#include "XCC Mod CreatorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_EDIT_INVERT_SELECTION, OnEditInvertSelection)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_COMMAND(ID_VIEW_OPTIONS, OnViewOptions)
	ON_COMMAND(ID_VIEW_LAUNCH, OnViewLaunch)
	ON_COMMAND(ID_MOD_CLEAR_GAME_DIRECTORY, OnModClearGameDirectory)
	ON_COMMAND(ID_MOD_ACTIVATE, OnModActivate)
	ON_COMMAND(ID_MOD_DEACTIVATE, OnModDeactivate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(100, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CXCCModCreatorView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	static_cast<CLeftView*>(m_wndSplitter.GetPane(0, 0))->set_other_pane(static_cast<CXCCModCreatorView*>(m_wndSplitter.GetPane(0, 1)));

	return TRUE;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
CXCCModCreatorView* CChildFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CXCCModCreatorView* pView = DYNAMIC_DOWNCAST(CXCCModCreatorView, pWnd);
	return pView;
}

void CChildFrame::OnFileExport() 
{
	GetRightPane()->export();
}

void CChildFrame::OnEditSelectAll() 
{
	GetRightPane()->select_all();
}

void CChildFrame::OnEditInvertSelection() 
{
	GetRightPane()->invert_selection();
}

void CChildFrame::OnViewRefresh() 
{
	GetRightPane()->sync();
}

void CChildFrame::OnViewOptions() 
{
	GetRightPane()->options();
}

void CChildFrame::OnModActivate() 
{
	CWaitCursor wait;
	GetRightPane()->GetDocument()->activate();
}

void CChildFrame::OnViewLaunch() 
{
	GetRightPane()->launch();
}

void CChildFrame::OnModDeactivate() 
{
	CWaitCursor wait;
	GetRightPane()->GetDocument()->deactivate();
}

void CChildFrame::OnModClearGameDirectory() 
{
	GetRightPane()->clear_game_dir();
}

