#pragma once

#include "resource.h"
#include "xcc_level.h"

class Cedit_structure_properties_dlg : public CDialog
{
public:
	void load(const t_structure_data_entry& d)
	{
		m_d = d;
	}

	void save(t_structure_data_entry& d) const
	{
		d = m_d;
	}

	Cedit_structure_properties_dlg(Cxcc_level& level);   // standard constructor

	//{{AFX_DATA(Cedit_structure_properties_dlg)
	enum { IDD = IDD_STRUCTURE_PROPERTIES_DLG };
	CComboBox	m_combo_side;
	long	m_edit_angle;
	CString	m_edit_cell;
	long	m_edit_health;
	CString	m_edit_trigger;
	CString	m_edit_type;
	BOOL	m_check_replace;
	BOOL	m_check_start;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(Cedit_structure_properties_dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(Cedit_structure_properties_dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelect();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_structure_data_entry m_d;
	Cxcc_level& m_level;
};
