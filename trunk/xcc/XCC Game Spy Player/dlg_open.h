#if !defined(AFX_DLG_OPEN_H__BA128AED_ECA0_4EA4_A0E6_48D1975F4684__INCLUDED_)
#define AFX_DLG_OPEN_H__BA128AED_ECA0_4EA4_A0E6_48D1975F4684__INCLUDED_

#include "xif_key.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// dlg_open.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cdlg_open dialog

class Cdlg_open : public ETSLayoutDialog
{
// Construction
public:
	int compare(int id_a, int id_b);
	void sort_replays(int i, bool reverse);
	Cxif_key export_cache();
	void import_cache(const Cxif_key& key);
	string fname();
	Cdlg_open(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cdlg_open)
	enum { IDD = IDD_OPEN };
	CButton	m_ok;
	CListCtrl	m_replays;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cdlg_open)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cdlg_open)
	virtual BOOL OnInitDialog();
	afx_msg void OnGetdispinfoReplays(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedReplays(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkReplays(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickReplays(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	typedef set<string> t_player_set;

	struct t_map_entry
	{
		string dir;
		string name;
		int gid;
		int size;
		t_player_set players;
		string scenario;
	};

	typedef map<int, t_map_entry> t_map;

	string m_buffer[4];
	int m_buffer_w;
	string m_fname;
	t_map m_map;
	int m_sort_column;
	bool m_sort_reverse;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_OPEN_H__BA128AED_ECA0_4EA4_A0E6_48D1975F4684__INCLUDED_)
