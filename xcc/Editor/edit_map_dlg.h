#pragma once

#include "resource.h"
#include "xcc_level.h"

class Cedit_map_dlg : public CDialog
{
public:
	Cedit_map_dlg(Cxcc_level& level);   // standard constructor

	//{{AFX_DATA(Cedit_map_dlg)
	enum { IDD = IDD_EDIT_MAP_DLG };
	CComboBox	m_combo_theater;
	long	m_edit_cx;
	long	m_edit_x;
	long	m_edit_y;
	long	m_edit_cy;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(Cedit_map_dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(Cedit_map_dlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_map_data& m_map_data;
};
