// XCC Mod LauncherDlg.h : header file
//

#if !defined(AFX_XCCMODLAUNCHERDLG_H__A69C40C5_D1B9_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_XCCMODLAUNCHERDLG_H__A69C40C5_D1B9_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xcc_mod.h"

/////////////////////////////////////////////////////////////////////////////
// CXCCModLauncherDlg dialog

class CXCCModLauncherDlg : public CDialog
{
// Construction
public:
	void set_mod_fname(string mod_fname);
	CXCCModLauncherDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXCCModLauncherDlg)
	enum { IDD = IDD_XCCMODLAUNCHER_DIALOG };
	CStatic	m_banner;
	CButton	m_ok;
	CButton	m_site;
	CButton	m_manual;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCModLauncherDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXCCModLauncherDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonXHP();
	afx_msg void OnButtonSite();
	virtual void OnOK();
	afx_msg void OnButtonManual();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	string m_mod_fname;
	Cxif_key m_key;
	Cxcc_mod m_mod;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCMODLAUNCHERDLG_H__A69C40C5_D1B9_11D4_A95D_0050042229FC__INCLUDED_)
