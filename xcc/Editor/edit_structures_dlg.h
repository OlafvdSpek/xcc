#pragma once

#include "list_ctrl_extension.h"
#include "resource.h"
#include "string_conversion.h"
#include "xcc_structures.h"

class Cedit_structures_dlg : public CDialog
{
public:
	void load_controls();
	void save_controls();
	void update_controls();
	void add_item(long i);
	void update_item(long i);
	Cedit_structures_dlg(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(Cedit_structures_dlg)
	enum { IDD = IDD_EDIT_STRUCTURES_DLG };
	CEdit	m_editctrl_flags;
	CEdit	m_editctrl_short_name;
	CEdit	m_editctrl_long_name;
	Clist_ctrl_extension	m_list;
	CString	m_edit_long_name;
	CString	m_edit_short_name;
	DWORD	m_edit_flags;
	CString	m_edit_size;
	BOOL	m_check_bib;
	BOOL	m_check_civilian;
	BOOL	m_check_icon;
	BOOL	m_check_desert;
	BOOL	m_check_temperate;
	BOOL	m_check_winter;
	BOOL	m_check_blocked10;
	BOOL	m_check_blocked11;
	BOOL	m_check_blocked3;
	BOOL	m_check_blocked4;
	BOOL	m_check_blocked5;
	BOOL	m_check_blocked6;
	BOOL	m_check_blocked7;
	BOOL	m_check_blocked8;
	BOOL	m_check_blocked9;
	BOOL	m_check_blocked0;
	BOOL	m_check_blocked1;
	BOOL	m_check_blocked2;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(Cedit_structures_dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(Cedit_structures_dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNewButton();
	virtual void OnOK();
	afx_msg void OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long m_current_i;
};
