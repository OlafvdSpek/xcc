// edit_structure_properties_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "xcc editor.h"
#include "edit_structure_properties_dlg.h"
#include "edit_triggers_dlg.h"
#include "xcc_cell.h"
#include "xcc_structures.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cedit_structure_properties_dlg dialog


Cedit_structure_properties_dlg::Cedit_structure_properties_dlg(Cxcc_level& level)
	: CDialog(Cedit_structure_properties_dlg::IDD, 0),
	m_level(level)
{
	//{{AFX_DATA_INIT(Cedit_structure_properties_dlg)
	m_edit_angle = 0;
	m_edit_cell = _T("");
	m_edit_health = 0;
	m_edit_trigger = _T("");
	m_edit_type = _T("");
	m_check_replace = FALSE;
	m_check_start = FALSE;
	//}}AFX_DATA_INIT
}


void Cedit_structure_properties_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cedit_structure_properties_dlg)
	DDX_Control(pDX, IDC_COMBO_SIDE, m_combo_side);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_edit_angle);
	DDV_MinMaxLong(pDX, m_edit_angle, 0, 255);
	DDX_Text(pDX, IDC_EDIT_CELL, m_edit_cell);
	DDX_Text(pDX, IDC_EDIT_HEALTH, m_edit_health);
	DDV_MinMaxLong(pDX, m_edit_health, 1, 256);
	DDX_Text(pDX, IDC_EDIT_TRIGGER, m_edit_trigger);
	DDV_MaxChars(pDX, m_edit_trigger, 15);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_edit_type);
	DDX_Check(pDX, IDC_CHECK_REPLACE, m_check_replace);
	DDX_Check(pDX, IDC_CHECK_START, m_check_start);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cedit_structure_properties_dlg, CDialog)
	//{{AFX_MSG_MAP(Cedit_structure_properties_dlg)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cedit_structure_properties_dlg message handlers

BOOL Cedit_structure_properties_dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	long i;
	for (i = 0; i < c_side_id; i++)
	{
		m_combo_side.SetItemData(m_combo_side.AddString(side_code[i]), i);
	}
	
	m_edit_type = xcc_structures::structure_data[m_d.t].long_name.c_str();
	m_combo_side.SelectString(-1, side_code[m_d.side]);
	m_edit_cell = static_cast<string>(Cxcc_cell(m_d.cell)).c_str();
	m_edit_health = m_d.health;
	m_edit_angle = m_d.angle;
	m_edit_trigger = m_d.trigger.c_str();
	m_check_start = static_cast<bool>(m_d.flags & sd_flags_start);
	m_check_replace = static_cast<bool>(m_d.flags & sd_flags_replace);
	UpdateData(false);
	
	return true;
}

void Cedit_structure_properties_dlg::OnOK() 
{
	if (!UpdateData(true))
		return;
	m_d.side = static_cast<t_side_id>(m_combo_side.GetItemData(m_combo_side.GetCurSel()));
	m_d.health = m_edit_health;
	m_d.angle = m_edit_angle;
	m_d.trigger = m_edit_trigger;
	m_d.flags = 0;
	if (m_check_start)
		m_d.flags |= sd_flags_start;
	if (m_check_replace)
		m_d.flags |= sd_flags_replace;
	CDialog::OnOK();
}

void Cedit_structure_properties_dlg::OnSelect() 
{
	Cedit_triggers_dlg dlg(m_level, true);
	if (dlg.DoModal() == IDOK)
	{
		m_edit_trigger = dlg.get_selected_name().c_str();
		UpdateData(false);
	}
}
