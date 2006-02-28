// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__4E596E2A_F686_11D2_B601_D35C3DCCB8F1__INCLUDED_)
#define AFX_MAINFRM_H__4E596E2A_F686_11D2_B601_D35C3DCCB8F1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XCC EditorDoc.h"
#include "XCC EditorView.h"
#include "edit_infantry_dlg.h"
#include "edit_structures_dlg.h"
#include "edit_units_dlg.h"
#include "log_window.h"
#include "object_selection.h"
#include "string_conversion.h"
#include "xcc_cell.h"
#include "xcc_level.h"	// Added by ClassView

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	Cxcc_cell m_mouse_pos;
	bool m_idle_msg_changed;
	string m_object_name;
	Clog_window m_log_window;
	Cobject_selection* m_selection_pane;
	CXCCEditorView* m_level_pane;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	t_side_id default_side() const;
	t_action_id default_action() const;
	CComboBox& combo_side() const;
	CComboBox& combo_action() const;
	void GetMessageString(UINT id, CString& msg) const;
	void set_statusbar_cx_pane(UINT id, long cx);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CSplitterWnd	m_splitter;
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	CDialogBar m_wndPropertyBar;
	void OnIdleUpdateCmdUI();
	void OnUpdateCell(CCmdUI *pCmdUI);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditEditStructures();
	afx_msg void OnEditEditUnits();
	afx_msg void OnEditEditInfantry();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__4E596E2A_F686_11D2_B601_D35C3DCCB8F1__INCLUDED_)
