#if !defined(AFX_XSE_DLG_H__D7A0CF20_C17D_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XSE_DLG_H__D7A0CF20_C17D_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// XSE_dlg.h : header file
//

#include <map>
#include "audio_idx_file.h"
#include "cc_structures.h"
#include "csf_file.h"
#include "file32.h"
#include "resource.h"
#include "XSE_list.h"
#include "xap.h"

/////////////////////////////////////////////////////////////////////////////
// CXSE_dlg dialog

class CXSE_dlg : public ETSLayoutDialog
{
// Construction
public:
	void sort_list(int i, bool reverse);
	void set_extract_to_dir(const string& v);
	void add_file(const string& name);
	void check_selection();
	int get_bag_size() const;
	int get_current_index();
	int get_free_id();
	int insert(int i);
	void read_idx_file(const Caudio_idx_file& f);
	void write_idx_file();
	int compare(int id_a, int id_b) const;
	CXSE_dlg(t_game game, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXSE_dlg)
	enum { IDD = IDD_XSE };
	CButton	m_compact;
	CXSE_list	m_list;
	CButton	m_play;
	CButton	m_extract;
	CButton	m_delete;
	CString	m_extract_to_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXSE_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXSE_dlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnExtract();
	afx_msg void OnDelete();
	afx_msg void OnCompact();
	afx_msg void OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnExtractToButton();
	afx_msg void OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnPlay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	struct t_map_entry
	{
		int offset;
		int size;
		int samplerate;
		int flags;
		int chunk_size;
		string name;
		string value;
		string extra_value;
	};

	typedef map<int, t_map_entry> t_map;
	typedef map<string, Ccsf_file::t_map::const_iterator> t_reverse_csf_map;

	bool m_expansion;
	t_game m_game;
	string m_buffer[4];
	int m_buffer_w;
	Cfile32 m_bag_f;
	Ccsf_file m_csf_f;
	Cfile32 m_idx_f;
	t_map m_map;
	t_reverse_csf_map m_reverse_csf_map;
	int m_sort_column;
	bool m_sort_reverse;
	LPDIRECTSOUND m_ds;
	Cxap m_xap;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XSE_DLG_H__D7A0CF20_C17D_11D4_B606_0000B4936994__INCLUDED_)
