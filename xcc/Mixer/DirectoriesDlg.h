// DirectoriesDlg.h : header file
//

#if !defined(AFX_DIRECTORIESDLG_H__0CCE0901_55C3_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_DIRECTORIESDLG_H__0CCE0901_55C3_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDirectoriesDlg dialog

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

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTORIESDLG_H__0CCE0901_55C3_11D4_B606_0000B4936994__INCLUDED_)
