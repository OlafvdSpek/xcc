#if !defined(AFX_OPTIONS_DLG_H__9FA091C0_D599_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_OPTIONS_DLG_H__9FA091C0_D599_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// options_dlg.h : header file
//

#include "xcc_mod.h"

/////////////////////////////////////////////////////////////////////////////
// Coptions_dlg dialog

class Coptions_dlg : public CDialog
{
// Construction
public:
	Cxcc_mod::t_options get() const;
	void set(Cxcc_mod::t_options options);
	Coptions_dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Coptions_dlg)
	enum { IDD = IDD_OPTIONS };
	int		m_game;
	CString	m_link;
	CString	m_link_title;
	CString	m_mail;
	CString	m_name;
	CString	m_mod_name;
	BOOL	m_ini_diff_compression;
	BOOL	m_csf_diff_compression;
	BOOL	m_exit_button;
	BOOL	m_manual_button;
	BOOL	m_site_button;
	BOOL	m_xhp_button;
	BOOL	m_custom_button_text;
	CString	m_mod_ucf;
	CString	m_mod_version;
	BOOL	m_update_button;
	BOOL	m_confirm_deactivate;
	BOOL	m_shp_compression;
	BOOL	m_vxl_compression;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Coptions_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Coptions_dlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_reg_key;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONS_DLG_H__9FA091C0_D599_11D4_A95D_0050042229FC__INCLUDED_)
