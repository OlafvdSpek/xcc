// XCC Cheat ReporterDlg.h : header file
//

#if !defined(AFX_XCCCHEATREPORTERDLG_H__DDCDF145_1315_11D5_A95E_0050042229FC__INCLUDED_)
#define AFX_XCCCHEATREPORTERDLG_H__DDCDF145_1315_11D5_A95E_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file.h"
#include "cc_structures.h"

/////////////////////////////////////////////////////////////////////////////
// CXCCCheatReporterDlg dialog

class CXCCCheatReporterDlg : public CDialog
{
// Construction
public:
	void decode(string fname);
	string image_ext();
	t_file_type image_format();
	t_game game();
	CXCCCheatReporterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXCCCheatReporterDlg)
	enum { IDD = IDD_XCCCHEATREPORTER_DIALOG };
	int		m_game;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCCheatReporterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXCCCheatReporterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPaste();
	afx_msg void OnCreate();
	afx_msg void OnDecode();
	afx_msg void OnXhp();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCCHEATREPORTERDLG_H__DDCDF145_1315_11D5_A95E_0050042229FC__INCLUDED_)
