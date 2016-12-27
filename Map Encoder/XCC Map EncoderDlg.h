#pragma once

#include "cc_file.h"
#include <virtual_binary.h>

class CXCCMapEncoderDlg : public CDialog
{
public:
	void convert(string _fname, Ccc_file& f);
	void convert(string fname);
	CXCCMapEncoderDlg(CWnd* pParent = NULL);	// standard constructor

	//{{AFX_DATA(CXCCMapEncoderDlg)
	enum { IDD = IDD_XCCMAPENCODER_DIALOG };
	CEdit	mc_gamemode;
	CButton	mc_create_mmx;
	CButton	mc_create_xmmf;
	BOOL	m_create_mmx;
	BOOL	m_create_xmmf;
	CString	m_gamemode;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CXCCMapEncoderDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	HICON m_hIcon;

	//{{AFX_MSG(CXCCMapEncoderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConvert();
	afx_msg void OnButtonXccHomePage();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnCreateMmx();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cvirtual_binary m_palet;
};
