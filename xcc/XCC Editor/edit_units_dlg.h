#if !defined(AFX_EDIT_UNITS_DLG_H__82448C23_0DD2_11D3_B601_B04A4AC10154__INCLUDED_)
#define AFX_EDIT_UNITS_DLG_H__82448C23_0DD2_11D3_B601_B04A4AC10154__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "list_ctrl_extension.h"
#include "string_conversion.h"
#include "xcc_units.h"

// edit_units_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cedit_units_dlg dialog

class Cedit_units_dlg : public CDialog
{
// Construction
public:
	void load_controls();
	void save_controls();
	void update_controls();
	void add_item(long i);
	void update_item(long i);
	Cedit_units_dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cedit_units_dlg)
	enum { IDD = IDD_EDIT_UNITS_DLG };
	CEdit	m_editctrl_c_rotations;
	CEdit	m_editctrl_c_images;
	CEdit	m_editctrl_base_oy;
	CEdit	m_editctrl_base_ox;
	CEdit	m_editctrl_long_name;
	CEdit	m_editctrl_short_name;
	CEdit	m_editctrl_flags;
	Clist_ctrl_extension	m_list;
	CString	m_edit_long_name;
	CString	m_edit_short_name;
	CString	m_edit_size;
	BOOL	m_check_icon;
	DWORD	m_edit_flags;
	long	m_edit_base_ox;
	long	m_edit_base_oy;
	DWORD	m_edit_c_rotations;
	DWORD	m_edit_c_images;
	BOOL	m_check_top;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cedit_units_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cedit_units_dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNewButton();
	afx_msg void OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long m_current_i;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDIT_UNITS_DLG_H__82448C23_0DD2_11D3_B601_B04A4AC10154__INCLUDED_)
