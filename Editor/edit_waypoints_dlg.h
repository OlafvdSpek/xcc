#pragma once

#include "list_ctrl_extension.h"
#include "resource.h"
#include "string_conversion.h"
#include "xcc_cell.h"
#include "xcc_level.h"

class Cedit_waypoints_dlg: public ETSLayoutDialog
{
public:
	long get_selected_i() const;
	Cedit_waypoints_dlg(Cxcc_level& level, bool selection_wanted = false);   // standard constructor

	//{{AFX_DATA(Cedit_waypoints_dlg)
	enum { IDD = IDD_EDIT_WAYPOINTS_DLG };
	CButton	m_delete_button;
	CButton	m_ok_button;
	Clist_ctrl_extension	m_list;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(Cedit_waypoints_dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

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
