// XIFTree.cpp : implementation file
//

#include "stdafx.h"
#include <windowsx.h>
#include "resource.h"
#include "XIF Editor.h"
#include "XIFTree.h"
#include "string_conversion.h"
#include "xif_tools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXIFTree

IMPLEMENT_DYNCREATE(CXIFTree, CTreeView)

CXIFTree::CXIFTree()
{
}

CXIFTree::~CXIFTree()
{
}


BEGIN_MESSAGE_MAP(CXIFTree, CTreeView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CXIFTree)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_COMMAND(ID_POPUP_REMOVE, OnPopupRemove)
	ON_UPDATE_COMMAND_UI(ID_POPUP_REMOVE, OnUpdatePopupRemove)
	ON_COMMAND(ID_POPUP_INSERT, OnPopupInsert)
	ON_UPDATE_COMMAND_UI(ID_POPUP_INSERT, OnUpdatePopupInsert)
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXIFTree message handlers

void CXIFTree::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	insert_key(-1, GetDocument()->get_top(), TVI_ROOT);
}

Cxif_key& CXIFTree::get_key(HTREEITEM e)
{
	int id = GetTreeCtrl().GetItemData(e);
	HTREEITEM parent = GetTreeCtrl().GetParentItem(e);
	if (parent)
		return get_key(parent).m_keys.find(id)->second;
	else
		return GetDocument()->get_top();
}

void CXIFTree::insert_key(int id, Cxif_key& key, HTREEITEM parent)
{
	HTREEITEM h = GetTreeCtrl().InsertItem(parent == TVI_ROOT ? "\\" : nh(8, id).c_str(), parent, TVI_LAST);
	GetTreeCtrl().SetItemData(h, id);
	for (t_xif_key_map::iterator k = key.m_keys.begin(); k != key.m_keys.end(); k++)
		insert_key(k->first, k->second, h);
}

BOOL CXIFTree::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= TVS_EDITLABELS | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS;
	return CTreeView::PreCreateWindow(cs);
}

void CXIFTree::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	m_list->open_key(&get_key(pNMTreeView->itemNew.hItem));
	*pResult = 0;
}

void CXIFTree::set_list(CXIFList* list)
{
	m_list = list;
}

void CXIFTree::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_XIFTREE));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

HTREEITEM CXIFTree::get_current_index()
{
	return GetTreeCtrl().GetNextItem(NULL, TVGN_CARET);
}

void CXIFTree::OnPopupInsert() 
{
	HTREEITEM e = get_current_index();
	Cxif_key& k = get_key(e);
	int id = 0;
	while (k.m_keys.find(id) != k.m_keys.end())
		id++;	
	insert_key(id, k.open_key_write(id), e);
}

void CXIFTree::OnUpdatePopupInsert(CCmdUI* pCmdUI) 
{
	HTREEITEM e = get_current_index();
	pCmdUI->Enable(static_cast<bool>(e));
}

void CXIFTree::OnPopupRemove() 
{
	HTREEITEM e = get_current_index();
	get_key(GetTreeCtrl().GetParentItem(e)).delete_key(GetTreeCtrl().GetItemData(e));
	GetTreeCtrl().DeleteItem(e);
}

void CXIFTree::OnUpdatePopupRemove(CCmdUI* pCmdUI) 
{
	HTREEITEM e = get_current_index();
	pCmdUI->Enable(e && GetTreeCtrl().GetParentItem(e));
}

void CXIFTree::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	*pResult = !GetTreeCtrl().GetParentItem(pTVDispInfo->item.hItem);
}

void CXIFTree::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	*pResult = false;
	const char* t = pTVDispInfo->item.pszText;
	if (t)
	{
		int id = str2id(t);
		if (id != -1)
		{
			CTreeCtrl& tc = GetTreeCtrl();
			HTREEITEM ph = tc.GetParentItem(pTVDispInfo->item.hItem);
			Cxif_key& pk = get_key(ph);
			if (pk.exists_key(id))
				return;
			Cxif_key k = get_key(pTVDispInfo->item.hItem);
			pk.delete_key(pTVDispInfo->item.lParam);
			pk.open_key_write(id) = k;
			tc.SetItemData(pTVDispInfo->item.hItem, id);
			*pResult = true;
		}
	}
}

void CXIFTree::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTreeCtrl& tc = GetTreeCtrl();
	
	DWORD dwPos = GetMessagePos();
	
	CPoint pt(GET_X_LPARAM(dwPos), GET_Y_LPARAM(dwPos));
	CPoint spt = pt;
	
	tc.ScreenToClient(&spt);
	
	UINT test;
	HTREEITEM h = tc.HitTest(spt, &test);
	
	if (h && test & TVHT_ONITEM)
	{
		tc.Select(h, TVGN_CARET);
		OnContextMenu(this, pt);
	}
	*pResult = 0;
}
