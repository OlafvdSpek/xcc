// INIMainFrm.h : interface of the CINIMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIMAINFRM_H__CBA4B647_0846_11D5_B606_0000B4936994__INCLUDED_)
#define AFX_INIMAINFRM_H__CBA4B647_0846_11D5_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CINIMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CINIMainFrame)
public:
	CINIMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CINIMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	afx_msg void OnUpdateIndicatorPosition(CCmdUI* pCmdUI);

// Implementation
public:
	virtual ~CINIMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CReBar      m_wndReBar;
	CDialogBar      m_wndDlgBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CINIMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INIMAINFRM_H__CBA4B647_0846_11D5_B606_0000B4936994__INCLUDED_)
