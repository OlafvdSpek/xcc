#pragma once

#include "resource.h"
#include "xcc_level.h"

class Cedit_side_dlg : public CDialog
{
public:
	Cedit_side_dlg(t_side_data& side_data);   // standard constructor

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

	//{{AFX_VIRTUAL(Cedit_side_dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(Cedit_side_dlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_side_data& m_side_data;
};
