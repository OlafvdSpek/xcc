// DirectoriesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DirectoriesDlg.h"

#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirectoriesDlg dialog


CDirectoriesDlg::CDirectoriesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDirectoriesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDirectoriesDlg)
	m_edit_dune2 = xcc_dirs::get_dune2_dir().c_str();
	m_edit_td_primary = xcc_dirs::get_td_primary_dir().c_str();
	m_edit_td_secondary = xcc_dirs::get_td_secondary_dir().c_str();
	m_edit_ra = xcc_dirs::get_ra_dir().c_str();
	m_edit_dune2000 = xcc_dirs::get_dune2000_dir().c_str();
	m_edit_ts = xcc_dirs::get_ts_dir().c_str();
	m_edit_ra2 = xcc_dirs::get_ra2_dir().c_str();
	m_edit_cd = xcc_dirs::get_cd_dir().c_str();
	m_edit_data = xcc_dirs::get_data_dir().c_str();
	//}}AFX_DATA_INIT
}


void CDirectoriesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirectoriesDlg)
	DDX_Text(pDX, IDC_DUNE2, m_edit_dune2);
	DDX_Text(pDX, IDC_DUNE2000, m_edit_dune2000);
	DDX_Text(pDX, IDC_RA2, m_edit_ra2);
	DDX_Text(pDX, IDC_RA, m_edit_ra);
	DDX_Text(pDX, IDC_TD_PRIMARY, m_edit_td_primary);
	DDX_Text(pDX, IDC_TD_SECONDARY, m_edit_td_secondary);
	DDX_Text(pDX, IDC_TS, m_edit_ts);
	DDX_Text(pDX, IDC_CD, m_edit_cd);
	DDX_Text(pDX, IDC_DATA, m_edit_data);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDirectoriesDlg, CDialog)
	//{{AFX_MSG_MAP(CDirectoriesDlg)
	ON_BN_CLICKED(IDC_RESET_CD, OnResetCd)
	ON_BN_CLICKED(IDC_RESET_DATA, OnResetData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectoriesDlg message handlers

void CDirectoriesDlg::OnOK() 
{
	CDialog::OnOK();
	xcc_dirs::set_dune2_dir(static_cast<string>(m_edit_dune2));
	xcc_dirs::set_td_primary_dir(static_cast<string>(m_edit_td_primary));
	xcc_dirs::set_td_secondary_dir(static_cast<string>(m_edit_td_secondary));
	xcc_dirs::set_ra_dir(static_cast<string>(m_edit_ra));
	xcc_dirs::set_dune2000_dir(static_cast<string>(m_edit_dune2000));
	xcc_dirs::set_ts_dir(static_cast<string>(m_edit_ts));
	xcc_dirs::set_ra2_dir(static_cast<string>(m_edit_ra2));
	xcc_dirs::set_data_dir(static_cast<string>(m_edit_data));
	xcc_dirs::set_cd_dir(static_cast<string>(m_edit_cd));
}

void CDirectoriesDlg::OnResetCd() 
{
	UpdateData(true);
	xcc_dirs::reset_cd_dir();
	m_edit_cd = xcc_dirs::get_cd_dir().c_str();
	UpdateData(false);
}

void CDirectoriesDlg::OnResetData() 
{
	UpdateData(true);
	xcc_dirs::reset_data_dir();
	m_edit_data = xcc_dirs::get_data_dir().c_str();
	UpdateData(false);
}
