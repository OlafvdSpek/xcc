#include "stdafx.h"
#include "DirectoriesDlg.h"

#include "xcc_dirs.h"

CDirectoriesDlg::CDirectoriesDlg(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(CDirectoriesDlg::IDD, pParent, "directories_dlg")
{
	//{{AFX_DATA_INIT(CDirectoriesDlg)
	m_edit_dune2 = xcc_dirs::get_dir(game_dune2).c_str();
	m_edit_td_primary = xcc_dirs::get_dir(game_td).c_str();
	m_edit_td_secondary = xcc_dirs::get_td_secondary_dir().c_str();
	m_edit_ra = xcc_dirs::get_dir(game_ra).c_str();
	m_edit_dune2000 = xcc_dirs::get_dir(game_dune2000).c_str();
	m_edit_ts = xcc_dirs::get_dir(game_ts).c_str();
	m_edit_ra2 = xcc_dirs::get_dir(game_ra2).c_str();
	m_edit_cd = xcc_dirs::get_cd_dir().c_str();
	m_edit_data = xcc_dirs::get_data_dir().c_str();
	//}}AFX_DATA_INIT
}

void CDirectoriesDlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
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

BEGIN_MESSAGE_MAP(CDirectoriesDlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(CDirectoriesDlg)
	ON_BN_CLICKED(IDC_RESET_CD, OnResetCd)
	ON_BN_CLICKED(IDC_RESET_DATA, OnResetData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDirectoriesDlg::OnOK() 
{
	ETSLayoutDialog::OnOK();
	xcc_dirs::set_dir(game_dune2, static_cast<string>(m_edit_dune2));
	xcc_dirs::set_dir(game_td, static_cast<string>(m_edit_td_primary));
	xcc_dirs::set_td_secondary_dir(static_cast<string>(m_edit_td_secondary));
	xcc_dirs::set_dir(game_ra, static_cast<string>(m_edit_ra));
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

BOOL CDirectoriesDlg::OnInitDialog() 
{
	ETSLayoutDialog::OnInitDialog();
	CreateRoot(HORIZONTAL)
		<< (pane(VERTICAL, ABSOLUTE_VERT)
			<< item(IDC_DUNE2_STATIC, NORESIZE)
			<< item(IDC_TD_PRIMARY_STATIC, NORESIZE)
			<< item(IDC_TD_SECONDARY_STATIC, NORESIZE)
			<< item(IDC_RA_STATIC, NORESIZE)
			<< item(IDC_DUNE2000_STATIC, NORESIZE)
			<< item(IDC_TS_STATIC, NORESIZE)
			<< item(IDC_RA2_STATIC, NORESIZE)
			<< item(IDC_DATA_STATIC, NORESIZE)
			<< item(IDC_CD_STATIC, NORESIZE)
			)
		<< (pane(VERTICAL, ABSOLUTE_VERT)
			<< item(IDC_DUNE2, ABSOLUTE_VERT)
			<< item(IDC_TD_PRIMARY, ABSOLUTE_VERT)
			<< item(IDC_TD_SECONDARY, ABSOLUTE_VERT)
			<< item(IDC_RA, ABSOLUTE_VERT)
			<< item(IDC_DUNE2000, ABSOLUTE_VERT)
			<< item(IDC_TS, ABSOLUTE_VERT)
			<< item(IDC_RA2, ABSOLUTE_VERT)
			<< item(IDC_DATA, ABSOLUTE_VERT)
			<< item(IDC_CD, ABSOLUTE_VERT)
			)
		<< (pane(VERTICAL, ABSOLUTE_VERT)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			<< itemGrowing(VERTICAL)
			<< item(IDC_RESET_DATA, NORESIZE)
			<< item(IDC_RESET_CD, NORESIZE)
			);
	UpdateLayout();
	return true;
}
