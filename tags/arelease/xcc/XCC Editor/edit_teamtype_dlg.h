#if !defined(AFX_EDIT_TEAMTYPE_DLG_H__2E101121_174A_11D3_B601_A0454AC10154__INCLUDED_)
#define AFX_EDIT_TEAMTYPE_DLG_H__2E101121_174A_11D3_B601_A0454AC10154__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <string>
#include "xcc_level.h"

using namespace std;

// edit_teamtype_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cedit_teamtype_dlg dialog

class Cedit_teamtype_dlg : public CDialog
{
// Construction
public:
	void add_object(int i);
	void add_action(int i);
	int get_selected_object_i();
	int get_selected_action_i();
	void load(const string& name);
	void save(string& name) const;
	Cedit_teamtype_dlg(Cxcc_level& level);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cedit_teamtype_dlg)
	enum { IDD = IDD_EDIT_TEAMTYPE_DLG };
	CButton	m_action_insert_button;
	CButton	m_object_insert_button;
	CButton	m_object_delete_button;
	CButton	m_action_delete_button;
	CListBox	m_list_object;
	CListBox	m_list_action;
	CComboBox	m_combo_side;
	CComboBox	m_combo_object;
	CComboBox	m_combo_action;
	CString	m_edit_name;
	int	m_edit_c_teams;
	int	m_edit_object;
	int	m_edit_action;
	BOOL	m_check_autocreate;
	BOOL	m_check_force_creation;
	BOOL	m_check_force_move;
	BOOL	m_check_link;
	BOOL	m_check_replace;
	int		m_edit_u1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cedit_teamtype_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cedit_teamtype_dlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnActionSelect();
	afx_msg void OnObjectDelete();
	afx_msg void OnActionDelete();
	afx_msg void OnObjectInsert();
	afx_msg void OnActionInsert();
	afx_msg void OnSelchangeActionList();
	afx_msg void OnSelchangeObjectList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cxcc_level& m_level;
	string m_teamtype_name;
	t_teamtype_data_entry m_teamtype_data;
	bool m_teamtype_data_loaded;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDIT_TEAMTYPE_DLG_H__2E101121_174A_11D3_B601_A0454AC10154__INCLUDED_)
