#pragma once

class CXCCWOLIRCServerClientDlg: public CDialog
{
public:
	void update_ipa2();
	int update_hosts(const string& ipa);
	CXCCWOLIRCServerClientDlg(CWnd* pParent = NULL);	// standard constructor

	enum { IDD = IDD_XCCWOLIRCSERVERCLIENT_DIALOG };
	CIPAddressCtrl	m_ipa2;
	CIPAddressCtrl	m_ipa;
	CString	m_hosts;
	CString	m_wolapi_dll;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSet();
	afx_msg void OnReset();
	afx_msg void OnOpen();
	afx_msg void OnTest();
	afx_msg void OnLadder();
	afx_msg void OnViewSerials();
	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;
};
