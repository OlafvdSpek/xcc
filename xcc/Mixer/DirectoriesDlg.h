#pragma once

#include "resource.h"

class CDirectoriesDlg: public ETSLayoutDialog
{
// Construction
public:
	CDirectoriesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDirectoriesDlg)
	enum { IDD = IDD_DIRECTORIES };
	CString	m_edit_dune2;
	CString	m_edit_dune2000;
	CString	m_edit_ra2;
	CString	m_edit_ra;
	CString	m_edit_td_primary;
	CString	m_edit_td_secondary;
	CString	m_edit_ts;
	CString	m_edit_cd;
	CString	m_edit_data;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectoriesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDirectoriesDlg)
	virtual void OnOK();
	afx_msg void OnResetCd();
	afx_msg void OnResetData();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
