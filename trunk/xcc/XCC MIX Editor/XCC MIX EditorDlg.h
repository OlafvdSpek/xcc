// XCC MIX EditorDlg.h : header file
//

#if !defined(AFX_XCCMIXEDITORDLG_H__A14B9B25_F2B7_11D3_B605_0000B4936994__INCLUDED_)
#define AFX_XCCMIXEDITORDLG_H__A14B9B25_F2B7_11D3_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <string>
#include "cc_file.h"
#include "mix_file.h"
#include "MIXList.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CXCCMIXEditorDlg dialog

class CXCCMIXEditorDlg : public ETSLayoutDialog
{
// Construction
public:
	void autosize_colums();
	void add_entry(int id);
	void add_file(const string& name);
	int compact_mix();
	int compare(int id_a, int id_b) const;
	int get_header_size() const;
	int get_max_offset() const;
	int read_key(const string& name);
	int read_mix(const string& name);
	int save_mix();
	void set_changed(bool changed);
	void set_status(const string& msg, bool error);
	void sort_list(int i, bool reverse);
	void update_buttons();
	void update_list();
	CXCCMIXEditorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXCCMIXEditorDlg)
	enum { IDD = IDD_XCCMIXEDITOR_DIALOG };
	CButton	m_button_insert;
	CButton	m_button_options;
	CButton	m_button_delete;
	CButton	m_button_load_key;
	CButton	m_button_compact;
	CButton	m_button_save;
	CButton	m_button_close;
	CButton	m_button_open;
	CButton	m_button_new;
	CMIXList	m_list;
	CString	m_edit_status;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCMIXEditorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXCCMIXEditorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonNew();
	afx_msg void OnButtonClose();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonCompact();
	afx_msg void OnButtonLoadKey();
	afx_msg void OnButtonXccHomePage();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonOptions();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitemList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnButtonInsert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	struct t_index_entry
	{
		t_file_type ft;
		int offset;
		int size;
		string fname;
	};

	typedef map<int, t_index_entry> t_index;

	bool	m_changed;
	bool	m_checksum;
	int		m_current_id;
	bool	m_encrypted;
	string	m_fname;
	t_game	m_game;
	t_index	m_index;	
	byte	m_key[cb_mix_key_source];
	bool	m_key_loaded;
	bool	m_open;
	int		m_sort_column;
	bool	m_sort_reverse;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCMIXEDITORDLG_H__A14B9B25_F2B7_11D3_B605_0000B4936994__INCLUDED_)
