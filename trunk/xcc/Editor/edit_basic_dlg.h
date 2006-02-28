#if !defined(AFX_EDIT_BASIC_DLG_H__57592383_1792_11D3_B601_50494AC10154__INCLUDED_)
#define AFX_EDIT_BASIC_DLG_H__57592383_1792_11D3_B601_50494AC10154__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// edit_basic_dlg.h : header file
//

#include "resource.h"
#include "xcc_level.h"

/////////////////////////////////////////////////////////////////////////////
// Cedit_basic_dlg dialog

class Cedit_basic_dlg : public CDialog
{
// Construction
public:
	Cedit_basic_dlg(Cxcc_level& level);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cedit_basic_dlg)
	enum { IDD = IDD_EDIT_BASIC_DLG };
	CComboBox	m_combo_player;
	CString	m_edit_action;
	CString	m_edit_brief;
	long	m_edit_buildlevel;
	CString	m_edit_intro;
	CString	m_edit_lose;
	long	m_edit_percent;
	CString	m_edit_theme;
	CString	m_edit_win;
	long	m_edit_carry_over_money;
	CString	m_edit_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cedit_basic_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cedit_basic_dlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_basic_data& m_basic_data;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDIT_BASIC_DLG_H__57592383_1792_11D3_B601_50494AC10154__INCLUDED_)
