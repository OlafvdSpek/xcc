#if !defined(AFX_EDIT_WAYPOINTS_DLG_H__0900C285_152E_11D3_B601_304C4AC10154__INCLUDED_)
#define AFX_EDIT_WAYPOINTS_DLG_H__0900C285_152E_11D3_B601_304C4AC10154__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// edit_waypoints_dlg.h : header file
//

#include "list_ctrl_extension.h"
#include "resource.h"
#include "string_conversion.h"
#include "xcc_cell.h"
#include "xcc_level.h"

/////////////////////////////////////////////////////////////////////////////
// Cedit_waypoints_dlg dialog

class Cedit_waypoints_dlg: public ETSLayoutDialog
{
// Construction
public:
	long get_selected_i() const;
	Cedit_waypoints_dlg(Cxcc_level& level, bool selection_wanted = false);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cedit_waypoints_dlg)
	enum { IDD = IDD_EDIT_WAYPOINTS_DLG };
	CButton	m_delete_button;
	CButton	m_ok_button;
	Clist_ctrl_extension	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cedit_waypoints_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cedit_waypoints_dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelete();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_waypoint_data& m_waypoint_data;
	long m_selected_i;
	const bool m_selection_wanted;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDIT_WAYPOINTS_DLG_H__0900C285_152E_11D3_B601_304C4AC10154__INCLUDED_)
