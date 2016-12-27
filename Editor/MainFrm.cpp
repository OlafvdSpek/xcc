#include "stdafx.h"
#include "MainFrm.h"

#include "edit_infantry_dlg.h"
#include "edit_structures_dlg.h"
#include "edit_units_dlg.h"
#include "xcc_log.h"

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND_EX(CG_ID_VIEW_PROPERTYBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_PROPERTYBAR, OnUpdateControlBarMenu)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_STRUCTURES, OnEditEditStructures)
	ON_COMMAND(ID_EDIT_UNITS, OnEditEditUnits)
	ON_COMMAND(ID_EDIT_INFANTRY, OnEditEditInfantry)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_CELL, OnUpdateCell)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CELL
};

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_wndPropertyBar.Create(this, CG_IDD_PROPERTYBAR, CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE, CG_ID_VIEW_PROPERTYBAR))
	{
		TRACE0("Failed to create dialog bar m_wndPropertyBar\n");
		return -1;		// fail to create
	}

	m_wndPropertyBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndPropertyBar);

	for (int i = 0; i < c_side_id; i++)
	{
		combo_side().SetItemData(combo_side().AddString(side_code[i]), i);
	}
		
	for (int i = 0; action_code[i]; i++)
	{
		combo_action().SetItemData(combo_action().AddString(action_code[i]), i);
	}

	combo_side().SelectString(-1, side_code[s_neutral]);
	combo_action().SelectString(-1, action_code[a_guard]);

	return 0;
}

void CMainFrame::OnIdleUpdateCmdUI()
{
	SetMessageText(m_object_name.c_str());
};

void CMainFrame::OnUpdateCell(CCmdUI *pCmdUI)
{
	OnIdleUpdateCmdUI();
	string text = "";
	if (m_mouse_pos.x != -1)
	{
		long x = 100 * m_mouse_pos.x >> 8;
		long y = 100 * m_mouse_pos.y >> 8;
		text = nwzl(2, x / 100) + ',' + nwzl(2, x % 100) + ";" + nwzl(2, y / 100) + ',' + nwzl(2, y % 100) + nwsl(5, m_mouse_pos.get_cc()) + nwsl(2, m_mouse_pos.subcell());
	}
	set_statusbar_cx_pane(ID_INDICATOR_CELL, 120);
	pCmdUI->SetText(text.c_str());
}

void CMainFrame::OnEditEditInfantry() 
{
	Cedit_infantry_dlg dlg;
	dlg.DoModal();	
}

void CMainFrame::OnEditEditStructures() 
{
	Cedit_structures_dlg dlg;
	dlg.DoModal();	
}

void CMainFrame::OnEditEditUnits() 
{
	Cedit_units_dlg dlg;
	dlg.DoModal();	
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (!m_splitter.CreateStatic(this, 1, 2))
		return false;
	if (!m_splitter.CreateView(0, 0, RUNTIME_CLASS(Cobject_selection), CSize(200, 0), pContext))
		return false;
	if (!m_splitter.CreateView(0, 1, pContext->m_pNewViewClass, CSize(0, 0), pContext))
		return false;
	m_selection_pane = reinterpret_cast<Cobject_selection*>(m_splitter.GetPane(0, 0));
	m_level_pane = reinterpret_cast<CXCCEditorView*>(m_splitter.GetPane(0, 1));
	if (!m_selection_pane || !m_level_pane)
		return false;
	SetActiveView((CView*)m_splitter.GetPane(0, 1));
	return true;
}

void CMainFrame::set_statusbar_cx_pane(UINT id, long _cx)
{
	int index = m_wndStatusBar.CommandToIndex(id);
	UINT style;
	int cx; 
	m_wndStatusBar.GetPaneInfo(index, id, style, cx);
	m_wndStatusBar.SetPaneInfo(index, id, style, _cx);
}

CComboBox& CMainFrame::combo_side() const
{
	return *static_cast<CComboBox*>(m_wndPropertyBar.GetDlgItem(IDC_COMBO_SIDE));
}

CComboBox& CMainFrame::combo_action() const
{
	return *static_cast<CComboBox*>(m_wndPropertyBar.GetDlgItem(IDC_COMBO_ACTION));
}

t_side_id CMainFrame::default_side() const
{
	return static_cast<t_side_id>(combo_side().GetItemData(combo_side().GetCurSel()));
}

t_action_id CMainFrame::default_action() const
{
	return static_cast<t_action_id>(combo_action().GetItemData(combo_action().GetCurSel()));
}
