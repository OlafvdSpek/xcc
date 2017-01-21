#pragma once

#include "palet.h"

class CXCCTMPEditorView : public CScrollView
{
protected: // create from serialization only
	CXCCTMPEditorView();
	DECLARE_DYNCREATE(CXCCTMPEditorView)

// Attributes
public:
	CXCCTMPEditorDoc* GetDocument()
	{ 
		return (CXCCTMPEditorDoc*)m_pDocument; 
	}

	bool view_true_height() const;
	void view_true_height(bool v);

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

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXCCTMPEditorView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CRect m_clip_rect;
	DWORD m_color_table[256];
	int m_selected = -1;
	bool m_view_true_height = false;
};
