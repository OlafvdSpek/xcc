#pragma once

class CXCCModCreatorView;

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

protected:
	CSplitterWnd m_wndSplitter;
public:

public:

	//{{AFX_VIRTUAL(CChildFrame)
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

public:
	virtual ~CChildFrame();

protected:
	CXCCModCreatorView* GetRightPane();
protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg void OnFileExport();
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditInvertSelection();
	afx_msg void OnViewRefresh();
	afx_msg void OnViewLaunch();
	afx_msg void OnModClearGameDirectory();
	afx_msg void OnModActivate();
	afx_msg void OnModDeactivate();
	afx_msg void OnModOptions();
	afx_msg void OnModReport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
