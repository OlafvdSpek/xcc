// XCC Map EncoderDlg.h : header file
//

#if !defined(AFX_XCCMAPENCODERDLG_H__BF04620A_FBA8_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XCCMAPENCODERDLG_H__BF04620A_FBA8_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXCCMapEncoderDlg dialog

class CXCCMapEncoderDlg : public CDialog
{
// Construction
public:
	void convert(string fname);
	CXCCMapEncoderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXCCMapEncoderDlg)
	enum { IDD = IDD_XCCMAPENCODER_DIALOG };
	CButton	mc_export_pkt;
	CButton	mc_create_mmx;
	CButton	mc_create_xmmf;
	BOOL	m_create_mmx;
	BOOL	m_export_pkt;
	BOOL	m_create_xmmf;
	BOOL	m_import_pkt;
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
	afx_msg void OnCreateXmmf();
	afx_msg void OnImportPkt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCMAPENCODERDLG_H__BF04620A_FBA8_11D4_B606_0000B4936994__INCLUDED_)
