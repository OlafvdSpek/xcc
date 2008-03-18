#pragma once

#include "resource.h"
#include "xcc_level.h"

class Cedit_basic_dlg : public CDialog
{
public:
	Cedit_basic_dlg(Cxcc_level& level);   // standard constructor

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

	//{{AFX_VIRTUAL(Cedit_basic_dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(Cedit_basic_dlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_basic_data& m_basic_data;
};
