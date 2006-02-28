// options_dlg.cpp : implementation file
//

#include "stdafx.h"
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
	m_link = _T("");
	m_link_title = _T("");
	m_mail = _T("");
	m_name = _T("");
	m_mod_name = _T("");
	m_ini_diff_compression = FALSE;
	m_csf_diff_compression = FALSE;
	m_exit_button = FALSE;
	m_manual_button = FALSE;
	m_site_button = FALSE;
	m_xhp_button = FALSE;
	m_custom_button_text = FALSE;
	m_mod_ucf = _T("");
	m_mod_version = _T("");
	m_update_button = FALSE;
	m_shp_compression = FALSE;
	m_vxl_compression = FALSE;
	m_mod_mfs = _T("");
	m_deactivate = -1;
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
	DDX_Check(pDX, IDC_INI_DIFF_COMPRESSION, m_ini_diff_compression);
	DDX_Check(pDX, IDC_CSF_DIFF_COMPRESSION, m_csf_diff_compression);
	DDX_Check(pDX, IDC_EXIT_BUTTON, m_exit_button);
	DDX_Check(pDX, IDC_MANUAL_BUTTON, m_manual_button);
	DDX_Check(pDX, IDC_SITE_BUTTON, m_site_button);
	DDX_Check(pDX, IDC_XHP_BUTTON, m_xhp_button);
	DDX_Check(pDX, IDC_CUSTOM_BUTTON_TEXT, m_custom_button_text);
	DDX_Text(pDX, IDC_MOD_UCF, m_mod_ucf);
	DDX_Text(pDX, IDC_MOD_VERSION, m_mod_version);
	DDX_Check(pDX, IDC_UPDATE_BUTTON, m_update_button);
	DDX_Check(pDX, IDC_SHP_COMPRESSION, m_shp_compression);
	DDX_Check(pDX, IDC_VXL_COMPRESSION, m_vxl_compression);
	DDX_Text(pDX, IDC_MOD_MFS, m_mod_mfs);
	DDX_CBIndex(pDX, IDC_DEACTIVATE, m_deactivate);
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
	case 2:
		r.game = game_ra2_yr;
		break;
	default:
		r.game = game_ra2;
	}
	r.csf_diff_compression = m_csf_diff_compression;
	r.ini_diff_compression = m_ini_diff_compression;
	r.shp_compression = m_shp_compression;
	r.vxl_compression = m_vxl_compression;
	r.custom_button_text = m_custom_button_text;
	r.xhp_button = m_xhp_button;
	r.exit_button = m_exit_button;
	r.update_button = m_update_button;
	r.manual_button = m_manual_button;
	r.site_button = m_site_button;
	r.mod_version = m_mod_version;
	r.mod_ucf = m_mod_ucf;
	r.deactivate = m_deactivate;
	r.mod_mfs = m_mod_mfs;
	// r.@ = m_@;
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
	case game_ra2_yr:
		m_game = 2;
		break;
	default:
		m_game = 1;
	}
	m_csf_diff_compression = options.csf_diff_compression;
	m_ini_diff_compression = options.ini_diff_compression;
	m_shp_compression = options.shp_compression;
	m_vxl_compression = options.vxl_compression;
	m_custom_button_text= options.custom_button_text;
	m_xhp_button = options.xhp_button;
	m_exit_button = options.exit_button;
	m_update_button = options.update_button;
	m_manual_button = options.manual_button;
	m_site_button = options.site_button;
	m_mod_version = options.mod_version.c_str();
	m_mod_ucf = options.mod_ucf.c_str();
	m_deactivate = options.deactivate;
	m_mod_mfs = options.mod_mfs.c_str();
}
