// XCC Mod CreatorView.cpp : implementation of the CXCCModCreatorView class
//

#include "stdafx.h"
#include "XCC Mod Creator.h"

#include "XCC Mod CreatorDoc.h"
#include "XCC Mod CreatorView.h"
#include "options_dlg.h"
#include "resource.h"

#include "fname.h"
#include "string_conversion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCModCreatorView

IMPLEMENT_DYNCREATE(CXCCModCreatorView, CListView)

BEGIN_MESSAGE_MAP(CXCCModCreatorView, CListView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CXCCModCreatorView)
	ON_WM_DROPFILES()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	ON_COMMAND(ID_EDIT_INSERT, OnEditInsert)
	ON_UPDATE_COMMAND_UI(ID_EDIT_INSERT, OnUpdateEditInsert)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_COMMAND(ID_POPUP_OPEN, OnPopupOpen)
	ON_UPDATE_COMMAND_UI(ID_POPUP_OPEN, OnUpdatePopupOpen)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_COMMAND(ID_POPUP_EXPLORE, OnPopupExplore)
	ON_UPDATE_COMMAND_UI(ID_POPUP_EXPLORE, OnUpdatePopupExplore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCModCreatorView construction/destruction

CXCCModCreatorView::CXCCModCreatorView()
{
	m_buffer_w = 0;
	m_category = Cxcc_mod::ct_unknown;
}

CXCCModCreatorView::~CXCCModCreatorView()
{
}

BOOL CXCCModCreatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CXCCModCreatorView drawing

void CXCCModCreatorView::OnDraw(CDC* pDC)
{
	CXCCModCreatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

static int c_colums = 3;

void CXCCModCreatorView::OnInitialUpdate()
{
	char* column_label[] = {"Name", "Size", "Type"};
	int column_alignment[] = {LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_LEFT};

	CListCtrl& lc = GetListCtrl();
	ListView_SetExtendedListViewStyleEx(lc.m_hWnd, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (int i = 0; i < c_colums; i++)
		lc.InsertColumn(i, column_label[i], column_alignment[i], -1, i);

	autosize_colums();
	CListView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CXCCModCreatorView diagnostics

#ifdef _DEBUG
void CXCCModCreatorView::AssertValid() const
{
	CListView::AssertValid();
}

void CXCCModCreatorView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CXCCModCreatorDoc* CXCCModCreatorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXCCModCreatorDoc)));
	return (CXCCModCreatorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXCCModCreatorView message handlers
void CXCCModCreatorView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
}

void CXCCModCreatorView::OnDropFiles(HDROP hDropInfo) 
{
	int c_files = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	char fname[MAX_PATH];
	for (int i = 0; i < c_files; i++)
	{
		DragQueryFile(hDropInfo, i, fname, MAX_PATH);
		insert(to_lower(fname));
	}
	DragFinish(hDropInfo);
}

int CXCCModCreatorView::get_free_id() const
{
	return m_map.empty() ? 0 : m_map.rbegin()->first + 1;
}

CXCCModCreatorView::t_map_entry CXCCModCreatorView::create_map_entry(string fname)
{
	t_map_entry e;
	e.fname = fname;
	e.ft = ft_unknown;
	e.size = -1;
	Ccc_file f(false);
	if (!f.open(fname))
	{
		e.ft = f.get_file_type();
		e.size = f.get_size();
		f.close();
	}
	return e;
}

int CXCCModCreatorView::insert(string fname)
{
	Cxcc_mod::t_category_type category = m_category;
	t_map_entry e = create_map_entry(fname);
	switch (e.ft)
	{
	case ft_hva:
		category = Cxcc_mod::ct_hva;
		break;
	case ft_mix:
		category = Cxcc_mod::ct_mix;
		break;
	case ft_vxl:
		category = Cxcc_mod::ct_vxl;
		break;
	}
	CListCtrl& lc = GetListCtrl();
	if (category == m_category && GetDocument()->contains(m_category, fname))
	{
		LVFINDINFO lvf;
		lvf.flags = LVFI_STRING;
		lvf.psz = fname.c_str();
		lc.DeleteItem(lc.FindItem(&lvf, -1));
	}
	int error = GetDocument()->insert(category, fname);
	if (category == m_category && !error)
	{
		int count = lc.GetItemCount();
		int index = lc.InsertItem(count, LPSTR_TEXTCALLBACK);
		int id = get_free_id();
		m_map[id] = e;
		lc.SetItemData(index, id);
		if (!count)
			autosize_colums();
	}
	return error;
}

void CXCCModCreatorView::sync()
{
	SetRedraw(false);
	CListCtrl& lc = GetListCtrl();
	lc.DeleteAllItems();
	m_map.clear();
	Cxcc_mod::t_category_file_list list = GetDocument()->category_file_list(m_category);
	for (Cxcc_mod::t_category_file_list::const_iterator i = list.begin(); i != list.end(); i++)
	{
		int index = lc.InsertItem(lc.GetItemCount(), LPSTR_TEXTCALLBACK);
		int id = get_free_id();
		m_map[id] = create_map_entry(*i);
		lc.SetItemData(index, id);
	}
	if (lc.GetItemCount())
		autosize_colums();
	sort_list(0, false);
	SetRedraw(true);
	Invalidate();
}

int CXCCModCreatorView::remove(string fname)
{
	CListCtrl& lc = GetListCtrl();
	if (GetDocument()->contains(m_category, fname))
	{
		GetDocument()->remove(m_category, fname);
		LVFINDINFO lvf;
		lvf.flags = LVFI_STRING;
		lvf.psz = fname.c_str();
		lc.DeleteItem(lc.FindItem(&lvf, -1));
		return 0;
	}
	return 1;
}

void CXCCModCreatorView::autosize_colums()
{
	CListCtrl& lc = GetListCtrl();
	for (int i = 0; i < c_colums; i++)
		lc.SetColumnWidth(i, LVSCW_AUTOSIZE);
}

void CXCCModCreatorView::set_category(Cxcc_mod::t_category_type category)
{
	CListCtrl& lc = GetListCtrl();
	m_category = category;
	sync();
	DragAcceptFiles(category != Cxcc_mod::ct_unknown);
}

void CXCCModCreatorView::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	CListCtrl& lc = GetListCtrl();
	int id = lc.GetItemData(pDispInfo->item.iItem);
	m_buffer[m_buffer_w].erase();
	Ccc_file f(false);
	const t_map_entry& e = m_map.find(id)->second;
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		m_buffer[m_buffer_w] = e.fname;
		break;
	case 1:
		if (e.size != -1)
			m_buffer[m_buffer_w] = n(e.size);
		break;
	case 2:
		if (e.size != -1)
			m_buffer[m_buffer_w] = ft_name[e.ft];
		break;
	}	
	pDispInfo->item.pszText = const_cast<char*>(m_buffer[m_buffer_w].c_str());
	m_buffer_w--;
	if (m_buffer_w < 0)
		m_buffer_w += 4;
	*pResult = 0;
}

void CXCCModCreatorView::OnEditInsert() 
{
	const char* all_filter = "All files (*.*)|*.*|";
	CFileDialog dlg(true, NULL, 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, all_filter, this);
	if (IDOK == dlg.DoModal())
		insert(static_cast<string>(dlg.GetPathName()));
}

void CXCCModCreatorView::OnUpdateEditInsert(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_category != Cxcc_mod::ct_unknown);
}

void CXCCModCreatorView::OnEditDelete() 
{
	CListCtrl& lc = GetListCtrl();
	while (1)
	{
		int index = lc.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if (index == -1)
			break;
		remove(m_map.find(lc.GetItemData(index))->second.fname);
	}
}

void CXCCModCreatorView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	CListCtrl& lc = GetListCtrl();
	pCmdUI->Enable(lc.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED) != -1);
}

void CXCCModCreatorView::OnContextMenu(CWnd*, CPoint point)
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
		VERIFY(menu.LoadMenu(CG_IDR_POPUP));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CXCCModCreatorView::OnPopupOpen() 
{
	CListCtrl& lc = GetListCtrl();
	int index = lc.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	while (index != -1)
	{		
		ShellExecute(m_hWnd, "open", m_map.find(lc.GetItemData(index))->second.fname.c_str(), NULL, NULL, SW_SHOW);
		index = lc.GetNextItem(index, LVNI_ALL | LVNI_SELECTED);
	}
}

void CXCCModCreatorView::OnUpdatePopupOpen(CCmdUI* pCmdUI) 
{
	CListCtrl& lc = GetListCtrl();
	pCmdUI->Enable(lc.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED) != -1);
}


void CXCCModCreatorView::OnPopupExplore() 
{
	CListCtrl& lc = GetListCtrl();
	int index = lc.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
	string dir = Cfname(m_map.find(lc.GetItemData(index))->second.fname).get_path();;
	dir.erase(dir.length() - 1);
	ShellExecute(m_hWnd, "open", dir.c_str(), NULL, NULL, SW_SHOW);	
}

void CXCCModCreatorView::OnUpdatePopupExplore(CCmdUI* pCmdUI) 
{
	CListCtrl& lc = GetListCtrl();
	pCmdUI->Enable(lc.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED) != -1);
}

void CXCCModCreatorView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int column = pNMListView->iSubItem;
	sort_list(column, column == m_sort_column ? !m_sort_reverse : false);
	*pResult = 0;
}

static int compare_int(unsigned int a, unsigned int b)
{
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}

static int compare_string(string a, string b)
{
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}

int CXCCModCreatorView::compare(int id_a, int id_b) const
{
	if (m_sort_reverse)
		swap(id_a, id_b);
	const t_map_entry& a = m_map.find(id_a)->second;
	const t_map_entry& b = m_map.find(id_b)->second;
	switch (m_sort_column)
	{
	case 0:
		return compare_string(a.fname, b.fname);
	case 1:
		return compare_int(a.size, b.size);
	case 2:
		return compare_int(a.ft, b.ft);
	default:
		return 0;
	}
}

static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return reinterpret_cast<CXCCModCreatorView*>(lParamSort)->compare(lParam1, lParam2);
}

void CXCCModCreatorView::sort_list(int i, bool reverse)
{
	CListCtrl& lc = GetListCtrl();
	m_sort_column = i;
	m_sort_reverse = reverse;
	lc.SortItems(Compare, reinterpret_cast<dword>(this));
}

void CXCCModCreatorView::export() 
{
	const char* xmlf_filter = "XMLF files (*.xmlf)|*.xmlf|";
	CFileDialog file_dlg(false, "xmlf", NULL, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, xmlf_filter, NULL);
	if (IDOK == file_dlg.DoModal())
	{
		CWaitCursor wait;
		GetDocument()->export(static_cast<string>(file_dlg.GetPathName()));
	}
}

void CXCCModCreatorView::select_all()
{
	SetFocus();
	CListCtrl& lc = GetListCtrl();
	for (int index = 0; index < lc.GetItemCount(); index++)
	{
		lc.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);
	}
}

void CXCCModCreatorView::invert_selection()
{
	SetFocus();
	CListCtrl& lc = GetListCtrl();
	for (int index = 0; index < lc.GetItemCount(); index++)
	{
		lc.SetItemState(index, ~lc.GetItemState(index, LVIS_SELECTED), LVIS_SELECTED);
	}
}

void CXCCModCreatorView::options()
{
	Coptions_dlg dlg;
	dlg.set(GetDocument()->options());
	if (IDOK == dlg.DoModal())
	{
		GetDocument()->options(dlg.get());
	}
}

void CXCCModCreatorView::launch()
{
	CWaitCursor wait;
	GetDocument()->launch();
}

void CXCCModCreatorView::clear_game_dir()
{
	GetDocument()->clear_game_dir();
}
