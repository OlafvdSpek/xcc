#pragma once

#include "XCC Mod CreatorView.h"

class CXCCModCreatorDoc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CXCCModCreatorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	void set_other_pane(CXCCModCreatorView* other_pane);
	virtual ~CLeftView();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CXCCModCreatorView* m_other_pane;
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CXCCModCreatorDoc* CLeftView::GetDocument()
   { return (CXCCModCreatorDoc*)m_pDocument; }
#endif
