#if !defined(AFX_EDIT_UNIT_PROPERTIES_DLG_H__BD897C23_1992_11D3_B601_D02E4AC1B40B__INCLUDED_)
#define AFX_EDIT_UNIT_PROPERTIES_DLG_H__BD897C23_1992_11D3_B601_D02E4AC1B40B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// edit_unit_properties_dlg.h : header file
//

#include "resource.h"
#include "xcc_level.h"

/////////////////////////////////////////////////////////////////////////////
// Cedit_unit_properties_dlg dialog

class Cedit_unit_properties_dlg : public CDialog
{
// Construction
public:
	void load(const t_unit_data_entry& d)
	{
		m_d = d;
	}

	void save(t_unit_data_entry& d) const
	{
		d = m_d;
	}

	Cedit_unit_properties_dlg(Cxcc_level& level);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cedit_unit_properties_dlg)
	enum { IDD = IDD_UNIT_PROPERTIES_DLG };
	CComboBox	m_combo_side;
	CComboBox	m_combo_action;
	long	m_edit_angle;
	CString	m_edit_cell;
	long	m_edit_health;
	CString	m_edit_trigger;
	CString	m_edit_type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cedit_unit_properties_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cedit_unit_properties_dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelect();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_unit_data_entry m_d;
	Cxcc_level& m_level;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDIT_UNIT_PROPERTIES_DLG_H__BD897C23_1992_11D3_B601_D02E4AC1B40B__INCLUDED_)
