#if !defined(AFX_XCCAUDIOPLAYERINFODLG_H__62EAD0E2_E448_11D2_B750_FB9906ADAC7B__INCLUDED_)
#define AFX_XCCAUDIOPLAYERINFODLG_H__62EAD0E2_E448_11D2_B750_FB9906ADAC7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// XCCAUDIOPLAYERINFODlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXCCAudioPlayerInfoDlg dialog

class CXCCAudioPlayerInfoDlg : public CDialog
{
// Construction
public:
	CXCCAudioPlayerInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXCCAudioPlayerInfoDlg)
	enum { IDD = IDD_INFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCAudioPlayerInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXCCAudioPlayerInfoDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCAUDIOPLAYERINFODLG_H__62EAD0E2_E448_11D2_B750_FB9906ADAC7B__INCLUDED_)
