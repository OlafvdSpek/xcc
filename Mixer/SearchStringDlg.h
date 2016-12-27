#pragma once

#include "ListCtrlEx.h"
#include "csf_file.h"
#include "resource.h"

class CSearchStringDlg : public ETSLayoutDialog
{
public:
	void set(const Ccsf_file* csf);
	CSearchStringDlg(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CSearchStringDlg)
	enum { IDD = IDD_SEARCH_STRING };
	CListCtrlEx	m_list;
	static CString	m_name;
	//}}AFX_DATA

	string m_selected;

	//{{AFX_VIRTUAL(CSearchStringDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(CSearchStringDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSearch();
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	const Ccsf_file* m_csf;
};
