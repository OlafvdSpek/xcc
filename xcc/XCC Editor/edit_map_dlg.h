#if !defined(AFX_EDIT_MAP_DLG_H__FD404EE2_17A1_11D3_B601_50494AC10154__INCLUDED_)
#define AFX_EDIT_MAP_DLG_H__FD404EE2_17A1_11D3_B601_50494AC10154__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// edit_map_dlg.h : header file
//

#include "resource.h"
#include "xcc_level.h"

/////////////////////////////////////////////////////////////////////////////
// Cedit_map_dlg dialog

class Cedit_map_dlg : public CDialog
{
// Construction
public:
	Cedit_map_dlg(Cxcc_level& level);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cedit_map_dlg)
	enum { IDD = IDD_EDIT_MAP_DLG };
	CComboBox	m_combo_theater;
	long	m_edit_cx;
	long	m_edit_x;
	long	m_edit_y;
	long	m_edit_cy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cedit_map_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cedit_map_dlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_map_data& m_map_data;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDIT_MAP_DLG_H__FD404EE2_17A1_11D3_B601_50494AC10154__INCLUDED_)
