// XCC Mod LauncherDlg.h : header file
//

#if !defined(AFX_XCCMODLAUNCHERDLG_H__A69C40C5_D1B9_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_XCCMODLAUNCHERDLG_H__A69C40C5_D1B9_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xcc_mod.h"
#include "xap.h"

/////////////////////////////////////////////////////////////////////////////
// CXCCModLauncherDlg dialog

class CXCCModLauncherDlg : public CDialog
{
// Construction
public:
	static HBITMAP create_bitmap(Cvirtual_image& image);
	LPDIRECTSOUND get_ds();
	void open_ds();
	void close_ds();
	void load_button_image(string fname, CButton& button);
	void load_intro();
	int download_update(string link, string fname);
	void set_mod(Cvirtual_binary v);
	void set_mod_fname(string mod_fname);
	CXCCModLauncherDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXCCModLauncherDlg)
	enum { IDD = IDD_XCCMODLAUNCHER_DIALOG };
	CButton	m_update;
	CButton	m_xhp;
	CButton	m_cancel;
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
	afx_msg void OnButtonUpdate();
	afx_msg void OnMailAuthor();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnUninstall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	LPDIRECTSOUND m_ds;
	string m_mod_fname;
	Cxif_key m_key;
	Cxcc_mod m_mod;
	Cvirtual_binary m_source;
	string m_uninstall_exe;
	Cxap m_xap;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCMODLAUNCHERDLG_H__A69C40C5_D1B9_11D4_A95D_0050042229FC__INCLUDED_)
