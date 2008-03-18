#include "stdafx.h"
#include "edit_infantry_dlg.h"

Cedit_infantry_dlg::Cedit_infantry_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cedit_infantry_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cedit_infantry_dlg)
	m_check_civilian = FALSE;
	m_check_icon = FALSE;
	m_edit_long_name = _T("");
	m_edit_short_name = _T("");
	m_edit_size = _T("");
	m_edit_ox = 0;
	m_edit_oy = 0;
	m_edit_flags = 0;
	//}}AFX_DATA_INIT
}

void Cedit_infantry_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cedit_infantry_dlg)
	DDX_Control(pDX, IDC_EDIT_OY, m_editctrl_oy);
	DDX_Control(pDX, IDC_EDIT_OX, m_editctrl_ox);
	DDX_Control(pDX, IDC_EDIT_SHORT_NAME, m_editctrl_short_name);
	DDX_Control(pDX, IDC_EDIT_LONG_NAME, m_editctrl_long_name);
	DDX_Control(pDX, IDC_EDIT_FLAGS, m_editctrl_flags);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Check(pDX, IDC_CHECK_CIVILIAN, m_check_civilian);
	DDX_Check(pDX, IDC_CHECK_ICON, m_check_icon);
	DDX_Text(pDX, IDC_EDIT_LONG_NAME, m_edit_long_name);
	DDX_Text(pDX, IDC_EDIT_SHORT_NAME, m_edit_short_name);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_edit_size);
	DDX_Text(pDX, IDC_EDIT_OX, m_edit_ox);
	DDX_Text(pDX, IDC_EDIT_OY, m_edit_oy);
	DDX_Text(pDX, IDC_EDIT_FLAGS, m_edit_flags);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Cedit_infantry_dlg, CDialog)
	//{{AFX_MSG_MAP(Cedit_infantry_dlg)
	ON_BN_CLICKED(IDC_NEW_BUTTON, OnNewButton)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, OnItemchangedList2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL Cedit_infantry_dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	

	m_current_i = -1;
	update_controls();

	ListView_SetExtendedListViewStyle(m_list.m_hWnd, ListView_GetExtendedListViewStyle(m_list.m_hWnd) | LVS_EX_FULLROWSELECT);
	m_list.add_column("Name", 0);
	m_list.add_column("Index", 1, LVCFMT_RIGHT);

	long last_i = -1;
	for (long i = 0; i < 256; i++)
	{
		xcc_infantry::t_infantry_data_entry& id = xcc_infantry::infantry_data[i];
		if (id.flags & id_flags_in_use)
			last_i = i;
	}
	for (int i = 0; i <= last_i; i++)
	{
		add_item(i);
	}

	m_list.autosize_columns();
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void Cedit_infantry_dlg::OnNewButton() 
{
	for (long i = 0; i < 256; i++)
	{
		xcc_infantry::t_infantry_data_entry& id = xcc_infantry::infantry_data[i];
		if (id.flags & id_flags_in_use)
			continue;
		id.long_name = "";
		id.short_name = "";
		id.flags = id_flags_in_use;
		add_item(i);
		m_list.SetItemState(i, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
		m_list.Update(i);

		break;
	}
}

void Cedit_infantry_dlg::add_item(long i)
{
	xcc_infantry::t_infantry_data_entry& id = xcc_infantry::infantry_data[i];	
	m_list.add_item(id.long_name, i, i);
	m_list.set_item(n(i), i, 1);
}

void Cedit_infantry_dlg::update_item(long i)
{
	xcc_infantry::t_infantry_data_entry& id = xcc_infantry::infantry_data[i];	
	m_list.set_item(id.long_name, i, 0);
}

void Cedit_infantry_dlg::OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->uChanged & LVIF_STATE)
		update_controls();
	*pResult = 0;
}

void Cedit_infantry_dlg::update_controls()
{
	long new_i = m_list.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
	save_controls();
	m_current_i = new_i;
	bool enable = m_current_i != -1;
	m_editctrl_long_name.EnableWindow(enable);
	m_editctrl_short_name.EnableWindow(enable);
	m_editctrl_flags.EnableWindow(enable);
	m_editctrl_ox.EnableWindow(enable);
	m_editctrl_oy.EnableWindow(enable);
	load_controls();
}

void Cedit_infantry_dlg::load_controls()
{
	if (m_current_i == -1)
		return;
	xcc_infantry::t_infantry_data_entry& id = xcc_infantry::infantry_data[m_current_i];	
	m_edit_long_name = id.long_name.c_str();
	m_edit_short_name = id.short_name.c_str();
	m_edit_flags = id.flags;
	m_edit_size = (n(id.cx) + " x " + n(id.cy)).c_str();
	// m_edit_ox = id.ox;
	// m_edit_oy = id.oy;
	m_check_civilian = static_cast<bool>(id.flags & id_flags_civilian);
	m_check_icon = static_cast<bool>(id.flags & id_flags_icon);
	UpdateData(false);
}

void Cedit_infantry_dlg::save_controls()
{
	if (m_current_i == -1)
		return;
	UpdateData(true);
	xcc_infantry::t_infantry_data_entry& id = xcc_infantry::infantry_data[m_current_i];	
	id.long_name = m_edit_long_name;
	id.short_name = m_edit_short_name;
	id.flags = m_edit_flags;
	// id.ox = m_edit_ox;
	// id.oy = m_edit_oy;
	update_item(m_current_i);
}

void Cedit_infantry_dlg::OnOK() 
{
	save_controls();	
	CDialog::OnOK();
}
