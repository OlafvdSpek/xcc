// MF TesterDlg.h : header file
//

#if !defined(AFX_MFTESTERDLG_H__22722E35_0AE6_452A_9F76_C7E54DAE60CF__INCLUDED_)
#define AFX_MFTESTERDLG_H__22722E35_0AE6_452A_9F76_C7E54DAE60CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMFTesterDlg dialog

class CMFTesterDlg : public ETSLayoutDialog
{
// Construction
public:
	void test_hostname(const char* name);
	void test_serverlist_server(int gid);
	CMFTesterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMFTesterDlg)
	enum { IDD = IDD_MFTESTER_DIALOG };
	CString	m_edit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFTesterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMFTesterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFTESTERDLG_H__22722E35_0AE6_452A_9F76_C7E54DAE60CF__INCLUDED_)
