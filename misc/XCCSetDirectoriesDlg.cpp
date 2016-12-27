#include "stdafx.h"
#include "XCCSetDirectoriesDlg.h"

#include "resource.h"
#include "xcc_dirs.h"

CXCCSetDirectoriesDlg::CXCCSetDirectoriesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXCCSetDirectoriesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXCCSetDirectoriesDlg)
	m_dir1 = xcc_dirs::get_td_primary_dir().c_str();
	m_dir2 = xcc_dirs::get_td_secondary_dir().c_str();
	m_cd_dir = xcc_dirs::get_cd_dir().c_str();
	m_data_dir = xcc_dirs::get_data_dir().c_str();
	//}}AFX_DATA_INIT
}


void CXCCSetDirectoriesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCSetDirectoriesDlg)
	DDX_Text(pDX, IDC_EDIT_PRIMARY, m_dir1);
	DDX_Text(pDX, IDC_EDIT_SECONDARY, m_dir2);
	DDX_Text(pDX, IDC_EDIT_CD, m_cd_dir);
	DDX_Text(pDX, IDC_EDIT_DATA, m_data_dir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXCCSetDirectoriesDlg, CDialog)
	//{{AFX_MSG_MAP(CXCCSetDirectoriesDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CXCCSetDirectoriesDlg::OnOK() 
{
	UpdateData(true);
	string s;
	xcc_dirs::set_td_primary_dir(s = m_dir1);
	xcc_dirs::set_td_secondary_dir(s = m_dir2);
	xcc_dirs::set_cd_dir(s = m_cd_dir);
	xcc_dirs::set_data_dir(s = m_data_dir);
	CDialog::OnOK();
}
