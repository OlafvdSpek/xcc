#if !defined(AFX_XCCSETDIRECTORIESDLG_H__F73FDA42_E161_11D2_B750_D7BC1EFADD65__INCLUDED_)
#define AFX_XCCSETDIRECTORIESDLG_H__F73FDA42_E161_11D2_B750_D7BC1EFADD65__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// XCCSetDirectoriesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXCCSetDirectoriesDlg dialog

class CXCCSetDirectoriesDlg : public CDialog
{
// Construction
public:
	CXCCSetDirectoriesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXCCSetDirectoriesDlg)
	enum { IDD = IDD_XCCDIRECTORIES };
	CString	m_dir1;
	CString	m_dir2;
	CString	m_cd_dir;
	CString	m_data_dir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCSetDirectoriesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXCCSetDirectoriesDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCSETDIRECTORIESDLG_H__F73FDA42_E161_11D2_B750_D7BC1EFADD65__INCLUDED_)
