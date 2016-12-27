#pragma once

#include "ListCtrlEx.h"
#include "extract_object.h"
#include "resource.h"

class CXCCObjectExtractorDlg : public ETSLayoutDialog
{
public:
	void add(int j, string name);
	void set_extract_to_dir(const string& v);
	CXCCObjectExtractorDlg(t_game game, CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CXCCObjectExtractorDlg)
	enum { IDD = IDD_XCC_OBJECT_EXTRACTOR };
	CListCtrlEx	m_list;
	CString	m_link;
	CString	m_link_title;
	CString	m_mail;
	CString	m_name;
	CString	m_extract_to_edit;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CXCCObjectExtractorDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXCCObjectExtractorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnExtract();
	afx_msg void OnExtractToButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_game m_game;
	Cextract_object m_extract_object;
	CString m_reg_key;
};
