#if !defined(AFX_EDIT_TRIGGER_DLG_H__C3C41783_15D2_11D3_B601_004B4AC10154__INCLUDED_)
#define AFX_EDIT_TRIGGER_DLG_H__C3C41783_15D2_11D3_B601_004B4AC10154__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "string_conversion.h"
#include "xcc_level.h"

/////////////////////////////////////////////////////////////////////////////
// Cedit_trigger_dlg dialog

class Cedit_trigger_dlg : public CDialog
{
// Construction
public:
	void load(const string& name);
	void save(string& name) const;
	Cedit_trigger_dlg(Cxcc_level& level);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cedit_trigger_dlg)
	enum { IDD = IDD_EDIT_TRIGGER_DLG };
	CComboBox	m_combo_side;
	CComboBox	m_combo_event;
	CComboBox	m_combo_cause;
	CString	m_edit_teamtype;
	long	m_edit_count;
	int		m_combo_loop;
	CString	m_edit_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cedit_trigger_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cedit_trigger_dlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cxcc_level& m_level;
	string m_trigger_name;
	t_trigger_data_entry m_trigger_data;
	bool m_trigger_data_loaded;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDIT_TRIGGER_DLG_H__C3C41783_15D2_11D3_B601_004B4AC10154__INCLUDED_)
