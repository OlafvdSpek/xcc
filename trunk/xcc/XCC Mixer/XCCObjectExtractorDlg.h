#if !defined(AFX_XCCOBJECTEXTRACTORDLG_H__4CA2DE60_9007_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XCCOBJECTEXTRACTORDLG_H__4CA2DE60_9007_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// XCCObjectExtractorDlg.h : header file
//

#include "ListCtrlEx.h"
#include "extract_object.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CXCCObjectExtractorDlg dialog

class CXCCObjectExtractorDlg : public ETSLayoutDialog
{
// Construction
public:
	void add(int j, string name);
	void set_extract_to_dir(const string& v);
	CXCCObjectExtractorDlg(t_game game, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXCCObjectExtractorDlg)
	enum { IDD = IDD_XCC_OBJECT_EXTRACTOR };
	CListCtrlEx	m_list;
	CString	m_link;
	CString	m_link_title;
	CString	m_mail;
	CString	m_name;
	CString	m_extract_to_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCObjectExtractorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
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

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCOBJECTEXTRACTORDLG_H__4CA2DE60_9007_11D4_B606_0000B4936994__INCLUDED_)
