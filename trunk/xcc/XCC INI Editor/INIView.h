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
private:
	typedef CCrystalEditView super;
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
protected:
	virtual COLORREF GetColor(int nColorIndex);

// Operations
protected:
	virtual void DrawSingleLine(CDC *pdc, const CRect &rect, int nLineIndex);
public:
	void find_section(int l);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CINIView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	void analyse();
	virtual ~CINIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	
// Generated message map functions
protected:
	//{{AFX_MSG(CINIView)
	afx_msg void OnViewSyntaxHighlighting();
	afx_msg void OnUpdateViewSyntaxHighlighting(CCmdUI* pCmdUI);
	afx_msg void OnViewSelectionMargin();
	afx_msg void OnUpdateViewSelectionMargin(CCmdUI* pCmdUI);
	afx_msg void OnViewReport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_syntax_highlighting;
};

#ifndef _DEBUG  // debug version in INIView.cpp
inline CINIDoc* CINIView::GetDocument()
   { return (CINIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INIVIEW_H__CBA4B64D_0846_11D5_B606_0000B4936994__INCLUDED_)
