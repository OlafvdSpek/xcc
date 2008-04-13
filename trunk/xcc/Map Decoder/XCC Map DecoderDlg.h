#pragma once

#include <virtual_binary.h>

class CXCCMapDecoderDlg : public CDialog
{
public:
	void convert(string _fname);
	CXCCMapDecoderDlg(CWnd* pParent = NULL);	// standard constructor

	//{{AFX_DATA(CXCCMapDecoderDlg)
	enum { IDD = IDD_XCCMAPDECODER_DIALOG };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CXCCMapDecoderDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXCCMapDecoderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConvert();
	afx_msg void OnButtonXccHomePage();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cvirtual_binary m_palet;
};
