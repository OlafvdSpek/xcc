#include "stdafx.h"
#include "edit_map_dlg.h"

Cedit_map_dlg::Cedit_map_dlg(Cxcc_level& level)
	: CDialog(Cedit_map_dlg::IDD, 0),
	m_map_data(level.map_data)
{
	//{{AFX_DATA_INIT(Cedit_map_dlg)
	m_edit_cx = 0;
	m_edit_x = 0;
	m_edit_y = 0;
	m_edit_cy = 0;
	//}}AFX_DATA_INIT
}

void Cedit_map_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cedit_map_dlg)
	DDX_Control(pDX, IDC_COMBO_THEATER, m_combo_theater);
	DDX_Text(pDX, IDC_EDIT_CX, m_edit_cx);
	DDV_MinMaxLong(pDX, m_edit_cx, 1, 62);
	DDX_Text(pDX, IDC_EDIT_X, m_edit_x);
	DDV_MinMaxLong(pDX, m_edit_x, 1, 62);
	DDX_Text(pDX, IDC_EDIT_Y, m_edit_y);
	DDV_MinMaxLong(pDX, m_edit_y, 1, 62);
	DDX_Text(pDX, IDC_EDIT_CY, m_edit_cy);
	DDV_MinMaxLong(pDX, m_edit_cy, 1, 62);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Cedit_map_dlg, CDialog)
	//{{AFX_MSG_MAP(Cedit_map_dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL Cedit_map_dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	for (long i = 0; i < c_theater_id; i++)
	{
		m_combo_theater.SetItemData(m_combo_theater.AddString(theater_code[i]), i);
	}

	m_edit_x = m_map_data.x;
	m_edit_y = m_map_data.y;
	m_edit_cx = m_map_data.cx;
	m_edit_cy = m_map_data.cy;
	m_combo_theater.SelectString(-1, theater_code[m_map_data.theater]);
	UpdateData(false);

	return true;
}

void Cedit_map_dlg::OnOK() 
{
	if (!UpdateData(true))
		return;
	m_map_data.x = m_edit_x;
	m_map_data.y = m_edit_y;
	m_map_data.cx = m_edit_cx;
	m_map_data.cy = m_edit_cy;
	m_map_data.theater = static_cast<t_theater_id>(m_combo_theater.GetItemData(m_combo_theater.GetCurSel()));
	CDialog::OnOK();
}
