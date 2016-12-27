#include "stdafx.h"
#include "edit_teamtype_dlg.h"
#include "edit_waypoints_dlg.h"
#include "string_conversion.h"
#include "xcc_infantry.h"
#include "xcc_structures.h"
#include "xcc_units.h"

Cedit_teamtype_dlg::Cedit_teamtype_dlg(Cxcc_level& level)
	: CDialog(Cedit_teamtype_dlg::IDD, 0),
	m_level(level)
{
	//{{AFX_DATA_INIT(Cedit_teamtype_dlg)
	m_edit_u1 = 7;
	m_edit_c_teams = 0;
	m_edit_object = 1;
	m_edit_action = 0;
	m_check_autocreate = FALSE;
	m_check_force_creation = FALSE;
	m_check_force_move = FALSE;
	m_check_link = FALSE;
	m_check_replace = FALSE;
	//}}AFX_DATA_INIT
	m_teamtype_data_loaded = false;
}

void Cedit_teamtype_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cedit_teamtype_dlg)
	DDX_Control(pDX, IDC_ACTION_INSERT, m_action_insert_button);
	DDX_Control(pDX, IDC_OBJECT_INSERT, m_object_insert_button);
	DDX_Control(pDX, IDC_OBJECT_DELETE, m_object_delete_button);
	DDX_Control(pDX, IDC_ACTION_DELETE, m_action_delete_button);
	DDX_Control(pDX, IDC_OBJECT_LIST, m_list_object);
	DDX_Control(pDX, IDC_ACTION_LIST, m_list_action);
	DDX_Control(pDX, IDC_COMBO_SIDE, m_combo_side);
	DDX_Control(pDX, IDC_OBJECT_COMBO, m_combo_object);
	DDX_Control(pDX, IDC_ACTION_COMBO, m_combo_action);
	DDX_Text(pDX, IDC_EDIT_NAME, m_edit_name);
	DDV_MaxChars(pDX, m_edit_name, 15);
	DDX_Text(pDX, IDC_EDIT_U1, m_edit_u1);
	DDV_MinMaxInt(pDX, m_edit_u1, 2, 30);
	DDX_Text(pDX, IDC_EDIT_C_TEAMS, m_edit_c_teams);
	DDV_MinMaxInt(pDX, m_edit_c_teams, 0, 99);
	DDX_Text(pDX, IDC_OBJECT_EDIT, m_edit_object);
	DDV_MinMaxInt(pDX, m_edit_object, 1, 99);
	DDX_Text(pDX, IDC_ACTION_EDIT, m_edit_action);
	DDV_MinMaxInt(pDX, m_edit_action, 0, 99);
	DDX_Check(pDX, IDC_CHECK_AUTOCREATE, m_check_autocreate);
	DDX_Check(pDX, IDC_CHECK_FORCE_CREATION, m_check_force_creation);
	DDX_Check(pDX, IDC_CHECK_FORCE_MOVE, m_check_force_move);
	DDX_Check(pDX, IDC_CHECK_LINK, m_check_link);
	DDX_Check(pDX, IDC_CHECK_REPLACE, m_check_replace);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Cedit_teamtype_dlg, CDialog)
	//{{AFX_MSG_MAP(Cedit_teamtype_dlg)
	ON_BN_CLICKED(IDC_ACTION_SELECT, OnActionSelect)
	ON_BN_CLICKED(IDC_OBJECT_DELETE, OnObjectDelete)
	ON_BN_CLICKED(IDC_ACTION_DELETE, OnActionDelete)
	ON_BN_CLICKED(IDC_OBJECT_INSERT, OnObjectInsert)
	ON_BN_CLICKED(IDC_ACTION_INSERT, OnActionInsert)
	ON_LBN_SELCHANGE(IDC_ACTION_LIST, OnSelchangeActionList)
	ON_LBN_SELCHANGE(IDC_OBJECT_LIST, OnSelchangeObjectList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static void insert(CComboBox& ctl, const string& t, int v)
{
	ctl.SetItemData(ctl.AddString(t.c_str()), v);
}

static void insert(CListBox& ctl, const string& t)
{
	ctl.AddString(t.c_str());
}

BOOL Cedit_teamtype_dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	for (int i = 0; i < c_side_id + 1; i++)
		insert(m_combo_side, side_code[i], i < c_side_id ? i : -1);
	for (int i = 0; i < 256; i++)
	{
		const xcc_infantry::t_infantry_data_entry& id = xcc_infantry::infantry_data[i];
		if (id.flags & id_flags_in_use)
			insert(m_combo_object, id.long_name, i);
		const xcc_units::t_unit_data_entry& ud = xcc_units::unit_data[i];
		if (ud.flags & ud_flags_in_use)
			insert(m_combo_object, ud.long_name, 0x80 | i);
	}
	for (int i = 0; action_code[i]; i++)
		insert(m_combo_action, action_code[i], i);
	
	if (m_teamtype_data_loaded)
	{
		const t_teamtype_data_entry& d = m_teamtype_data;
		m_edit_name = m_teamtype_name.c_str();
		m_combo_side.SelectString(-1, side_code[m_teamtype_data.side != -1 ? m_teamtype_data.side : c_side_id]);
		m_edit_u1 = m_teamtype_data.u1;
		m_edit_c_teams = m_teamtype_data.c_teams;
		m_check_link = static_cast<bool>(m_teamtype_data.flags & td_flags_link);
		m_check_force_move = static_cast<bool>(m_teamtype_data.flags & td_flags_force_move);
		m_check_autocreate = static_cast<bool>(m_teamtype_data.flags & td_flags_autocreate);
		m_check_replace = static_cast<bool>(m_teamtype_data.flags & td_flags_replace);
		m_check_force_creation = static_cast<bool>(m_teamtype_data.flags & td_flags_force_creation);
		for (auto& i : d.objects)
			add_object(i);
		for (auto& i : d.actions)
			add_action(i);
		UpdateData(false);
	}

	return true;
}

void Cedit_teamtype_dlg::OnOK() 
{
	if (!UpdateData(true))
		return;

	if (m_edit_name.IsEmpty())
	{
		GotoDlgCtrl(GetDlgItem(IDC_EDIT_NAME));
		AfxMessageBox("Please enter a value");
		return;
	}
	m_teamtype_name = m_edit_name;

	t_teamtype_data_entry& d = m_teamtype_data;
	int i;

	i = m_combo_side.GetCurSel();
	if (i == CB_ERR)
	{
		GotoDlgCtrl(GetDlgItem(IDC_COMBO_SIDE));
		AfxMessageBox("Please select a value");
		return;
	}
	d.side = static_cast<t_side_id>(m_combo_side.GetItemData(i));

	d.u1 = m_edit_u1;
	d.c_teams = m_edit_c_teams;
	d.flags = 0;
	if (m_check_link)
		d.flags |= td_flags_link;
	if (m_check_force_move)
		d.flags |= td_flags_force_move;
	if (m_check_autocreate)
		d.flags |= td_flags_autocreate;
	if (m_check_replace)
		d.flags |= td_flags_replace;
	if (m_check_force_creation)
		d.flags |= td_flags_force_creation;

	CDialog::OnOK();
}

void Cedit_teamtype_dlg::load(const string& name)
{
	m_teamtype_name = name;
	m_teamtype_data = m_level.teamtype_data[name];
	m_teamtype_data_loaded = true;
}

void Cedit_teamtype_dlg::save(string& name) const
{
	name = m_teamtype_name;
	m_level.teamtype_data[name] = m_teamtype_data;
}

void Cedit_teamtype_dlg::OnObjectInsert() 
{
	if (!UpdateData(true))
		return;
	int i = m_combo_object.GetCurSel();
	if (i == CB_ERR)
	{
		GotoDlgCtrl(GetDlgItem(IDC_OBJECT_COMBO));
		AfxMessageBox("Please select a value");
		return;
	}
	t_teamtype_data_entry& d = m_teamtype_data;
	int v = m_combo_object.GetItemData(i);
	d.objects.push_back(make_pair(v & 0x80 ? xcc_units::unit_data[v & 0x7f].short_name : xcc_infantry::infantry_data[v].short_name, m_edit_object));
	add_object(d.objects.back());
	OnSelchangeObjectList();
}

void Cedit_teamtype_dlg::OnObjectDelete() 
{
	t_teamtype_data_entry& d = m_teamtype_data;
	int i = get_selected_object_i();
	m_list_object.DeleteString(i);
	d.objects.erase(d.objects.begin() + i);
	OnSelchangeObjectList();
}

void Cedit_teamtype_dlg::OnActionInsert() 
{
	if (!UpdateData(true))
		return;
	int i = m_combo_action.GetCurSel();
	if (i == CB_ERR)
	{
		GotoDlgCtrl(GetDlgItem(IDC_ACTION_COMBO));
		AfxMessageBox("Please select a value");
		return;
	}
	t_teamtype_data_entry& d = m_teamtype_data;
	d.actions.push_back(make_pair(m_combo_action.GetItemData(i), m_edit_action));
	add_action(d.actions.back());
	OnSelchangeActionList();
}

void Cedit_teamtype_dlg::OnActionSelect() 
{
	Cedit_waypoints_dlg dlg(m_level, true);
	if (dlg.DoModal() == IDOK)
	{
		m_edit_action = dlg.get_selected_i();
		UpdateData(false);
	}
}

void Cedit_teamtype_dlg::OnActionDelete() 
{
	t_teamtype_data_entry& d = m_teamtype_data;
	int i = get_selected_action_i();
	m_list_action.DeleteString(i);
	d.actions.erase(d.actions.begin() + i);
	OnSelchangeActionList();
}

int Cedit_teamtype_dlg::get_selected_object_i()
{
	int i = m_list_object.GetCurSel();
	return i == CB_ERR ? -1 : i;
}

int Cedit_teamtype_dlg::get_selected_action_i()
{
	int i = m_list_action.GetCurSel();
	return i == CB_ERR ? -1 : i;
}

void Cedit_teamtype_dlg::OnSelchangeObjectList() 
{
	m_object_insert_button.EnableWindow(m_teamtype_data.objects.size() < 9);
	m_object_delete_button.EnableWindow(get_selected_object_i() != -1);
}

void Cedit_teamtype_dlg::OnSelchangeActionList() 
{
	m_action_insert_button.EnableWindow(m_teamtype_data.actions.size() < 64);
	m_action_delete_button.EnableWindow(get_selected_action_i() != -1);
}

void Cedit_teamtype_dlg::add_object(const t_teamtype_data_entry::t_objects::value_type& v)
{
	insert(m_list_object, v.first + ": " + n(v.second));
}

void Cedit_teamtype_dlg::add_action(const t_teamtype_data_entry::t_actions::value_type& v)
{
	insert(m_list_action, static_cast<string>(action_code[v.first]) + ": " + n(v.second));
}
