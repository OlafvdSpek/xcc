#if !defined(AFX_XSE_LIST_H__4A1B3180_C22D_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_XSE_LIST_H__4A1B3180_C22D_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XSE_list.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXSE_list window

class CXSE_list : public CListCtrl
{
// Construction
public:
	CXSE_list();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXSE_list)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXSE_list();

	// Generated message map functions
protected:
	//{{AFX_MSG(CXSE_list)
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XSE_LIST_H__4A1B3180_C22D_11D4_A95D_0050042229FC__INCLUDED_)
