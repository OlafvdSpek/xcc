#if !defined(AFX_FORMAT_EDIT_DLG_H__39FA4CFC_7CDF_403E_8BE8_ED94634A9CD9__INCLUDED_)
#define AFX_FORMAT_EDIT_DLG_H__39FA4CFC_7CDF_403E_8BE8_ED94634A9CD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// format_edit_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cformat_edit_dlg dialog

class Cformat_edit_dlg : public ETSLayoutDialog
{
// Construction
public:
	void update_vars();
	void set(const Cucr_format& v);
	const Cucr_format& get() const;
	Cformat_edit_dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cformat_edit_dlg)
	enum { IDD = IDD_FORMAT };
	CListCtrl	m_vars;
	CListCtrl	m_blocks;
	CString	m_extensions;
	CString	m_name;
	CString	m_registry_keys;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cformat_edit_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cformat_edit_dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetdispinfoBlocks(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdispinfoVars(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedBlocks(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	string m_buffer[4];
	int m_buffer_w;
	const Cucr_format::t_block* m_block;
	Cucr_format m_format;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMAT_EDIT_DLG_H__39FA4CFC_7CDF_403E_8BE8_ED94634A9CD9__INCLUDED_)
