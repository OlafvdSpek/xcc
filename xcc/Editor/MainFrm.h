#pragma once

#include "XCC EditorDoc.h"
#include "XCC EditorView.h"
#include "object_selection.h"
#include "string_conversion.h"
#include "xcc_cell.h"
#include "xcc_level.h"

class CMainFrame : public CFrameWnd
{
protected:
	DECLARE_DYNCREATE(CMainFrame)

public:
	Cxcc_cell m_mouse_pos;
	string m_object_name;
	Cobject_selection* m_selection_pane;
	CXCCEditorView* m_level_pane;

	t_side_id default_side() const;
	t_action_id default_action() const;
	CComboBox& combo_side() const;
	CComboBox& combo_action() const;
	void set_statusbar_cx_pane(UINT id, long cx);

protected:
	CSplitterWnd	m_splitter;
	CStatusBar  m_wndStatusBar;
	CDialogBar m_wndPropertyBar;
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
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
