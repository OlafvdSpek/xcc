#if !defined(AFX_LIBRARY_DLG_H__5A6E1A7F_7A12_4826_B56E_55A59EF8AA4B__INCLUDED_)
#define AFX_LIBRARY_DLG_H__5A6E1A7F_7A12_4826_B56E_55A59EF8AA4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// library_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Clibrary_dlg dialog

class Clibrary_dlg : public ETSLayoutDialog
{
// Construction
public:
	void update_containers();
	Clibrary_dlg(const Cucr_formats& formats, Cucr_library& library, CWnd* pParent = NULL);   // standard constructor

	const string& container() const
	{
		return m_container;
	}

// Dialog Data
	//{{AFX_DATA(Clibrary_dlg)
	enum { IDD = IDD_LIBRARY };
	CButton	m_ok_button;
	CTreeCtrl	m_tree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Clibrary_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void insert_format(const Cucr_library::t_containers& containers);

	// Generated message map functions
	//{{AFX_MSG(Clibrary_dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectories();
	afx_msg void OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	typedef map<string, HTREEITEM> t_map;
	typedef map<HTREEITEM, string> t_reverse_map;

	string m_container;
	t_map m_map;
	t_reverse_map m_reverse_map;
	const Cucr_formats& m_formats;
	Cucr_library& m_library;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIBRARY_DLG_H__5A6E1A7F_7A12_4826_B56E_55A59EF8AA4B__INCLUDED_)
