#if !defined(AFX_DLG_EDIT_KEY_H__1B7664D5_1007_4DDA_AA83_1A5C70A2F19E__INCLUDED_)
#define AFX_DLG_EDIT_KEY_H__1B7664D5_1007_4DDA_AA83_1A5C70A2F19E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// dlg_edit_key.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cdlg_edit_key dialog

class Cdlg_edit_key : public ETSLayoutDialog
{
// Construction
public:
	void set_value(const string& v);
	void set_name(const string& v);
	string get_value();
	string get_name();
	Cdlg_edit_key(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cdlg_edit_key)
	enum { IDD = IDD_EDIT_KEY };
	CString	m_name;
	CString	m_value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cdlg_edit_key)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cdlg_edit_key)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_EDIT_KEY_H__1B7664D5_1007_4DDA_AA83_1A5C70A2F19E__INCLUDED_)
