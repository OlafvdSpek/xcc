// edit_structures_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "edit_structures_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cedit_structures_dlg dialog


Cedit_structures_dlg::Cedit_structures_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cedit_structures_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cedit_structures_dlg)
	m_edit_long_name = _T("");
	m_edit_short_name = _T("");
	m_edit_flags = 0;
	m_edit_size = _T("");
	m_check_bib = FALSE;
	m_check_civilian = FALSE;
	m_check_icon = FALSE;
	m_check_desert = FALSE;
	m_check_temperate = FALSE;
	m_check_winter = FALSE;
	m_check_blocked10 = FALSE;
	m_check_blocked11 = FALSE;
	m_check_blocked3 = FALSE;
	m_check_blocked4 = FALSE;
	m_check_blocked5 = FALSE;
	m_check_blocked6 = FALSE;
	m_check_blocked7 = FALSE;
	m_check_blocked8 = FALSE;
	m_check_blocked9 = FALSE;
	m_check_blocked0 = FALSE;
	m_check_blocked1 = FALSE;
	m_check_blocked2 = FALSE;
	//}}AFX_DATA_INIT
}


void Cedit_structures_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cedit_structures_dlg)
	DDX_Control(pDX, IDC_EDIT_FLAGS, m_editctrl_flags);
	DDX_Control(pDX, IDC_EDIT_SHORT_NAME, m_editctrl_short_name);
	DDX_Control(pDX, IDC_EDIT_LONG_NAME, m_editctrl_long_name);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Text(pDX, IDC_EDIT_LONG_NAME, m_edit_long_name);
	DDX_Text(pDX, IDC_EDIT_SHORT_NAME, m_edit_short_name);
	DDX_Text(pDX, IDC_EDIT_FLAGS, m_edit_flags);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_edit_size);
	DDX_Check(pDX, IDC_CHECK_BIB, m_check_bib);
	DDX_Check(pDX, IDC_CHECK_CIVILIAN, m_check_civilian);
	DDX_Check(pDX, IDC_CHECK_ICON, m_check_icon);
	DDX_Check(pDX, IDC_CHECK_DESERT, m_check_desert);
	DDX_Check(pDX, IDC_CHECK_TEMPERATE, m_check_temperate);
	DDX_Check(pDX, IDC_CHECK_WINTER, m_check_winter);
	DDX_Check(pDX, IDC_CHECK_BLOCKED10, m_check_blocked10);
	DDX_Check(pDX, IDC_CHECK_BLOCKED11, m_check_blocked11);
	DDX_Check(pDX, IDC_CHECK_BLOCKED3, m_check_blocked3);
	DDX_Check(pDX, IDC_CHECK_BLOCKED4, m_check_blocked4);
	DDX_Check(pDX, IDC_CHECK_BLOCKED5, m_check_blocked5);
	DDX_Check(pDX, IDC_CHECK_BLOCKED6, m_check_blocked6);
	DDX_Check(pDX, IDC_CHECK_BLOCKED7, m_check_blocked7);
	DDX_Check(pDX, IDC_CHECK_BLOCKED8, m_check_blocked8);
	DDX_Check(pDX, IDC_CHECK_BLOCKED9, m_check_blocked9);
	DDX_Check(pDX, IDC_CHECK_BLOCKED0, m_check_blocked0);
	DDX_Check(pDX, IDC_CHECK_BLOCKED1, m_check_blocked1);
	DDX_Check(pDX, IDC_CHECK_BLOCKED2, m_check_blocked2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cedit_structures_dlg, CDialog)
	//{{AFX_MSG_MAP(Cedit_structures_dlg)
	ON_BN_CLICKED(IDC_NEW_BUTTON, OnNewButton)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, OnItemchangedList2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cedit_structures_dlg message handlers

BOOL Cedit_structures_dlg::OnInitDialog() 
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
		xcc_structures::t_structure_data_entry& sd = xcc_structures::structure_data[i];
		if (sd.flags & sd_flags_in_use)
			last_i = i;
	}
	for (i = 0; i <= last_i; i++)
	{
			add_item(i);
	}

	m_list.autosize_columns();
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void Cedit_structures_dlg::OnNewButton() 
{
	for (long i = 0; i < 256; i++)
	{
		xcc_structures::t_structure_data_entry& sd = xcc_structures::structure_data[i];
		if (sd.flags & sd_flags_in_use)
			continue;
		sd.long_name = "";
		sd.short_name = "";
		sd.flags = sd_flags_in_use;
		add_item(i);
		m_list.SetItemState(i, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
		m_list.Update(i);

		break;
	}
}

void Cedit_structures_dlg::add_item(long i)
{
	xcc_structures::t_structure_data_entry& sd = xcc_structures::structure_data[i];	
	m_list.add_item(sd.long_name, i, i);
	m_list.set_item(n(i), i, 1);
}

void Cedit_structures_dlg::update_item(long i)
{
	xcc_structures::t_structure_data_entry& sd = xcc_structures::structure_data[i];	
	m_list.set_item(sd.long_name, i, 0);
}

void Cedit_structures_dlg::OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->uChanged & LVIF_STATE)
		update_controls();
	*pResult = 0;
}

void Cedit_structures_dlg::update_controls()
{
	long new_i = m_list.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
	save_controls();
	m_current_i = new_i;
	bool enable = m_current_i != -1;
	m_editctrl_long_name.EnableWindow(enable);
	m_editctrl_short_name.EnableWindow(enable);
	m_editctrl_flags.EnableWindow(enable);
	load_controls();
}

void Cedit_structures_dlg::load_controls()
{
	if (m_current_i == -1)
		return;
	xcc_structures::t_structure_data_entry& sd = xcc_structures::structure_data[m_current_i];	
	m_edit_long_name = sd.long_name.c_str();
	m_edit_short_name = sd.short_name.c_str();
	m_edit_flags = sd.flags;
	m_edit_size = (n(sd.cx) + " x " + n(sd.cy)).c_str();
	m_check_bib = static_cast<bool>(sd.flags & sd_flags_bib);
	m_check_civilian = static_cast<bool>(sd.flags & sd_flags_civilian);
	m_check_icon = static_cast<bool>(sd.flags & sd_flags_icon);
	m_check_desert = static_cast<bool>(sd.flags & sd_flags_desert);
	m_check_temperate = static_cast<bool>(sd.flags & sd_flags_temperate);
	m_check_winter = static_cast<bool>(sd.flags & sd_flags_winter);
	m_check_blocked0 = static_cast<bool>(sd.blocked >> 0 & 1);
	m_check_blocked1 = static_cast<bool>(sd.blocked >> 1 & 1);
	m_check_blocked2 = static_cast<bool>(sd.blocked >> 2 & 1);
	m_check_blocked3 = static_cast<bool>(sd.blocked >> 3 & 1);
	m_check_blocked4 = static_cast<bool>(sd.blocked >> 4 & 1);
	m_check_blocked5 = static_cast<bool>(sd.blocked >> 5 & 1);
	m_check_blocked6 = static_cast<bool>(sd.blocked >> 6 & 1);
	m_check_blocked7 = static_cast<bool>(sd.blocked >> 7 & 1);
	m_check_blocked8 = static_cast<bool>(sd.blocked >> 8 & 1);
	m_check_blocked9 = static_cast<bool>(sd.blocked >> 9 & 1);
	m_check_blocked10 = static_cast<bool>(sd.blocked >> 10 & 1);
	m_check_blocked11 = static_cast<bool>(sd.blocked >> 11 & 1);
	UpdateData(false);
}

void Cedit_structures_dlg::save_controls()
{
	if (m_current_i == -1)
		return;
	UpdateData(true);
	xcc_structures::t_structure_data_entry& sd = xcc_structures::structure_data[m_current_i];	
	sd.long_name = m_edit_long_name;
	sd.short_name = m_edit_short_name;
	sd.flags = m_edit_flags;
	sd.blocked = 0;
	if (m_check_blocked0)
		sd.blocked |= 1 << 0;
	if (m_check_blocked1)
		sd.blocked |= 1 << 1;
	if (m_check_blocked2)
		sd.blocked |= 1 << 2;
	if (m_check_blocked3)
		sd.blocked |= 1 << 3;
	if (m_check_blocked4)
		sd.blocked |= 1 << 4;
	if (m_check_blocked5)
		sd.blocked |= 1 << 5;
	if (m_check_blocked6)
		sd.blocked |= 1 << 6;
	if (m_check_blocked7)
		sd.blocked |= 1 << 7;
	if (m_check_blocked8)
		sd.blocked |= 1 << 8;
	if (m_check_blocked9)
		sd.blocked |= 1 << 9;
	if (m_check_blocked10)
		sd.blocked |= 1 << 10;
	if (m_check_blocked11)
		sd.blocked |= 1 << 11;
	update_item(m_current_i);
}

void Cedit_structures_dlg::OnOK() 
{
	save_controls();
	CDialog::OnOK();
}
