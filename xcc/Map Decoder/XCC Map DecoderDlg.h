// XCC Map DecoderDlg.h : header file
//

#if !defined(AFX_XCCMAPDECODERDLG_H__3F5275A6_FD1B_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XCCMAPDECODERDLG_H__3F5275A6_FD1B_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "virtual_binary.h"

/////////////////////////////////////////////////////////////////////////////
// CXCCMapDecoderDlg dialog

class CXCCMapDecoderDlg : public CDialog
{
// Construction
public:
	void convert(string _fname);
	CXCCMapDecoderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXCCMapDecoderDlg)
	enum { IDD = IDD_XCCMAPDECODER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCMapDecoderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
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

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCMAPDECODERDLG_H__3F5275A6_FD1B_11D4_B606_0000B4936994__INCLUDED_)
