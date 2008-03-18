#include "stdafx.h"
#include "edit_briefing_dlg.h"

Cedit_briefing_dlg::Cedit_briefing_dlg(Cxcc_level& level)
	: CDialog(Cedit_briefing_dlg::IDD, 0),
	m_briefing_data(level.briefing_data)
{
	//{{AFX_DATA_INIT(Cedit_briefing_dlg)
	//}}AFX_DATA_INIT
}

void Cedit_briefing_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cedit_briefing_dlg)
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Cedit_briefing_dlg, CDialog)
	//{{AFX_MSG_MAP(Cedit_briefing_dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL Cedit_briefing_dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_edit = m_briefing_data.c_str();
	UpdateData(false);
	
	return true;
}

void Cedit_briefing_dlg::OnOK() 
{
	if (!UpdateData(true))
		return;
	m_briefing_data = m_edit;
	CDialog::OnOK();
}
