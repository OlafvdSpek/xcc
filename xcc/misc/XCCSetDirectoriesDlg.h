#pragma once

class CXCCSetDirectoriesDlg : public CDialog
{
public:
	CXCCSetDirectoriesDlg(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CXCCSetDirectoriesDlg)
	enum { IDD = IDD_XCCDIRECTORIES };
	CString	m_dir1;
	CString	m_dir2;
	CString	m_cd_dir;
	CString	m_data_dir;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CXCCSetDirectoriesDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//{{AFX_MSG(CXCCSetDirectoriesDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
