#if !defined(AFX_SEARCHSTRINGDLG_H__AAAA3B3C_53F5_4C71_B6E3_36BA1DB487C2__INCLUDED_)
#define AFX_SEARCHSTRINGDLG_H__AAAA3B3C_53F5_4C71_B6E3_36BA1DB487C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SearchStringDlg.h : header file
//

#include "csf_file.h"

/////////////////////////////////////////////////////////////////////////////
// CSearchStringDlg dialog

class CSearchStringDlg : public ETSLayoutDialog
{
// Construction
public:
	void set(const Ccsf_file* csf);
	CSearchStringDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchStringDlg)
	enum { IDD = IDD_SEARCH_STRING };
	CListCtrl	m_list;
	static CString	m_name;
	//}}AFX_DATA

	string m_selected;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchStringDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchStringDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSearch();
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	const Ccsf_file* m_csf;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHSTRINGDLG_H__AAAA3B3C_53F5_4C71_B6E3_36BA1DB487C2__INCLUDED_)
