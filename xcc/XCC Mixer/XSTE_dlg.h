#if !defined(AFX_XSTE_DLG_H__327575A8_BFED_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XSTE_DLG_H__327575A8_BFED_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// XSTE_dlg.h : header file
//

#include "csf_file.h"

/////////////////////////////////////////////////////////////////////////////
// CXSTE_dlg dialog

class CXSTE_dlg : public ETSLayoutDialog
{
// Construction
public:
	void sort_list(int i);
	int get_current_index();
	int insert(const string& name);
	void check_selection();
	int compare(int id_a, int id_b) const;
	CXSTE_dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXSTE_dlg)
	enum { IDD = IDD_XSTE };
	CButton	m_insert;
	CButton	m_edit;
	CButton	m_delete;
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXSTE_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXSTE_dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnEdit();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInsert();
	afx_msg void OnDelete();
	afx_msg void OnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	string m_buffer[4];
	int m_buffer_w;
	Ccsf_file m_f;
	int m_sort_column;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XSTE_DLG_H__327575A8_BFED_11D4_B606_0000B4936994__INCLUDED_)
