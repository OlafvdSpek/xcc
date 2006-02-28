#if !defined(AFX_XSTE_EDIT_DLG_H__539A77C0_C0B6_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XSTE_EDIT_DLG_H__539A77C0_C0B6_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// XSTE_edit_dlg.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CXSTE_edit_dlg dialog

class CXSTE_edit_dlg : public ETSLayoutDialog
{
// Construction
public:
	string get_name() const;
	string get_value() const;
	string get_extra_value() const;
	void set(const string& name, const string& value, const string& extra_value);
	CXSTE_edit_dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXSTE_edit_dlg)
	enum { IDD = IDD_XSTE_EDIT };
	CString	m_extra_value;
	CString	m_name;
	CString	m_value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXSTE_edit_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXSTE_edit_dlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XSTE_EDIT_DLG_H__539A77C0_C0B6_11D4_B606_0000B4936994__INCLUDED_)
