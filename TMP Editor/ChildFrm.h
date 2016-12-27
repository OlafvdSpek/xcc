#pragma once

class CLeftView;
class CXCCTMPEditorView;

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
public:

// Operations
public:
	CLeftView* GetLeftPane();
	CXCCTMPEditorView* GetRightPane();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditInvertSelection();
	afx_msg void OnPaletSnow();
	afx_msg void OnPaletTemperate();
	afx_msg void OnPaletUrban();
	afx_msg void OnPaletLoad();
	afx_msg void OnViewTrueHeight();
	afx_msg void OnUpdateViewTrueHeight(CCmdUI* pCmdUI);
	afx_msg void OnPaletDesert();
	afx_msg void OnPaletLunar();
	afx_msg void OnPaletUrban2();
	afx_msg void OnUpdatePaletDesert(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePaletLunar(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePaletSnow(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePaletTemperate(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePaletUrban(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePaletUrban2(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
