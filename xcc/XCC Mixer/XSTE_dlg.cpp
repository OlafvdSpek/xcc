// XSTE_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "xcc mixer.h"
#include "XSTE_dlg.h"
#include "XSTE_edit_dlg.h"

#include "mix_file.h"
#include "string_conversion.h"
#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXSTE_dlg dialog


CXSTE_dlg::CXSTE_dlg(t_game game, bool expansion, CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(CXSTE_dlg::IDD, pParent, "XSTE_dlg")
{
	//{{AFX_DATA_INIT(CXSTE_dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_buffer_w = 0;
	m_expansion = expansion;
	m_game = game;
}


void CXSTE_dlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXSTE_dlg)
	DDX_Control(pDX, IDC_CAT_LIST, m_cat_list);
	DDX_Control(pDX, IDC_INSERT, m_insert);
	DDX_Control(pDX, IDC_EDIT, m_edit);
	DDX_Control(pDX, IDC_DELETE, m_delete);
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXSTE_dlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(CXSTE_dlg)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST, OnEndlabeleditList)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST, OnGetdispinfoList)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST, OnColumnclickList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CAT_LIST, OnItemchangedCatList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXSTE_dlg message handlers

static int c_colums = 3;
static char* column_label[] = {"Name", "Value", "Extra value"};

BOOL CXSTE_dlg::OnInitDialog() 
{
	ETSLayoutDialog::OnInitDialog();
	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL, GREEDY)
			<< item(IDC_CAT_LIST, ABSOLUTE_HORZ)
			<< item(IDC_LIST, GREEDY)
			)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< itemGrowing(HORIZONTAL)
			<< item(IDC_INSERT, NORESIZE)
			<< item(IDC_EDIT, NORESIZE)
			<< item(IDC_DELETE, NORESIZE)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			);
	UpdateLayout();
	SetRedraw(false);
	ListView_SetExtendedListViewStyle(m_list.m_hWnd, ListView_GetExtendedListViewStyle(m_list.m_hWnd) | LVS_EX_FULLROWSELECT);
	LV_COLUMN lvc;
	lvc.mask = LVCF_TEXT | LVCF_SUBITEM;
	for (int i = 0; i < c_colums; i++)
	{
		lvc.iSubItem = i;
		lvc.pszText = column_label[i];
		m_list.InsertColumn(i, &lvc);
	}
	int error = m_f.open(xcc_dirs::get_dir(m_game) + xcc_dirs::get_csf_fname(m_game, m_expansion));
	if (error)
	{
		Cmix_file language;
		error = language.open(xcc_dirs::get_language_mix(m_game, m_expansion));
		if (!error)
		{
			error = m_f.open(xcc_dirs::get_csf_fname(m_game, m_expansion), language);
			language.close();
		}
	}
	if (!error)
	{
		create_cat_map();
		for (t_cat_map::const_iterator i = m_cat_map.begin(); i != m_cat_map.end(); i++)
			m_cat_list.SetItemData(m_cat_list.InsertItem(m_cat_list.GetItemCount(), i->second.c_str()), i->first);
		m_f.close();
	}	
	check_selection();
	sort_list(0, false);
	SetRedraw(true);
	Invalidate();
	return true;
}

static string get_cat(const string& name)
{
	int a = name.find(':');
	int b = name.find('_');
	if (a == string::npos)
	{
		if (b == string::npos)
			return "Other";
		return to_upper(name.substr(0, b));
	}
	if (b == string::npos)
		return to_upper(name.substr(0, a));
	return to_upper(name.substr(0, min(a, b)));
}

int CXSTE_dlg::get_cat_id(const string& name) const
{
	t_reverse_cat_map::const_iterator i = m_reverse_cat_map.find(get_cat(name));
	return (i == m_reverse_cat_map.end() ? m_reverse_cat_map.find("Other") : i)->second;
}

void CXSTE_dlg::create_cat_map()
{
	static int cat_id = 0;
	for (Ccsf_file::t_map::const_iterator i = m_f.get_map().begin(); i != m_f.get_map().end(); i++)
	{
		string cat = get_cat(i->first);
		if (m_reverse_cat_map.find(cat) == m_reverse_cat_map.end())
		{
			m_cat_map[cat_id] = cat;
			m_reverse_cat_map[cat] = cat_id++;
		}
		static int id = 0;
		t_map_entry& e = m_map[id++];
		e.i = i;
		e.cat_id = m_reverse_cat_map.find(cat)->second;
	}
	string cat = "Other";
	if (m_reverse_cat_map.find(cat) == m_reverse_cat_map.end())
	{
		m_cat_map[cat_id] = cat;
		m_reverse_cat_map[cat] = cat_id++;
	}
}

int CXSTE_dlg::insert(int id)
{
	int index = m_list.InsertItem(m_list.GetItemCount(), LPSTR_TEXTCALLBACK);
	m_list.SetItemData(index, id);
	return index;
}

int CXSTE_dlg::get_current_index()
{
	return m_list.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
}

void CXSTE_dlg::check_selection()
{
	int index = get_current_index();
	m_insert.EnableWindow(m_f.get_map().find("") == m_f.get_map().end());
	m_edit.EnableWindow(index != -1);
	m_delete.EnableWindow(index != -1);
}

void CXSTE_dlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// if (pNMListView->uNewState & LVIS_FOCUSED)
	check_selection();
	*pResult = 0;
}

int CXSTE_dlg::get_free_id()
{
	int id = 0;
	while (m_map.find(id) != m_map.end())
		id++;
	return id;
}

void CXSTE_dlg::set_map_entry(int id, const string& name)
{
	t_map_entry& e = m_map[id];
	e.i = m_f.get_map().find(name);
	e.cat_id = get_cat_id(name);
}

void CXSTE_dlg::OnInsert() 
{
	m_f.set_value("", wstring(), "");
	int id = get_free_id();
	set_map_entry(id, "");
	m_list.SetFocus();
	m_list.EditLabel(insert(id));
}

void CXSTE_dlg::OnEdit() 
{
	int index = get_current_index();
	CXSTE_edit_dlg dlg;
	string name = m_list.GetItemText(index, 0);
	Ccsf_file::t_map::const_iterator i = m_f.get_map().find(name);
	dlg.set(i->first, Ccsf_file::convert2string(i->second.value), i->second.extra_value);
	if (dlg.DoModal() == IDOK)
	{
		m_f.set_value(name, Ccsf_file::convert2wstring(dlg.get_value()), dlg.get_extra_value());
		m_list.Update(index);
	}
}

void CXSTE_dlg::OnDelete() 
{
	SetRedraw(false);
	while (1)
	{
		int index = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if (index == -1)
			break;
		m_f.erase_value(static_cast<string>(m_list.GetItemText(index, 0)));
		m_list.DeleteItem(index);
	}
	check_selection();
	SetRedraw(true);
	Invalidate();
}

void CXSTE_dlg::OnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	*pResult = false;
	const char* t = pDispInfo->item.pszText;
	if (t)
	{
		if (m_f.get_map().find(t) != m_f.get_map().end())
			return;
		int id = pDispInfo->item.lParam;
		t_map_entry& f = m_map[id++];
		string old_name = f.i->first;
		Ccsf_file::t_map_entry e = m_f.get_map().find(old_name)->second;
		m_f.erase_value(old_name);
		m_f.set_value(t, e.value, e.extra_value);
		f.i = m_f.get_map().find(t);
		f.cat_id = get_cat_id(t);
		if (old_name.empty())
			check_selection();
		*pResult = true;
	}	
}

void CXSTE_dlg::OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	int id = m_list.GetItemData(pDispInfo->item.iItem);
	const t_map_entry& e = m_map.find(id)->second;
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		m_buffer[m_buffer_w] = e.i->first;
		break;
	case 1:
		m_buffer[m_buffer_w] = m_f.get_converted_value(e.i->first);
		break;
	case 2:
		m_buffer[m_buffer_w] = m_f.get_extra_value(e.i->first);
		break;
	}
	pDispInfo->item.pszText = const_cast<char*>(m_buffer[m_buffer_w].c_str());
	m_buffer_w--;
	if (m_buffer_w < 0)
		m_buffer_w += 4;
	*pResult = 0;
}

void CXSTE_dlg::OnOK() 
{
	ETSLayoutDialog::OnOK();
	int cb_d = m_f.get_write_size();
	byte* d = new byte[cb_d];
	m_f.write(d);
	file32_write(xcc_dirs::get_dir(m_game) + xcc_dirs::get_csf_fname(m_game, m_expansion), d, cb_d);
	delete[] d;
}

void CXSTE_dlg::OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int column = reinterpret_cast<NM_LISTVIEW*>(pNMHDR)->iSubItem;
	sort_list(column, column == m_sort_column ? !m_sort_reverse : false);
	*pResult = 0;
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

int CXSTE_dlg::compare(int id_a, int id_b) const
{
	if (m_sort_reverse)
		swap(id_a, id_b);
	const t_map_entry& a = m_map.find(id_a)->second;
	const t_map_entry& b = m_map.find(id_b)->second;
	switch (m_sort_column)
	{
	case 0:
		return compare_string(a.i->first, b.i->first);
	case 1:
		return compare_string(m_f.get_converted_value(a.i->first), m_f.get_converted_value(b.i->first));
	case 2:
		return compare_string(m_f.get_extra_value(a.i->first), m_f.get_extra_value(b.i->first));
	default:
		return 0;
	}
}

static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return reinterpret_cast<CXSTE_dlg*>(lParamSort)->compare(lParam1, lParam2);
}

void CXSTE_dlg::sort_list(int i, bool reverse)
{
	m_sort_column = i;
	m_sort_reverse = reverse;
	m_list.SortItems(Compare, reinterpret_cast<dword>(this));
}

void CXSTE_dlg::OnItemchangedCatList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	SetRedraw(false);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->uNewState & LVIS_SELECTED)
	{
		if (~pNMListView->uOldState & LVIS_SELECTED)
		{
			m_list.DeleteAllItems();
			int cat_id = m_cat_list.GetItemData(pNMListView->iItem);
			for (t_map::const_iterator i = m_map.begin(); i != m_map.end(); i++)
			{
				if (i->second.cat_id == cat_id)
				{
					LVFINDINFO lvf;
					lvf.flags = LVFI_PARAM;
					lvf.lParam = i->first;
					int index = m_list.FindItem(&lvf, -1);
					if (index == -1)
						insert(i->first);
				}
			}
			m_sort_column = -1;
			for (int j = 0; j < c_colums; j++)
				m_list.SetColumnWidth(j, LVSCW_AUTOSIZE);
		}
	}
	// else if (pNMListView->uOldState & LVIS_SELECTED)
		
	SetRedraw(true);
	Invalidate();
	*pResult = 0;
}