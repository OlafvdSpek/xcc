// XCC TMP EditorView.h : interface of the CXCCTMPEditorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCCTMPEDITORVIEW_H__64DA8145_F21A_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XCCTMPEDITORVIEW_H__64DA8145_F21A_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "palet.h"

class CXCCTMPEditorView : public CScrollView
{
protected: // create from serialization only
	CXCCTMPEditorView();
	DECLARE_DYNCREATE(CXCCTMPEditorView)

// Attributes
public:
	CXCCTMPEditorDoc* GetDocument();

// Operations
public:
	void load_color_table(const t_palet palet);
	void load_grey_table(int c_colors = 256);
	void draw_image8(const byte* s, int cx_s, int cy_s, CDC* pDC, int x_d, int y_d);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCTMPEditorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	void select(int id);
	virtual ~CXCCTMPEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXCCTMPEditorView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CRect m_clip_rect;
	dword m_color_table[256];
	int m_selected;
};

#ifndef _DEBUG  // debug version in XCC TMP EditorView.cpp
inline CXCCTMPEditorDoc* CXCCTMPEditorView::GetDocument()
   { return (CXCCTMPEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCTMPEDITORVIEW_H__64DA8145_F21A_11D4_B606_0000B4936994__INCLUDED_)
