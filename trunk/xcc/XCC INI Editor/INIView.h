// INIView.h : interface of the CINIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIVIEW_H__CBA4B64D_0846_11D5_B606_0000B4936994__INCLUDED_)
#define AFX_INIVIEW_H__CBA4B64D_0846_11D5_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CCrystalEditView.h"

class CINIView: public CCrystalEditView
{
protected: // create from serialization only
	CINIView();
	DECLARE_DYNCREATE(CINIView)

// Attributes
public:
	CINIDoc* GetDocument();

	virtual CCrystalTextBuffer *LocateTextBuffer()
	{
		return &GetDocument()->m_xTextBuffer;
	}
// Operations
protected:
	virtual void DrawSingleLine(CDC *pdc, const CRect &rect, int nLineIndex);
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CINIView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CINIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	
// Generated message map functions
protected:
	//{{AFX_MSG(CINIView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in INIView.cpp
inline CINIDoc* CINIView::GetDocument()
   { return (CINIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INIVIEW_H__CBA4B64D_0846_11D5_B606_0000B4936994__INCLUDED_)
