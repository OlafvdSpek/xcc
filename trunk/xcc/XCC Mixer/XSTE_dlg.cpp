// XSTE_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "xcc mixer.h"
#include "XSTE_dlg.h"
#include "XSTE_edit_dlg.h"

#include "mix_file.h"
#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXSTE_dlg dialog


CXSTE_dlg::CXSTE_dlg(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(CXSTE_dlg::IDD, pParent, "XSTE_dlg")
{
	//{{AFX_DATA_INIT(CXSTE_dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_buffer_w = 0;
}


void CXSTE_dlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXSTE_dlg)
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
		<< item(IDC_LIST, GREEDY)
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

	int error = m_f.open(xcc_dirs::get_ra2_dir() + "ra2.csf");
	if (error)
	{
		Cmix_file language;
		error = language.open(xcc_dirs::get_ra2_dir() + "language.mix");
		if (!error)
		{
			error = m_f.open("ra2.csf", language);
			language.close();
		}
	}
	if (!error)
	{
		for (Ccsf_file::t_map::const_iterator i = m_f.get_map().begin(); i != m_f.get_map().end(); i++)
			insert(i->first);
		for (int j = 0; j < c_colums; j++)
			m_list.SetColumnWidth(j, LVSCW_AUTOSIZE);
		m_f.close();
	}	
	check_selection();
	SetRedraw(true);
	Invalidate();
	return true;
}

int CXSTE_dlg::insert(const string& name)
{
	int index = m_list.InsertItem(m_list.GetItemCount(), name.c_str());
	m_list.SetItemText(index, 1, LPSTR_TEXTCALLBACK);
	m_list.SetItemText(index, 2, LPSTR_TEXTCALLBACK);
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
	if (pNMListView->uNewState & LVIS_FOCUSED)
		check_selection();
	*pResult = 0;
}

void CXSTE_dlg::OnInsert() 
{
	m_f.set_value("", wstring(), "");
	m_list.SetFocus();
	m_list.EditLabel(insert(""));
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
	while (1)
	{
		int index = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if (index == -1)
			break;
		m_f.erase_value(static_cast<string>(m_list.GetItemText(index, 0)));
		m_list.DeleteItem(index);
	}
	check_selection();
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
		string old_name = m_list.GetItemText(pDispInfo->item.iItem, 0);
		Ccsf_file::t_map_entry e = m_f.get_map().find(old_name)->second;
		m_f.erase_value(old_name);
		m_f.set_value(t, e.value, e.extra_value);
		if (old_name.empty())
			check_selection();
		*pResult = true;
	}	
}

void CXSTE_dlg::OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	string name = m_list.GetItemText(pDispInfo->item.iItem, 0);
	m_buffer[m_buffer_w] = (pDispInfo->item.iSubItem == 1 ? m_f.get_converted_value(name): m_f.get_extra_value(name));
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
	file32_write(xcc_dirs::get_ra2_dir() + "ra2.csf", d, cb_d);
	delete[] d;
}

void CXSTE_dlg::OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	sort_list(reinterpret_cast<NM_LISTVIEW*>(pNMHDR)->iSubItem);
	*pResult = 0;
}

int CXSTE_dlg::compare(int id_a, int id_b) const
{
	/*
	const t_map_entry& a = m_map.find(id_a)->second;
	const t_map_entry& b = m_map.find(id_b)->second;
	*/
	switch (m_sort_column)
	{
	default:
		return 0;
	}
}

static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return reinterpret_cast<CXSTE_dlg*>(lParamSort)->compare(lParam1, lParam2);
}

void CXSTE_dlg::sort_list(int i)
{
	m_sort_column = i;
	m_list.SortItems(Compare, reinterpret_cast<dword>(this));
}

