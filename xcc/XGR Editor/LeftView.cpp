// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "XGR Editor.h"

#include "ChildFrm.h"
#include "LeftView.h"
#include "XGR EditorDoc.h"
#include "XGR EditorView.h"

#include "string_conversion.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_COMMAND(ID_POPUP_DELETE, OnPopupDelete)
	ON_UPDATE_COMMAND_UI(ID_POPUP_DELETE, OnUpdatePopupDelete)
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

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	CTreeCtrl& tc = GetTreeCtrl();
	const CXGREditorDoc::t_map& map = GetDocument()->map();
	for (CXGREditorDoc::t_map::const_iterator i = map.begin(); i != map.end(); i++)
	{
		string name = i->first.c_str();
		HTREEITEM p = TVI_ROOT;
		int a = 0;
		int b;
		while ((b = name.find('\\', a)) != string::npos)
		{
			t_map::const_iterator i = m_map.find(name.substr(0, b));
			p = i == m_map.end() ? m_map[name.substr(0, b)] = tc.InsertItem(name.substr(a, b - a).c_str(), p) : i->second;
			a = b + 1;
		}
		m_reverse_map[m_map[name] = tc.InsertItem(name.substr(a).c_str(), p)] = name;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	if (~pNMTreeView->itemOld.state & TVIS_SELECTED && pNMTreeView->itemNew.state & TVIS_SELECTED)
	{
		t_reverse_map::const_iterator i = m_reverse_map.find(pNMTreeView->itemNew.hItem);
		if (i == m_reverse_map.end())
			GetRightPane()->close();
		else
		{
			string name = m_reverse_map.find(pNMTreeView->itemNew.hItem)->second;
			GetRightPane()->open(GetDocument()->map().find(name)->second);
		}
	}
	else
		GetRightPane()->close();
	*pResult = 0;
}

CXGREditorView* CLeftView::GetRightPane()
{
	return reinterpret_cast<CChildFrame*>(GetParent()->GetParent())->GetRightPane();
}

void CLeftView::OnContextMenu(CWnd*, CPoint point)
{
	{
		if (point.x == -1 && point.y == -1)
		{
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_LEFT_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CLeftView::OnPopupDelete() 
{
	CTreeCtrl& tc = GetTreeCtrl();
	t_reverse_map::iterator i = m_reverse_map.find(tc.GetSelectedItem());
	GetDocument()->erase(i->second);
	tc.DeleteItem(i->first);
	m_map.erase(i->second);
	m_reverse_map.erase(i);
}

void CLeftView::OnUpdatePopupDelete(CCmdUI* pCmdUI) 
{
	CTreeCtrl& tc = GetTreeCtrl();
	pCmdUI->Enable(m_reverse_map.find(tc.GetSelectedItem()) != m_reverse_map.end());
}
