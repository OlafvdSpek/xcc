// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "XCC TMP Editor.h"

#include "ChildFrm.h"
#include "LeftView.h"
#include "XCC TMP EditorView.h"

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
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_EDIT_INVERT_SELECTION, OnEditInvertSelection)
	ON_COMMAND(ID_PALET_SNOW, OnPaletSnow)
	ON_COMMAND(ID_PALET_TEMPERATE, OnPaletTemperate)
	ON_COMMAND(ID_PALET_URBAN, OnPaletUrban)
	ON_COMMAND(ID_PALET_LOAD, OnPaletLoad)
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
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(300, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CXCCTMPEditorView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	GetLeftPane()->set_other_pane(GetRightPane());
	return TRUE;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	return TRUE;
}

void CChildFrame::ActivateFrame(int nCmdShow)
{
	nCmdShow = SW_SHOWMAXIMIZED;
	CMDIChildWnd::ActivateFrame(nCmdShow);
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

CLeftView* CChildFrame::GetLeftPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	return pView;
}

CXCCTMPEditorView* CChildFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CXCCTMPEditorView* pView = DYNAMIC_DOWNCAST(CXCCTMPEditorView, pWnd);
	return pView;
}

void CChildFrame::OnEditSelectAll() 
{
	GetLeftPane()->select_all();
}

void CChildFrame::OnEditInvertSelection() 
{
	GetLeftPane()->invert_selection();
}

void CChildFrame::OnPaletSnow() 
{
	GetLeftPane()->GetDocument()->load_snow_palet();
}

void CChildFrame::OnPaletTemperate() 
{
	GetLeftPane()->GetDocument()->load_temperate_palet();
}

void CChildFrame::OnPaletUrban() 
{
	GetLeftPane()->GetDocument()->load_urban_palet();
}

void CChildFrame::OnPaletLoad() 
{
	const char* pal_filter = "PAL files (*.pal)|*.pal|";

	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, pal_filter, this);
	if (IDOK == dlg.DoModal())
		GetLeftPane()->GetDocument()->load_palet(static_cast<string>(dlg.GetPathName()));
}
