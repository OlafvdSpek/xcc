#include "stdafx.h"

#include "ChildFrm.h"
#include "LeftView.h"
#include "XCC TMP EditorView.h"
#include "resource.h"

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_EDIT_INVERT_SELECTION, OnEditInvertSelection)
	ON_COMMAND(ID_PALET_SNOW, OnPaletSnow)
	ON_COMMAND(ID_PALET_TEMPERATE, OnPaletTemperate)
	ON_COMMAND(ID_PALET_URBAN, OnPaletUrban)
	ON_COMMAND(ID_PALET_LOAD, OnPaletLoad)
	ON_COMMAND(ID_VIEW_TRUE_HEIGHT, OnViewTrueHeight)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TRUE_HEIGHT, OnUpdateViewTrueHeight)
	ON_COMMAND(ID_PALET_DESERT, OnPaletDesert)
	ON_COMMAND(ID_PALET_LUNAR, OnPaletLunar)
	ON_COMMAND(ID_PALET_URBAN2, OnPaletUrban2)
	ON_UPDATE_COMMAND_UI(ID_PALET_DESERT, OnUpdatePaletDesert)
	ON_UPDATE_COMMAND_UI(ID_PALET_LUNAR, OnUpdatePaletLunar)
	ON_UPDATE_COMMAND_UI(ID_PALET_SNOW, OnUpdatePaletSnow)
	ON_UPDATE_COMMAND_UI(ID_PALET_TEMPERATE, OnUpdatePaletTemperate)
	ON_UPDATE_COMMAND_UI(ID_PALET_URBAN, OnUpdatePaletUrban)
	ON_UPDATE_COMMAND_UI(ID_PALET_URBAN2, OnUpdatePaletUrban2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

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
	CMDIChildWnd::ActivateFrame(SW_SHOWMAXIMIZED);
}

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

void CChildFrame::OnPaletDesert() 
{
	GetLeftPane()->GetDocument()->load_desert_palet(false);
}

void CChildFrame::OnUpdatePaletDesert(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetLeftPane()->GetDocument()->load_desert_palet(true));
}

void CChildFrame::OnPaletLunar() 
{
	GetLeftPane()->GetDocument()->load_lunar_palet(false);	
}

void CChildFrame::OnUpdatePaletLunar(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetLeftPane()->GetDocument()->load_lunar_palet(true));	
}

void CChildFrame::OnPaletSnow() 
{
	GetLeftPane()->GetDocument()->load_snow_palet(false);
}

void CChildFrame::OnUpdatePaletSnow(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetLeftPane()->GetDocument()->load_snow_palet(true));
}

void CChildFrame::OnPaletTemperate() 
{
	GetLeftPane()->GetDocument()->load_temperate_palet(false);
}

void CChildFrame::OnUpdatePaletTemperate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetLeftPane()->GetDocument()->load_temperate_palet(true));	
}

void CChildFrame::OnUpdatePaletUrban(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetLeftPane()->GetDocument()->load_urban_palet(true));	
}

void CChildFrame::OnPaletUrban() 
{
	GetLeftPane()->GetDocument()->load_urban_palet(false);
}

void CChildFrame::OnPaletUrban2() 
{
	GetLeftPane()->GetDocument()->load_urban2_palet(false);	
}

void CChildFrame::OnUpdatePaletUrban2(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetLeftPane()->GetDocument()->load_urban2_palet(true));	
}

void CChildFrame::OnPaletLoad() 
{
	const char* pal_filter = "PAL files (*.pal)|*.pal|";

	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, pal_filter, this);
	if (IDOK == dlg.DoModal())
		GetLeftPane()->GetDocument()->load_palet(static_cast<string>(dlg.GetPathName()), false);
}

void CChildFrame::OnViewTrueHeight() 
{
	GetRightPane()->view_true_height(!GetRightPane()->view_true_height());
}

void CChildFrame::OnUpdateViewTrueHeight(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetRightPane()->view_true_height());
}
