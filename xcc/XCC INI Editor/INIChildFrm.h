// INIChildFrm.h : interface of the CINIChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INICHILDFRM_H__CBA4B649_0846_11D5_B606_0000B4936994__INCLUDED_)
#define AFX_INICHILDFRM_H__CBA4B649_0846_11D5_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "inileftview.h"
#include "iniview.h"

class CINIChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CINIChildFrame)
public:
	CINIChildFrame();

// Attributes
protected:
	CSplitterWnd m_wndSplitter1;
	CSplitterWnd m_wndSplitter2;
public:

// Operations
public:
	CINILeftView* GetLeftPane();
	CINIView* GetRightPane();
	void SetActivePane(int row, int col);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CINIChildFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CINIChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CINIChildFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INICHILDFRM_H__CBA4B649_0846_11D5_B606_0000B4936994__INCLUDED_)
