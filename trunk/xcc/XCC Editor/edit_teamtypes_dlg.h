#if !defined(AFX_EDIT_TEAMTYPES_DLG_H__709DB463_1737_11D3_B601_A0454AC10154__INCLUDED_)
#define AFX_EDIT_TEAMTYPES_DLG_H__709DB463_1737_11D3_B601_A0454AC10154__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// edit_teamtypes_dlg.h : header file
//

#include "list_ctrl_extension.h"
#include "resource.h"
#include "string_conversion.h"
#include "xcc_infantry.h"
#include "xcc_level.h"
#include "xcc_structures.h"
#include "xcc_units.h"

/////////////////////////////////////////////////////////////////////////////
// Cedit_teamtypes_dlg dialog

class Cedit_teamtypes_dlg : public CDialog
{
// Construction
public:
	void update_controls();
	const string& get_selected_name() const;
	long get_index(const string& name) const;
	void update_teamtype(const string& name);
	void add_teamtype(const string& name);
	Cedit_teamtypes_dlg(Cxcc_level& level, bool selection_wanted = false);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cedit_teamtypes_dlg)
	enum { IDD = IDD_EDIT_TEAMTYPES_DLG };
	Clist_ctrl_extension	m_list;
	CButton	m_ok_button;
	CButton	m_edit_button;
	CButton	m_delete_button;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cedit_teamtypes_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cedit_teamtypes_dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNew();
	afx_msg void OnEdit();
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	Cxcc_level& m_level;
	t_teamtype_data& m_teamtype_data;
	string m_selected_name;
	const bool m_selection_wanted;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDIT_TEAMTYPES_DLG_H__709DB463_1737_11D3_B601_A0454AC10154__INCLUDED_)
