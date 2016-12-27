#pragma once

#include "resource.h"
#include "string_conversion.h"
#include "xcc_level.h"

class Cedit_trigger_dlg : public CDialog
{
public:
	void load(const string& name);
	void save(string& name) const;
	Cedit_trigger_dlg(Cxcc_level& level);   // standard constructor

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

	//{{AFX_VIRTUAL(Cedit_trigger_dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

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
