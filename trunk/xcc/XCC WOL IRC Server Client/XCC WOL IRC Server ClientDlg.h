// XCC WOL IRC Server ClientDlg.h : header file
//

#if !defined(AFX_XCCWOLIRCSERVERCLIENTDLG_H__B0AEAA9F_1124_46A5_9782_F517980415E3__INCLUDED_)
#define AFX_XCCWOLIRCSERVERCLIENTDLG_H__B0AEAA9F_1124_46A5_9782_F517980415E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXCCWOLIRCServerClientDlg dialog

class CXCCWOLIRCServerClientDlg : public CDialog
{
// Construction
public:
	void update_ipa2();
	int update_hosts(const string& ipa);
	CXCCWOLIRCServerClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXCCWOLIRCServerClientDlg)
	enum { IDD = IDD_XCCWOLIRCSERVERCLIENT_DIALOG };
	CIPAddressCtrl	m_ipa2;
	CIPAddressCtrl	m_ipa;
	CString	m_hosts;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCWOLIRCServerClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXCCWOLIRCServerClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSet();
	afx_msg void OnReset();
	afx_msg void OnOpen();
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCWOLIRCSERVERCLIENTDLG_H__B0AEAA9F_1124_46A5_9782_F517980415E3__INCLUDED_)
