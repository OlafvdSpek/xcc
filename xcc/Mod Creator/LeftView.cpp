// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"

#include "LeftView.h"

#include "xcc_mod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

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
