#if !defined(AFX_MIXLIST_H__A14B9B31_F2B7_11D3_B605_0000B4936994__INCLUDED_)
#define AFX_MIXLIST_H__A14B9B31_F2B7_11D3_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXCCMIXEditorDlg;

// MIXList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMIXList window

class CMIXList : public CListCtrl
{
// Construction
public:
	CMIXList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMIXList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMIXList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMIXList)
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIXLIST_H__A14B9B31_F2B7_11D3_B605_0000B4936994__INCLUDED_)
