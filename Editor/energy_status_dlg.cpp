#include "stdafx.h"
#include "energy_status_dlg.h"

#include "xcc_structures.h"

Cenergy_status_dlg::Cenergy_status_dlg(const Cxcc_level& level)
	: CDialog(Cenergy_status_dlg::IDD, 0),
	m_level(level)
{
	//{{AFX_DATA_INIT(Cenergy_status_dlg)
	//}}AFX_DATA_INIT
	for (int i = 0; i < c_side_id; i++)
		m_power_in[i] = m_power_out[i] = 0;
	for (auto& i : m_level.structure_data)
	{
		m_power_in[i.side] += i.t->power_out;
		m_power_out[i.side] += i.t->power_in;
	}
}

void Cenergy_status_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cenergy_status_dlg)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_BADGUY_IN, m_power_in[s_badguy]);
	DDX_Text(pDX, IDC_EDIT_BADGUY_OUT, m_power_out[s_badguy]);
	DDX_Text(pDX, IDC_EDIT_GOODGUY_IN, m_power_in[s_goodguy]);
	DDX_Text(pDX, IDC_EDIT_GOODGUY_OUT, m_power_out[s_goodguy]);
	DDX_Text(pDX, IDC_EDIT_MULTI1_IN, m_power_in[s_multi1]);
	DDX_Text(pDX, IDC_EDIT_MULTI1_OUT, m_power_out[s_multi1]);
	DDX_Text(pDX, IDC_EDIT_MULTI2_IN, m_power_in[s_multi2]);
	DDX_Text(pDX, IDC_EDIT_MULTI2_OUT, m_power_out[s_multi2]);
	DDX_Text(pDX, IDC_EDIT_MULTI3_IN, m_power_in[s_multi3]);
	DDX_Text(pDX, IDC_EDIT_MULTI3_OUT, m_power_out[s_multi3]);
	DDX_Text(pDX, IDC_EDIT_MULTI4_IN, m_power_in[s_multi4]);
	DDX_Text(pDX, IDC_EDIT_MULTI4_OUT, m_power_out[s_multi4]);
	DDX_Text(pDX, IDC_EDIT_MULTI5_IN, m_power_in[s_multi5]);
	DDX_Text(pDX, IDC_EDIT_MULTI5_OUT, m_power_out[s_multi5]);
	DDX_Text(pDX, IDC_EDIT_MULTI6_IN, m_power_in[s_multi6]);
	DDX_Text(pDX, IDC_EDIT_MULTI6_OUT, m_power_out[s_multi6]);
	DDX_Text(pDX, IDC_EDIT_NEUTRAL_IN, m_power_in[s_neutral]);
	DDX_Text(pDX, IDC_EDIT_NEUTRAL_OUT, m_power_out[s_neutral]);
	DDX_Text(pDX, IDC_EDIT_SPECIAL_IN, m_power_in[s_special]);
	DDX_Text(pDX, IDC_EDIT_SPECIAL_OUT, m_power_out[s_special]);
}

BEGIN_MESSAGE_MAP(Cenergy_status_dlg, CDialog)
	//{{AFX_MSG_MAP(Cenergy_status_dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
