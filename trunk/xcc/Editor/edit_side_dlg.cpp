#include "stdafx.h"
#include "edit_side_dlg.h"

Cedit_side_dlg::Cedit_side_dlg(t_side_data& side_data)
	: CDialog(Cedit_side_dlg::IDD, 0),
	m_side_data(side_data)
{
	//{{AFX_DATA_INIT(Cedit_side_dlg)
	m_check_badguy = FALSE;
	m_check_goodguy = FALSE;
	m_check_multi1 = FALSE;
	m_check_multi2 = FALSE;
	m_check_multi3 = FALSE;
	m_check_multi4 = FALSE;
	m_check_multi5 = FALSE;
	m_check_multi6 = FALSE;
	m_check_special = FALSE;
	m_edit_credits = 0;
	m_check_neutral = FALSE;
	//}}AFX_DATA_INIT
}

void Cedit_side_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cedit_side_dlg)
	DDX_Control(pDX, IDC_COMBO_EDGE, m_combo_edge);
	DDX_Check(pDX, IDC_CHECK_BADGUY, m_check_badguy);
	DDX_Check(pDX, IDC_CHECK_GOODGUY, m_check_goodguy);
	DDX_Check(pDX, IDC_CHECK_MULTI1, m_check_multi1);
	DDX_Check(pDX, IDC_CHECK_MULTI2, m_check_multi2);
	DDX_Check(pDX, IDC_CHECK_MULTI3, m_check_multi3);
	DDX_Check(pDX, IDC_CHECK_MULTI4, m_check_multi4);
	DDX_Check(pDX, IDC_CHECK_MULTI5, m_check_multi5);
	DDX_Check(pDX, IDC_CHECK_MULTI6, m_check_multi6);
	DDX_Check(pDX, IDC_CHECK_SPECIAL, m_check_special);
	DDX_Text(pDX, IDC_EDIT_CREDITS, m_edit_credits);
	DDV_MinMaxLong(pDX, m_edit_credits, 0, 1000000);
	DDX_Check(pDX, IDC_CHECK_NEUTRAL, m_check_neutral);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Cedit_side_dlg, CDialog)
	//{{AFX_MSG_MAP(Cedit_side_dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL Cedit_side_dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	for (long i = 0; i < c_edge_id; i++)
	{
		m_combo_edge.SetItemData(m_combo_edge.AddString(edge_code[i]), i);
	}

	const t_side_data& d = m_side_data;
	m_check_goodguy = static_cast<bool>(d.allies >> s_goodguy & 1);
	m_check_badguy = static_cast<bool>(d.allies >> s_badguy & 1);
	m_check_neutral = static_cast<bool>(d.allies >> s_neutral & 1);
	m_check_special = static_cast<bool>(d.allies >> s_special & 1);
	m_check_multi1 = static_cast<bool>(d.allies >> s_multi1 & 1);
	m_check_multi2 = static_cast<bool>(d.allies >> s_multi2 & 1);
	m_check_multi3 = static_cast<bool>(d.allies >> s_multi3 & 1);
	m_check_multi4 = static_cast<bool>(d.allies >> s_multi4 & 1);
	m_check_multi5 = static_cast<bool>(d.allies >> s_multi5 & 1);
	m_check_multi6 = static_cast<bool>(d.allies >> s_multi6 & 1);
	m_edit_credits = d.credits;
	m_combo_edge.SelectString(-1, edge_code[d.edge]);
	UpdateData(false);

	return true;
}

void Cedit_side_dlg::OnOK() 
{
	if (!UpdateData(true))
		return;
	t_side_data& d = m_side_data;
	d.allies = 0;
	if (m_check_goodguy)
		d.allies |= 1 << s_goodguy;
	if (m_check_badguy)
		d.allies |= 1 << s_badguy;
	if (m_check_neutral)
		d.allies |= 1 << s_neutral;
	if (m_check_special)
		d.allies |= 1 << s_special;
	if (m_check_multi1)
		d.allies |= 1 << s_multi1;
	if (m_check_multi2)
		d.allies |= 1 << s_multi2;
	if (m_check_multi3)
		d.allies |= 1 << s_multi3;
	if (m_check_multi4)
		d.allies |= 1 << s_multi4;
	if (m_check_multi5)
		d.allies |= 1 << s_multi5;
	if (m_check_multi6)
		d.allies |= 1 << s_multi6;
	d.credits = m_edit_credits;
	d.edge = static_cast<t_edge_id>(m_combo_edge.GetItemData(m_combo_edge.GetCurSel()));

	CDialog::OnOK();
}
