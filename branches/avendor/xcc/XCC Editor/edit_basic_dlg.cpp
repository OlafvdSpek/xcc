// edit_basic_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "xcc editor.h"
#include "edit_basic_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cedit_basic_dlg dialog


Cedit_basic_dlg::Cedit_basic_dlg(Cxcc_level& level)
	: CDialog(Cedit_basic_dlg::IDD, 0),
	m_basic_data(level.basic_data)
{
	//{{AFX_DATA_INIT(Cedit_basic_dlg)
	m_edit_buildlevel = 0;
	m_edit_percent = 0;
	m_edit_carry_over_money = 0;
	//}}AFX_DATA_INIT
}


void Cedit_basic_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cedit_basic_dlg)
	DDX_Control(pDX, IDC_COMBO_PLAYER, m_combo_player);
	DDX_Text(pDX, IDC_EDIT_ACTION, m_edit_action);
	DDX_Text(pDX, IDC_EDIT_BRIEF, m_edit_brief);
	DDX_Text(pDX, IDC_EDIT_BUILDLEVEL, m_edit_buildlevel);
	DDV_MinMaxLong(pDX, m_edit_buildlevel, 0, 99);
	DDX_Text(pDX, IDC_EDIT_INTRO, m_edit_intro);
	DDX_Text(pDX, IDC_EDIT_LOSE, m_edit_lose);
	DDX_Text(pDX, IDC_EDIT_PERCENT, m_edit_percent);
	DDV_MinMaxLong(pDX, m_edit_percent, 0, 100);
	DDX_Text(pDX, IDC_EDIT_THEME, m_edit_theme);
	DDX_Text(pDX, IDC_EDIT_WIN, m_edit_win);
	DDX_Text(pDX, IDC_EDIT_CARRY_OVER_MONEY, m_edit_carry_over_money);
	DDV_MinMaxLong(pDX, m_edit_carry_over_money, 0, 1000000);
	DDX_Text(pDX, IDC_EDIT_NAME, m_edit_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cedit_basic_dlg, CDialog)
	//{{AFX_MSG_MAP(Cedit_basic_dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cedit_basic_dlg message handlers

BOOL Cedit_basic_dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	for (long i = 0; i < c_side_id; i++)
	{
		m_combo_player.SetItemData(m_combo_player.AddString(side_code[i]), i);
	}

	m_edit_action = m_basic_data.action.c_str();
	m_edit_brief = m_basic_data.brief.c_str();
	m_edit_buildlevel = m_basic_data.build_level;
	m_edit_carry_over_money = m_basic_data.carry_over_money;
	m_edit_intro = m_basic_data.intro.c_str();
	m_edit_lose = m_basic_data.lose.c_str();
	m_edit_name = m_basic_data.name.c_str();
	m_edit_percent = m_basic_data.percent;
	m_combo_player.SelectString(-1, side_code[m_basic_data.player]);
	m_edit_theme = m_basic_data.theme.c_str();
	m_edit_win = m_basic_data.win.c_str();
	UpdateData(false);

	return true;
}

void Cedit_basic_dlg::OnOK() 
{
	if (!UpdateData(true))
		return;
	m_basic_data.action = m_edit_action;
	m_basic_data.brief = m_edit_brief;
	m_basic_data.build_level = m_edit_buildlevel;
	m_basic_data.carry_over_money = m_edit_carry_over_money;
	m_basic_data.intro = m_edit_intro;
	m_basic_data.lose = m_edit_lose;
	m_basic_data.name = m_edit_name;
	m_basic_data.percent = m_edit_percent;
	m_basic_data.player = static_cast<t_side_id>(m_combo_player.GetItemData(m_combo_player.GetCurSel()));
	m_basic_data.theme = m_edit_theme;
	m_basic_data.win = m_edit_win;
	CDialog::OnOK();
}
