// SelectPaletDlg.cpp : implementation file
//

#include "stdafx.h"
#include "xcc mixer.h"
#include "MainFrm.h"
#include "SelectPaletDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectPaletDlg dialog


CSelectPaletDlg::CSelectPaletDlg(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(CSelectPaletDlg::IDD, pParent, "select_palet_dlg")
{
	//{{AFX_DATA_INIT(CSelectPaletDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_current_palet = -1;
}


void CSelectPaletDlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectPaletDlg)
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_TREE, m_tree);
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectPaletDlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(CSelectPaletDlg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectPaletDlg message handlers

void CSelectPaletDlg::set(CMainFrame* main_frame, t_pal_map_list pal_map_list, t_pal_list pal_list)
{
	m_main_frame = main_frame; 
	m_pal_map_list  = pal_map_list;
	m_pal_list = pal_list;
}

BOOL CSelectPaletDlg::OnInitDialog() 
{
	ETSLayoutDialog::OnInitDialog();
	ListView_SetExtendedListViewStyle(m_list.m_hWnd, ListView_GetExtendedListViewStyle(m_list.m_hWnd) | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "Name");
	m_list.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL, GREEDY)
			<< item(IDC_TREE, GREEDY)
			<< item(IDC_LIST, GREEDY)
			)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< itemGrowing(HORIZONTAL)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			);
	UpdateLayout();
	m_list.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	insert_tree_entry(-1, TVI_ROOT);
	return true;
}

void CSelectPaletDlg::insert_tree_entry(int parent_id, HTREEITEM parent_item)
{
	CTreeCtrl& tc = m_tree;
	typedef t_pal_map_list t_map;
	typedef multimap<string, int> t_sort_map;
	const t_map& map = m_pal_map_list;
	t_sort_map sort_map;
	{
		for (t_map::const_iterator i = map.begin(); i != map.end(); i++)
		{
			if (i->second.parent == parent_id)
				sort_map.insert(t_sort_map::value_type(i->second.name, i->first));
		}
	}
	for (t_sort_map::const_iterator j = sort_map.begin(); j != sort_map.end(); j++)
	{
		t_map::const_iterator i = map.find(j->second);
		HTREEITEM h = tc.InsertItem(i->second.name.c_str(), parent_item);
		tc.SetItemData(h, i->first);
		insert_tree_entry(i->first, h);
		if (m_current_palet != -1 && m_pal_list.find(m_current_palet)->second.parent == i->first)
			tc.SelectItem(h);
	}
}

void CSelectPaletDlg::update_list(int parent_id, int current_palet)
{
	CListCtrl& lc = m_list;
	lc.DeleteAllItems();
	typedef t_pal_list t_map;
	const t_map& map = m_pal_list;
	for (t_map::const_iterator i = map.begin(); i != map.end(); i++)
	{
		if (i->second.parent != parent_id)
			continue;
		string name = i->second.name;
		{	
			int i = name.rfind(' ');
			if (i != string::npos)
				name = name.substr(i + 1);
		}
		int index = lc.InsertItem(lc.GetItemCount(), name.c_str());
		lc.SetItemData(index, i->first);
		if (current_palet == i->first)
			lc.SetItemState(index, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	}
	check_selection();
}

void CSelectPaletDlg::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	if (~pNMTreeView->itemOld.state & TVIS_SELECTED && pNMTreeView->itemNew.state & TVIS_SELECTED)
		update_list(pNMTreeView->itemNew.lParam, m_current_palet);
	*pResult = 0;
}

void CSelectPaletDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CListCtrl& lc = m_list;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_current_palet = pNMListView->uNewState & LVIS_FOCUSED ? lc.GetItemData(pNMListView->iItem) : -1;
	if (m_current_palet != -1)
		m_main_frame->set_palet(m_current_palet);
	check_selection();
	*pResult = 0;
}

void CSelectPaletDlg::check_selection()
{
	m_ok.EnableWindow(m_current_palet != -1);
}

void CSelectPaletDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_current_palet != -1)
		EndDialog(IDOK);	
	*pResult = 0;
}

void CSelectPaletDlg::OnSize(UINT nType, int cx, int cy) 
{
	ETSLayoutDialog::OnSize(nType, cx, cy);
	if (m_list.GetSafeHwnd())
		m_list.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
}
