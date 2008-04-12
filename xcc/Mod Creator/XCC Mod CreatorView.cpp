#include "stdafx.h"

#include <boost/algorithm/string.hpp>
#include "XCC Mod CreatorDoc.h"
#include "XCC Mod CreatorView.h"
#include "options_dlg.h"
#include "properties_dlg.h"
#include "resource.h"

#include "fname.h"
#include "string_conversion.h"
#include "xcc_apps.h"

using namespace boost;

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
	ON_COMMAND(ID_POPUP_PROPERTIES, OnPopupProperties)
	ON_UPDATE_COMMAND_UI(ID_POPUP_PROPERTIES, OnUpdatePopupProperties)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

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

static int c_columns = 5;

void CXCCModCreatorView::OnInitialUpdate()
{
	const char* column_label[] = {"Name", "Size", "Type", "Mode", "Module"};
	int column_alignment[] = {LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT};

	CListCtrl& lc = GetListCtrl();
	lc.SetExtendedStyle(lc.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	for (int i = 0; i < c_columns; i++)
		lc.InsertColumn(i, column_label[i], column_alignment[i], -1, i);

	autosize_colums();
	CListView::OnInitialUpdate();
}

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
		insert(to_lower_copy(string(fname)));
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
	m_sort_column = -1;
	return error;
}

void CXCCModCreatorView::sync()
{
	CWaitCursor wait;
	SetRedraw(false);
	CListCtrl& lc = GetListCtrl();
	lc.DeleteAllItems();
	m_map.clear();
	Cxcc_mod::t_category_file_list list = GetDocument()->category_file_list(m_category);
	for (Cxcc_mod::t_category_file_list::const_iterator i = list.begin(); i != list.end(); i++)
	{
		int index = lc.InsertItem(lc.GetItemCount(), LPSTR_TEXTCALLBACK);
		int id = get_free_id();
		m_map[id] = create_map_entry(i->first);
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
	for (int i = 0; i < c_columns; i++)
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
	int id = pDispInfo->item.lParam;
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
	case 3:
		{
			int mode = GetDocument()->file_properties(m_category, e.fname).mode;
			if (mode != -1)
				m_buffer[m_buffer_w] = GetDocument()->mod().get_mode(mode);
		}
		break;
	case 4:
		{
			int module = GetDocument()->file_properties(m_category, e.fname).module;
			if (module != -1)
				m_buffer[m_buffer_w] = GetDocument()->mod().get_module(module);
		}
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
	int index = focus();
	string dir = Cfname(m_map.find(lc.GetItemData(index))->second.fname).get_path();
	if (!dir.empty())
	{
		dir.erase(dir.length() - 1);
		ShellExecute(m_hWnd, "open", dir.c_str(), NULL, NULL, SW_SHOW);
	}
}

void CXCCModCreatorView::OnUpdatePopupExplore(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(focus() != -1);
}

void CXCCModCreatorView::OnPopupProperties()
{
	CListCtrl& lc = GetListCtrl();
	int index = focus();
	string fname = m_map.find(lc.GetItemData(focus()))->second.fname;
	Cproperties_dlg dlg;
	dlg.mod(GetDocument()->mod());
	dlg.properties(GetDocument()->file_properties(m_category, fname));
	if (IDOK == dlg.DoModal())
	{
		Cxcc_mod::t_file_properties properties;
		properties.mode = GetDocument()->add_mode(dlg.mode());
		properties.module = GetDocument()->add_module(dlg.module());
		GetDocument()->file_properties(m_category, fname, properties);
	}
}

void CXCCModCreatorView::OnUpdatePopupProperties(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(focus() != -1);
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
	Cvirtual_binary exe;
	Cxcc_apps apps;
	string export_filter;
	const char* export_ext = "xmlf";
	Cfname fname = static_cast<string>(GetDocument()->GetPathName());
	if (apps.is_available(app_xml) && !exe.load(apps.get_exe(app_xml)))
	{
		export_filter += "BZ EXE files (*.exe)|*.exe|"
			"GZ EXE files (*.exe)|*.exe|"
			"EXE files (*.exe)|*.exe|";
		export_ext = "exe";
	}
	export_filter += "BZ XMLF files (*.xmlf)|*.xmlf|"
		"GZ XMLF files (*.xmlf)|*.xmlf|"
		"XMLF files (*.xmlf)|*.xmlf|";
	CFileDialog dlg(false, export_ext, NULL, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, export_filter.c_str(), NULL);
	if (IDOK == dlg.DoModal())
	{
		CWaitCursor wait;
		GetDocument()->export(static_cast<string>(dlg.GetPathName()), dlg.m_ofn.nFilterIndex < 4 ? exe : Cvirtual_binary(), dlg.m_ofn.nFilterIndex % 3);
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
	if (GetDocument()->launch())
		MessageBox("Error launching mod.", NULL, MB_ICONERROR);
}

void CXCCModCreatorView::clear_game_dir()
{
	GetDocument()->clear_game_dir();
}

int CXCCModCreatorView::focus() const
{
	return GetListCtrl().GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
}
