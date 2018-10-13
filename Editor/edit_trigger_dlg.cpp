#include "stdafx.h"
#include "edit_teamtypes_dlg.h"
#include "edit_trigger_dlg.h"

Cedit_trigger_dlg::Cedit_trigger_dlg(Cxcc_level& level)
	: CDialog(Cedit_trigger_dlg::IDD, 0),
	m_level(level)
{
	//{{AFX_DATA_INIT(Cedit_trigger_dlg)
	m_edit_count = 0;
	//}}AFX_DATA_INIT
	m_trigger_data_loaded = false;
}

void Cedit_trigger_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cedit_trigger_dlg)
	DDX_Control(pDX, IDC_COMBO_SIDE, m_combo_side);
	DDX_Control(pDX, IDC_COMBO_EVENT, m_combo_event);
	DDX_Control(pDX, IDC_COMBO_CAUSE, m_combo_cause);
	DDX_Text(pDX, IDC_EDIT_TEAMTYPE, m_edit_teamtype);
	DDV_MaxChars(pDX, m_edit_teamtype, 15);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_edit_count);
	DDV_MinMaxLong(pDX, m_edit_count, 0, 999);
	DDX_CBIndex(pDX, IDC_COMBO_LOOP, m_combo_loop);
	DDX_Text(pDX, IDC_EDIT_NAME, m_edit_name);
	DDV_MaxChars(pDX, m_edit_name, 15);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Cedit_trigger_dlg, CDialog)
	//{{AFX_MSG_MAP(Cedit_trigger_dlg)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static void insert(CComboBox& ctl, const string& t, int v)
{
	ctl.SetItemData(ctl.AddString(t.c_str()), v);
}

BOOL Cedit_trigger_dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	for (int i = 0; cause_code[i]; i++)
		insert(m_combo_cause, cause_code[i], i);
	for (int i = 0; event_code[i]; i++)
		insert(m_combo_event, event_code[i], i);
	for (int i = 0; i < c_side_id + 1; i++)
		insert(m_combo_side, side_code[i], i);
	
	if (m_trigger_data_loaded)
	{
		m_edit_name = m_trigger_name.c_str();
		m_combo_cause.SelectString(-1, cause_code[m_trigger_data.cause]);
		m_combo_event.SelectString(-1, event_code[m_trigger_data.event]);
		m_edit_count = m_trigger_data.count;
		m_combo_side.SelectString(-1, side_code[m_trigger_data.side != -1 ? m_trigger_data.side : c_side_id]);
		m_edit_teamtype = m_trigger_data.teamtype.c_str();
		m_combo_loop = m_trigger_data.loop;
		UpdateData(false);
	}

	return true;
}

void Cedit_trigger_dlg::OnOK() 
{
	if (!UpdateData(true))
		return;

	if (m_edit_name.IsEmpty())
	{
		GotoDlgCtrl(GetDlgItem(IDC_EDIT_NAME));
		AfxMessageBox("Please enter a value");
		return;
	}
	m_trigger_name = m_edit_name;

	t_trigger_data_entry& d = m_trigger_data;
	long i;

	i = m_combo_cause.GetCurSel();
	if (i == CB_ERR)
	{
		GotoDlgCtrl(GetDlgItem(IDC_COMBO_CAUSE));
		AfxMessageBox("Please select a value");
		return;
	}
	d.cause = static_cast<t_cause_id>(m_combo_cause.GetItemData(i));

	i = m_combo_event.GetCurSel();
	if (i == CB_ERR)
	{
		GotoDlgCtrl(GetDlgItem(IDC_COMBO_EVENT));
		AfxMessageBox("Please select a value");
		return;
	}
	d.event = static_cast<t_event_id>(m_combo_event.GetItemData(i));

	d.count = m_edit_count;

	i = m_combo_side.GetCurSel();
	if (i == CB_ERR)
	{
		GotoDlgCtrl(GetDlgItem(IDC_COMBO_SIDE));
		AfxMessageBox("Please select a value");
		return;
	}
	d.side = static_cast<t_side_id>(m_combo_side.GetItemData(i));

	d.teamtype = m_edit_teamtype.IsEmpty() ? "none" : string(m_edit_teamtype);

	i = m_combo_loop;
	if (i == CB_ERR)
	{
		GotoDlgCtrl(GetDlgItem(IDC_COMBO_LOOP));
		AfxMessageBox("Please select a value");
		return;
	}
	d.loop = i;

	CDialog::OnOK();
}

void Cedit_trigger_dlg::load(const string& name)
{
	m_trigger_name = name;
	m_trigger_data = m_level.trigger_data[name];
	m_trigger_data_loaded = true;
}

void Cedit_trigger_dlg::save(string& name) const
{
	name = m_trigger_name;
	m_level.trigger_data[name] = m_trigger_data;
}

void Cedit_trigger_dlg::OnSelect() 
{
	Cedit_teamtypes_dlg dlg(m_level, true);
	if (dlg.DoModal() == IDOK)
	{
		m_edit_teamtype = dlg.get_selected_name().c_str();
		UpdateData(false);
	}
}
