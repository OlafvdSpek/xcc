// options_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "XCC Mod Creator.h"
#include "options_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Coptions_dlg dialog


Coptions_dlg::Coptions_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Coptions_dlg::IDD, pParent)
{
	m_reg_key = "options_dlg";
	//{{AFX_DATA_INIT(Coptions_dlg)
	m_game = 1;
	m_link = _T("http://");
	m_link_title = _T("");
	m_mail = _T("");
	m_name = _T("");
	m_mod_name = _T("");
	//}}AFX_DATA_INIT
}


void Coptions_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Coptions_dlg)
	DDX_CBIndex(pDX, IDC_GAME, m_game);
	DDX_Text(pDX, IDC_LINK, m_link);
	DDX_Text(pDX, IDC_LINK_TITLE, m_link_title);
	DDX_Text(pDX, IDC_MAIL, m_mail);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_MOD_NAME, m_mod_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Coptions_dlg, CDialog)
	//{{AFX_MSG_MAP(Coptions_dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Coptions_dlg message handlers

Cxcc_mod::t_options Coptions_dlg::get() const
{
	Cxcc_mod::t_options r;
	r.name = m_name;
	r.mail = m_mail;
	r.link_title = m_link_title;
	r.link = m_link;
	r.mod_name = m_mod_name;
	switch (m_game)
	{
	case 0:
		r.game = game_ts;
		break;
	default:
		r.game = game_ra2;
	}
	return r;	
}

void Coptions_dlg::set(Cxcc_mod::t_options options)
{
	m_name = options.name.c_str();
	m_mail = options.mail.c_str();
	m_link_title = options.link_title.c_str();
	m_link = options.link.c_str();
	m_mod_name = options.mod_name.c_str();
	switch (options.game)
	{
	case game_ts:
		m_game = 0;
		break;
	default:
		m_game = 1;
	}
}
