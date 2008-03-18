#pragma once

#include "resource.h"

class CXSTE_edit_dlg : public ETSLayoutDialog
{
public:
	string get_name() const;
	string get_value() const;
	string get_extra_value() const;
	void set(const string& name, const string& value, const string& extra_value);
	CXSTE_edit_dlg(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CXSTE_edit_dlg)
	enum { IDD = IDD_XSTE_EDIT };
	CString	m_extra_value;
	CString	m_name;
	CString	m_value;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CXSTE_edit_dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXSTE_edit_dlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
