#if !defined(AFX_EDIT_INFANTRY_DLG_H__75B5F141_0E10_11D3_B601_B04A4AC10154__INCLUDED_)
#define AFX_EDIT_INFANTRY_DLG_H__75B5F141_0E10_11D3_B601_B04A4AC10154__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// edit_infantry_dlg.h : header file
//

#include "list_ctrl_extension.h"
#include "resource.h"
#include "string_conversion.h"
#include "xcc_infantry.h"

/////////////////////////////////////////////////////////////////////////////
// Cedit_infantry_dlg dialog

class Cedit_infantry_dlg : public CDialog
{
// Construction
public:
	void load_controls();
	void save_controls();
	void update_controls();
	void add_item(long i);
	void update_item(long i);
	Cedit_infantry_dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cedit_infantry_dlg)
	enum { IDD = IDD_EDIT_INFANTRY_DLG };
	CEdit	m_editctrl_oy;
	CEdit	m_editctrl_ox;
	CEdit	m_editctrl_short_name;
	CEdit	m_editctrl_long_name;
	CEdit	m_editctrl_flags;
	Clist_ctrl_extension	m_list;
	BOOL	m_check_civilian;
	BOOL	m_check_icon;
	CString	m_edit_long_name;
	CString	m_edit_short_name;
	CString	m_edit_size;
	long	m_edit_ox;
	long	m_edit_oy;
	DWORD	m_edit_flags;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cedit_infantry_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cedit_infantry_dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNewButton();
	virtual void OnOK();
	afx_msg void OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long m_current_i;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDIT_INFANTRY_DLG_H__75B5F141_0E10_11D3_B601_B04A4AC10154__INCLUDED_)
