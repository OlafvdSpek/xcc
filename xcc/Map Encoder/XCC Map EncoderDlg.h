// XCC Map EncoderDlg.h : header file
//

#if !defined(AFX_XCCMAPENCODERDLG_H__BF04620A_FBA8_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XCCMAPENCODERDLG_H__BF04620A_FBA8_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file.h"
#include "virtual_binary.h"

/////////////////////////////////////////////////////////////////////////////
// CXCCMapEncoderDlg dialog

class CXCCMapEncoderDlg : public CDialog
{
// Construction
public:
	void convert(string _fname, Ccc_file& f);
	void convert(string fname);
	CXCCMapEncoderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXCCMapEncoderDlg)
	enum { IDD = IDD_XCCMAPENCODER_DIALOG };
	CEdit	mc_gamemode;
	CButton	mc_create_mmx;
	CButton	mc_create_xmmf;
	BOOL	m_create_mmx;
	BOOL	m_create_xmmf;
	CString	m_gamemode;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCMapEncoderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
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

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCMAPENCODERDLG_H__BF04620A_FBA8_11D4_B606_0000B4936994__INCLUDED_)
