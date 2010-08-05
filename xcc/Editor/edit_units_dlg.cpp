#include "stdafx.h"
#include "edit_units_dlg.h"

Cedit_units_dlg::Cedit_units_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cedit_units_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cedit_units_dlg)
	m_edit_long_name = _T("");
	m_edit_short_name = _T("");
	m_edit_size = _T("");
	m_check_icon = FALSE;
	m_edit_flags = 0;
	m_edit_base_ox = 0;
	m_edit_base_oy = 0;
	m_edit_c_rotations = 0;
	m_edit_c_images = 0;
	m_check_top = FALSE;
	//}}AFX_DATA_INIT
}

void Cedit_units_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cedit_units_dlg)
	DDX_Control(pDX, IDC_EDIT_C_ROTATIONS, m_editctrl_c_rotations);
	DDX_Control(pDX, IDC_EDIT_BASE_OY, m_editctrl_base_oy);
	DDX_Control(pDX, IDC_EDIT_BASE_OX, m_editctrl_base_ox);
	DDX_Control(pDX, IDC_EDIT_LONG_NAME, m_editctrl_long_name);
	DDX_Control(pDX, IDC_EDIT_SHORT_NAME, m_editctrl_short_name);
	DDX_Control(pDX, IDC_EDIT_FLAGS, m_editctrl_flags);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Text(pDX, IDC_EDIT_LONG_NAME, m_edit_long_name);
	DDX_Text(pDX, IDC_EDIT_SHORT_NAME, m_edit_short_name);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_edit_size);
	DDX_Check(pDX, IDC_CHECK_ICON, m_check_icon);
	DDX_Text(pDX, IDC_EDIT_FLAGS, m_edit_flags);
	DDX_Text(pDX, IDC_EDIT_BASE_OX, m_edit_base_ox);
	DDX_Text(pDX, IDC_EDIT_BASE_OY, m_edit_base_oy);
	DDX_Text(pDX, IDC_EDIT_C_ROTATIONS, m_edit_c_rotations);
	DDX_Text(pDX, IDC_EDIT_C_IMAGES, m_edit_c_images);
	DDX_Check(pDX, IDC_CHECK_TOP, m_check_top);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Cedit_units_dlg, CDialog)
	//{{AFX_MSG_MAP(Cedit_units_dlg)
	ON_BN_CLICKED(IDC_NEW_BUTTON, OnNewButton)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, OnItemchangedList2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL Cedit_units_dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	

	m_current_i = -1;
	update_controls();

	ListView_SetExtendedListViewStyle(m_list.m_hWnd, ListView_GetExtendedListViewStyle(m_list.m_hWnd) | LVS_EX_FULLROWSELECT);
	m_list.add_column("Name", 0);
	m_list.add_column("Index", 1, LVCFMT_RIGHT);

	long last_i = -1;
	for (int i = 0; i < 256; i++)
	{
		xcc_units::t_unit_data_entry& ud = xcc_units::unit_data[i];
		if (ud.flags & ud_flags_in_use)
			last_i = i;
	}
	for (int i = 0; i <= last_i; i++)
	{
		add_item(i);
	}

	m_list.autosize_columns();
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void Cedit_units_dlg::OnNewButton() 
{
	for (int i = 0; i < 256; i++)
	{
		xcc_units::t_unit_data_entry& ud = xcc_units::unit_data[i];
		if (ud.flags & ud_flags_in_use)
			continue;
		ud.long_name = "";
		ud.short_name = "";
		ud.flags = ud_flags_in_use;
		add_item(i);
		m_list.SetItemState(i, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
		m_list.Update(i);

		break;
	}
}

void Cedit_units_dlg::add_item(long i)
{
	xcc_units::t_unit_data_entry& ud = xcc_units::unit_data[i];	
	m_list.add_item(ud.long_name, i, i);
	m_list.set_item(n(i), i, 1);
}

void Cedit_units_dlg::update_item(long i)
{
	xcc_units::t_unit_data_entry& ud = xcc_units::unit_data[i];	
	m_list.set_item(ud.long_name, i, 0);
}

void Cedit_units_dlg::OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->uChanged & LVIF_STATE)
		update_controls();
	*pResult = 0;
}

void Cedit_units_dlg::update_controls()
{
	long new_i = m_list.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
	save_controls();
	m_current_i = new_i;
	bool enable = m_current_i != -1;
	m_editctrl_long_name.EnableWindow(enable);
	m_editctrl_short_name.EnableWindow(enable);
	m_editctrl_flags.EnableWindow(enable);
	m_editctrl_base_ox.EnableWindow(enable);
	m_editctrl_base_oy.EnableWindow(enable);
	m_editctrl_c_rotations.EnableWindow(enable);
	load_controls();
}

void Cedit_units_dlg::load_controls()
{
	if (m_current_i == -1)
		return;
	xcc_units::t_unit_data_entry& ud = xcc_units::unit_data[m_current_i];	
	m_edit_long_name = ud.long_name.c_str();
	m_edit_short_name = ud.short_name.c_str();
	m_edit_flags = ud.flags;
	m_edit_size = (n(ud.cx) + " x " + n(ud.cy)).c_str();
	m_edit_base_ox = ud.base_ox;
	m_edit_base_oy = ud.base_oy;
	m_edit_c_rotations = ud.c_rotations;
	m_edit_c_images = ud.c_images;
	m_check_icon = static_cast<bool>(ud.flags & ud_flags_icon);
	m_check_top = static_cast<bool>(ud.flags & ud_flags_top);
	UpdateData(false);
}

void Cedit_units_dlg::save_controls()
{
	if (m_current_i == -1)
		return;
	UpdateData(true);
	xcc_units::t_unit_data_entry& ud = xcc_units::unit_data[m_current_i];	
	ud.long_name = m_edit_long_name;
	ud.short_name = m_edit_short_name;
	ud.flags = m_edit_flags;
	ud.base_ox = m_edit_base_ox;
	ud.base_oy = m_edit_base_oy;
	ud.c_rotations = m_edit_c_rotations;
	update_item(m_current_i);
}

void Cedit_units_dlg::OnOK() 
{
	save_controls();
	CDialog::OnOK();
}
