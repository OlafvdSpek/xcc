// XRG Mod LauncherDlg.h : header file
//

#if !defined(AFX_XRGMODLAUNCHERDLG_H__AACDFD1E_A453_4101_B3B3_018903366F98__INCLUDED_)
#define AFX_XRGMODLAUNCHERDLG_H__AACDFD1E_A453_4101_B3B3_018903366F98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXRGModLauncherDlg dialog

class CXRGModLauncherDlg : public CDialog
{
// Construction
public:
	void convert(string fname);
	CXRGModLauncherDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXRGModLauncherDlg)
	enum { IDD = IDD_XRGMODLAUNCHER_DIALOG };
	BOOL	m_binary_diff_compression;
	BOOL	m_tga_compression;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXRGModLauncherDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXRGModLauncherDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConvert();
	afx_msg void OnXHP();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XRGMODLAUNCHERDLG_H__AACDFD1E_A453_4101_B3B3_018903366F98__INCLUDED_)
