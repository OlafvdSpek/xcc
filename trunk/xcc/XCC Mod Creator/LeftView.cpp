// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "XCC Mod Creator.h"

#include "XCC Mod CreatorDoc.h"
#include "LeftView.h"

#include "xcc_mod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS;
	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CXCCModCreatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}


void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	CTreeCtrl& tc = GetTreeCtrl();
	for (int i = 0; i < Cxcc_mod::ct_unknown; i++)
	{
		HTREEITEM h = tc.InsertItem(Cxcc_mod::ct_name[i], TVI_ROOT, TVI_SORT);
		tc.SetItemData(h, i);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CXCCModCreatorDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXCCModCreatorDoc)));
	return (CXCCModCreatorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	if (~pNMTreeView->itemOld.state & TVIS_SELECTED && pNMTreeView->itemNew.state & TVIS_SELECTED)
		m_other_pane->set_category(static_cast<Cxcc_mod::t_category_type>(pNMTreeView->itemNew.lParam));	
	*pResult = 0;
}

void CLeftView::set_other_pane(CXCCModCreatorView* other_pane)
{
	m_other_pane = other_pane;
}
