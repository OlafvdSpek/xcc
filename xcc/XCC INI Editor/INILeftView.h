#if !defined(AFX_INILEFTVIEW_H__14267140_08EE_11D5_B606_0000B4936994__INCLUDED_)
#define AFX_INILEFTVIEW_H__14267140_08EE_11D5_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// INILeftView.h : header file
//

#include "inidoc.h"

/////////////////////////////////////////////////////////////////////////////
// CINILeftView view

class CINILeftView : public CTreeView
{
protected:
	CINILeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CINILeftView)

// Attributes
public:
	CINIDoc* GetDocument()
	{
		return (CINIDoc*)m_pDocument; 
	}

	virtual CINIDoc::CINIBuffer *LocateTextBuffer()
	{
		return &GetDocument()->m_xTextBuffer;
	}
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CINILeftView)
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CINILeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CINILeftView)
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INILEFTVIEW_H__14267140_08EE_11D5_B606_0000B4936994__INCLUDED_)
