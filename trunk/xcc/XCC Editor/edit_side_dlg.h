#if !defined(AFX_EDIT_SIDE_DLG_H__FD404EE3_17A1_11D3_B601_50494AC10154__INCLUDED_)
#define AFX_EDIT_SIDE_DLG_H__FD404EE3_17A1_11D3_B601_50494AC10154__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// edit_side_dlg.h : header file
//

#include "resource.h"
#include "xcc_level.h"

/////////////////////////////////////////////////////////////////////////////
// Cedit_side_dlg dialog

class Cedit_side_dlg : public CDialog
{
// Construction
public:
	Cedit_side_dlg(t_side_data& side_data);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cedit_side_dlg)
	enum { IDD = IDD_EDIT_SIDE_DLG };
	CComboBox	m_combo_edge;
	BOOL	m_check_badguy;
	BOOL	m_check_goodguy;
	BOOL	m_check_multi1;
	BOOL	m_check_multi2;
	BOOL	m_check_multi3;
	BOOL	m_check_multi4;
	BOOL	m_check_multi5;
	BOOL	m_check_multi6;
	BOOL	m_check_special;
	long	m_edit_credits;
	BOOL	m_check_neutral;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cedit_side_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cedit_side_dlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_side_data& m_side_data;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDIT_SIDE_DLG_H__FD404EE3_17A1_11D3_B601_50494AC10154__INCLUDED_)
