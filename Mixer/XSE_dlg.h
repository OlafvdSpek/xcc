#pragma once

#include "ListCtrlEx.h"
#include "audio_idx_file.h"
#include "cc_structures.h"
#include "csf_file.h"
#include "file32.h"
#include "resource.h"
#include "xap.h"

class CXSE_dlg : public ETSLayoutDialog
{
public:
	void bag_file(const string&);
	void idx_file(const string&);
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

	//{{AFX_DATA(CXSE_dlg)
	enum { IDD = IDD_XSE };
	CButton	m_compact;
	CListCtrlEx	m_list;
	CButton	m_play;
	CButton	m_extract;
	CButton	m_delete;
	CString	m_extract_to_edit;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CXSE_dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

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
	afx_msg void OnPlay();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
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
	typedef map<string, Ccsf_file::t_map::const_pointer> t_reverse_csf_map;

	bool m_expansion;
	t_game m_game;
	Cfile32 m_bag_f;
	string m_bag_fname;
	Ccsf_file m_csf_f;
	Cfile32 m_idx_f;
	string m_idx_fname;
	t_map m_map;
	t_reverse_csf_map m_reverse_csf_map;
	int m_sort_column;
	bool m_sort_reverse;
	LPDIRECTSOUND m_ds;
};
