// INIChildFrm.cpp : implementation of the CINIChildFrame class
//

#include "stdafx.h"
#include "XCC INI Editor.h"

#include "inileftview.h"
#include "INIChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CINIChildFrame

IMPLEMENT_DYNCREATE(CINIChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CINIChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CINIChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CINIChildFrame construction/destruction

CINIChildFrame::CINIChildFrame()
{
}

CINIChildFrame::~CINIChildFrame()
{
}

BOOL CINIChildFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	m_wndSplitter1.CreateStatic(this, 1, 2);
	m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CINILeftView), CSize(200,0), pContext);
	m_wndSplitter1.CreateView(0, 1, RUNTIME_CLASS(CINIView), CSize(200,0), pContext);
	// m_wndSplitter2.Create(&m_wndSplitter1, 2, 2, CSize(10, 10), pContext, WS_CHILD | WS_VISIBLE |WS_HSCROLL | WS_VSCROLL | SPLS_DYNAMIC_SPLIT, m_wndSplitter1.IdFromRowCol(0, 1));
	return true;
	/*
	return m_wndSplitter2.Create( this,
		2, 2,
		CSize( 10, 10 ),
		pContext );
	*/
}

BOOL CINIChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	return TRUE;
}

void CINIChildFrame::ActivateFrame(int nCmdShow)
{
	nCmdShow = SW_SHOWMAXIMIZED;
	CMDIChildWnd::ActivateFrame(nCmdShow);
}


/////////////////////////////////////////////////////////////////////////////
// CINIChildFrame diagnostics

#ifdef _DEBUG
void CINIChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CINIChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CINIChildFrame message handlers

CINILeftView* CINIChildFrame::GetLeftPane()
{
	return reinterpret_cast<CINILeftView*>(m_wndSplitter1.GetPane(0, 0));;
}

CINIView* CINIChildFrame::GetRightPane()
{
	return reinterpret_cast<CINIView*>(m_wndSplitter1.GetPane(0, 1));;
}

void CINIChildFrame::SetActivePane(int row, int col)
{
	m_wndSplitter1.SetActivePane(row, col);
}