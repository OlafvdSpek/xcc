#if !defined(AFX_DLG_EDIT_BIN32_H__07B5E8E2_2FE7_11D4_B605_0000B4936994__INCLUDED_)
#define AFX_DLG_EDIT_BIN32_H__07B5E8E2_2FE7_11D4_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// dlg_edit_bin32.h : header file
//

#include <string>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// Cdlg_edit_bin32 dialog

class Cdlg_edit_bin32 : public CDialog
{
// Construction
public:
	int get();
	void set(const string& key, int value);
	Cdlg_edit_bin32(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cdlg_edit_bin32)
	enum { IDD = IDD_EDIT_BIN32 };
	CString	m_key;
	CString	m_value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cdlg_edit_bin32)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cdlg_edit_bin32)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_EDIT_BIN32_H__07B5E8E2_2FE7_11D4_B605_0000B4936994__INCLUDED_)
