// list_ctrl_extension.cpp : implementation file
//

#include "stdafx.h"
#include "list_ctrl_extension.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Clist_ctrl_extension

Clist_ctrl_extension::Clist_ctrl_extension()
{
	m_max_column_i = -1;
}

Clist_ctrl_extension::~Clist_ctrl_extension()
{
}


BEGIN_MESSAGE_MAP(Clist_ctrl_extension, CListCtrl)
	//{{AFX_MSG_MAP(Clist_ctrl_extension)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Clist_ctrl_extension message handlers

void Clist_ctrl_extension::set_fixed_width_font()
{
	if (m_font.CreateFont(-11, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New"))
		SetFont(&m_font);
}

void Clist_ctrl_extension::add_column(const string& text, long index, dword format)
{
	LV_COLUMN column_data;
	column_data.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT;
	column_data.fmt = format;
	char s[256];
	strcpy(s, text.c_str()); 
	column_data.pszText = s;
	column_data.iSubItem = index;
	InsertColumn(index, &column_data);
	if (index > m_max_column_i)
		m_max_column_i = index;
}

void Clist_ctrl_extension::add_item(const string& text, dword index, dword user_parameter)
{
	LV_ITEM item_data;
	item_data.mask = LVIF_TEXT | LVIF_PARAM;
	item_data.iItem = index;
	item_data.iSubItem = 0;
	char s[256];
	strcpy(s, text.c_str()); 
	item_data.pszText = s;
	item_data.lParam = user_parameter;
	InsertItem(&item_data);
}

void Clist_ctrl_extension::set_item(const string& text, dword index, dword subindex)
{
	SetItemText(index, subindex, text.c_str());
}

void Clist_ctrl_extension::autosize_columns()
{
	for (long i = 0; i <= m_max_column_i; i++)
		SetColumnWidth(i, LVSCW_AUTOSIZE);
}

void Clist_ctrl_extension::set_full_row_selection()
{
	ListView_SetExtendedListViewStyle(m_hWnd, ListView_GetExtendedListViewStyle(m_hWnd) | LVS_EX_FULLROWSELECT);
}

long Clist_ctrl_extension::get_focused_item() const
{
	return GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
}

BOOL Clist_ctrl_extension::PreCreateWindow(CREATESTRUCT& cs) 
{
	// cs.dwExStyle |= LVS_EX_FULLROWSELECT;
	return CListCtrl::PreCreateWindow(cs);
}
