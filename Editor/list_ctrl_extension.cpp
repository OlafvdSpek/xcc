#include "stdafx.h"
#include "list_ctrl_extension.h"

BEGIN_MESSAGE_MAP(Clist_ctrl_extension, CListCtrl)
	//{{AFX_MSG_MAP(Clist_ctrl_extension)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void Clist_ctrl_extension::set_fixed_width_font()
{
	if (m_font.CreateFont(-11, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New"))
		SetFont(&m_font);
}

void Clist_ctrl_extension::add_column(const string& text, int index, int format)
{
	InsertColumn(index, text.c_str(), format);
}

void Clist_ctrl_extension::add_item(const string& text, int index, int user_parameter)
{
	SetItemData(InsertItem(index, text.c_str()), user_parameter);
}

void Clist_ctrl_extension::set_item(const string& text, int index, int subindex)
{
	SetItemText(index, subindex, text.c_str());
}

void Clist_ctrl_extension::autosize_columns()
{
	for (int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)
		SetColumnWidth(i, LVSCW_AUTOSIZE);
}

int Clist_ctrl_extension::get_focused_item() const
{
	return GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
}

void Clist_ctrl_extension::PreSubclassWindow() 
{
	CListCtrl::PreSubclassWindow();
	SetExtendedStyle(GetExtendedStyle() | LVS_EX_FULLROWSELECT);
}
