#if !defined(AFX_DLG_CCR_H__DED240E0_1320_11D5_A95E_0050042229FC__INCLUDED_)
#define AFX_DLG_CCR_H__DED240E0_1320_11D5_A95E_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// dlg_ccr.h : header file
//

#include "cc_structures.h"
#include "virtual_binary.h"

/////////////////////////////////////////////////////////////////////////////
// Cdlg_ccr dialog

class Cdlg_ccr : public ETSLayoutDialog
{
// Construction
public:
	void load_nicknames();
	void autosize_colums();
	int compare(int id_a, int id_b) const;
	int load_screenshots();
	int load_stats();
	Cdlg_ccr(CWnd* pParent = NULL);   // standard constructor
	void game(t_game game);

// Dialog Data
	//{{AFX_DATA(Cdlg_ccr)
	enum { IDD = IDD_CCR };
	CComboBox	m_nickname;
	CListCtrl	m_list;
	CString	m_stats;
	CString	m_description;
	BOOL	m_connection_speed;
	BOOL	m_disconnect;
	BOOL	m_game_speed;
	BOOL	m_map_revealer;
	BOOL	m_mod_map;
	BOOL	m_reconnection_error;
	BOOL	m_build_anywhere;
	BOOL	m_money;
	BOOL	m_tech;
	CString	m_mail;
	CString	m_name;
	int		m_game_id;
	BOOL	m_send_ws;
	BOOL	m_send_xhp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cdlg_ccr)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;

	// Generated message map functions
	//{{AFX_MSG(Cdlg_ccr)
	virtual BOOL OnInitDialog();
	afx_msg void OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	struct t_map_entry
	{
		string fname;
		int size;
	};

	typedef map<int, t_map_entry> t_map;

	int get_free_id() const;
	void sort_list(int i, bool reverse);

	string m_buffer[4];
	int m_buffer_w;
	t_game m_game;
	t_map m_map;
	CString m_reg_key;
	int m_sort_column;
	bool m_sort_reverse;
};

int xcrf_decode(Cvirtual_binary s, string fname);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_CCR_H__DED240E0_1320_11D5_A95E_0050042229FC__INCLUDED_)
