#pragma once

#include <windows.h>
#include "edit_teamtypes_dlg.h"
#include "edit_triggers_dlg.h"
#include "edit_waypoints_dlg.h"
#include "open_from_mix_dlg.h"
#include "xcc_cell.h"
#include "xcc_draw.h"
#include "xcc_overlays.h"
#include "xcc_templates.h"

class CXCCEditorView : public CScrollView
{
protected: // create from serialization only
	enum t_layer_id
	{
		l_template, l_overlay, l_smudge, l_terrain,
			l_infantry, l_structure, l_unit,
			l_celltrigger, l_waypoint
	};

	bool m_creating_sel;
	Cxcc_cell m_sel_bp;
	Cxcc_cell m_sel_ep;
	Cxcc_cell m_mouse_pos;
	int m_current_object;
	t_object_id m_current_object_type;
	bool m_mouse_leave_active;
	bool m_mouse_left;
	Cxcc_cell m_temp_object_pos;
	CSize m_temp_object_size;
	Cxcc_cell m_context_pos;
	CXCCEditorView();
	DECLARE_DYNCREATE(CXCCEditorView)
	Cxcc_overlays overlays;
	Cxcc_templates templates;
	CDC m_MemDC;
	bool m_lock_template_layer;
	bool m_lock_overlay_layer;
	bool m_lock_smudge_layer;
	bool m_lock_terrain_layer;
	bool m_lock_infantry_layer;
	bool m_lock_structure_layer;
	bool m_lock_unit_layer;

	bool m_view_border_filter;
	bool m_view_moveable_filter;
	bool m_view_structure_blocked_filter;

	bool m_view_template_layer;
	bool m_view_overlay_layer;
	bool m_view_smudge_layer;
	bool m_view_terrain_layer;
	bool m_view_infantry_layer;
	bool m_view_structure_layer;
	bool m_view_unit_layer;

	bool m_view_celltrigger_layer;
	bool m_view_waypoint_layer;

	bool m_MemDCCreated;
	bool m_MemDCValid;
	array<t_palet32bgr_entry, 256> m_color_table;
	HBITMAP mh_dib;
	dword* mp_dib;

// Attributes
public:
	CXCCEditorDoc* GetDocument() const;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCEditorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void sel_fill_with_wall(dword t);
	void get_selection(Cxcc_cell& a, Cxcc_cell& b) const;
	CRect get_selection() const;
	Cxcc_cell get_cell_from_point(const CPoint& point);
	CPoint CXCCEditorView::get_point_from_cell(const Cxcc_cell& cell);
	static const byte* get_rp(t_object_id type, t_side_id side);
	void update_current_object(const Cxcc_cell& cell);
	void on_mouse_entered();
	void on_mouse_left();
	void enable_mouse_event();
	void erase_temp_object();
	Cxcc_level& level() const;
	t_side_id main_opponent() const;
	void draw_image(const byte* s, const byte* rp, dword* d, dword sx, dword sy, dword dx, dword dy, dword cx, dword cy, dword dpitch);
	void draw_template(dword v, dword* d, dword dx, dword dy, dword dpitch, bool red, bool blue);
	void draw_overlay(dword v, dword* d, dword dx, dword dy, dword dpitch);
	void draw_terrain(dword v, dword* d, dword dx, dword dy, dword dpitch);
	void draw_structure(dword v, int angle, const byte* rp, dword* d, dword dx, dword dy, dword dpitch, bool bib);
	void draw_infantry(const xcc_infantry::t_infantry_data_entry&, int angle, const byte* rp, dword* d, dword dx, dword dy, dword dpitch);
	void draw_unit(dword v, int angle, const byte* rp, dword* d, dword dx, dword dy, dword dpitch);
	void Invalidate(bool mem_surface);
	void update_mem_surface();
	virtual ~CXCCEditorView();

protected:

// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CXCCEditorView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSwitchMoveable();
	afx_msg void OnUpdateSwitchMoveable(CCmdUI* pCmdUI);
	afx_msg void OnViewMoveableFilter();
	afx_msg void OnUpdateViewMoveableFilter(CCmdUI* pCmdUI);
	afx_msg void OnFileOpenFromMix();
	afx_msg void OnViewOverlayLayer();
	afx_msg void OnUpdateViewOverlayLayer(CCmdUI* pCmdUI);
	afx_msg void OnViewTerrainLayer();
	afx_msg void OnUpdateViewTerrainLayer(CCmdUI* pCmdUI);
	afx_msg void OnViewUpdate();
	afx_msg void OnFileSaveAsImage();
	afx_msg void OnViewBorderFilter();
	afx_msg void OnUpdateViewBorderFilter(CCmdUI* pCmdUI);
	afx_msg void OnViewStructureblockedfilter();
	afx_msg void OnUpdateViewStructureblockedfilter(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditLockInfantryLayer();
	afx_msg void OnEditLockOverlayLayer();
	afx_msg void OnEditLockSmudgeLayer();
	afx_msg void OnEditLockStructureLayer();
	afx_msg void OnEditLockTemplateLayer();
	afx_msg void OnEditLockTerrainLayer();
	afx_msg void OnEditLockUnitLayer();
	afx_msg void OnUpdateEditLockInfantryLayer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditLockOverlayLayer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditLockSmudgeLayer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditLockStructureLayer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditLockTemplateLayer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditLockTerrainLayer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditLockUnitLayer(CCmdUI* pCmdUI);
	afx_msg void OnViewInfantryLayer();
	afx_msg void OnUpdateViewInfantryLayer(CCmdUI* pCmdUI);
	afx_msg void OnViewStructureLayer();
	afx_msg void OnUpdateViewStructureLayer(CCmdUI* pCmdUI);
	afx_msg void OnViewUnitLayer();
	afx_msg void OnUpdateViewUnitLayer(CCmdUI* pCmdUI);
	afx_msg void OnViewTemplateLayer();
	afx_msg void OnUpdateViewTemplateLayer(CCmdUI* pCmdUI);
	afx_msg void OnViewSmudgeLayer();
	afx_msg void OnUpdateViewSmudgeLayer(CCmdUI* pCmdUI);
	afx_msg void OnViewCelltriggerLayer();
	afx_msg void OnUpdateViewCelltriggerLayer(CCmdUI* pCmdUI);
	afx_msg void OnViewWaypointLayer();
	afx_msg void OnUpdateViewWaypointLayer(CCmdUI* pCmdUI);
	afx_msg void OnEditWaypoints();
	afx_msg void OnEditTriggers();
	afx_msg void OnPopupSetWaypoint();
	afx_msg void OnPopupSetCelltrigger();
	afx_msg void OnEditTeamtypes();
	afx_msg void OnEditBasic();
	afx_msg void OnEditMap();
	afx_msg void OnEditGoodguy();
	afx_msg void OnEditBadguy();
	afx_msg void OnEditNeutral();
	afx_msg void OnEditSpecial();
	afx_msg void OnEditMulti1();
	afx_msg void OnEditMulti2();
	afx_msg void OnEditMulti3();
	afx_msg void OnEditMulti4();
	afx_msg void OnEditMulti5();
	afx_msg void OnEditMulti6();
	afx_msg void OnPopupDelete();
	afx_msg void OnUpdatePopupDelete(CCmdUI* pCmdUI);
	afx_msg void OnPopupProperties();
	afx_msg void OnUpdatePopupProperties(CCmdUI* pCmdUI);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPopupFillWithCelltriggers();
	afx_msg void OnPopupFillWithTiberium();
	afx_msg void OnPopupFillWithWater();
	afx_msg void OnUpdatePopupFillWithWater(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePopupFillWithTiberium(CCmdUI* pCmdUI);
	afx_msg void OnPopupFillWithSandbagWall();
	afx_msg void OnPopupFillWithConcreteWall();
	afx_msg void OnPopupFillWithChainLinkFence();
	afx_msg void OnToolsEnergyStatus();
	afx_msg void OnEditBriefing();
	afx_msg void OnToolsUpgradeTiberium();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg void OnPopupClearLayer(UINT nID);
	afx_msg void OnUpdatePopupClearLayer(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

inline CXCCEditorDoc* CXCCEditorView::GetDocument() const
{
	return (CXCCEditorDoc*)m_pDocument;
}

inline Cxcc_level& CXCCEditorView::level() const
{
	return GetDocument()->level;
}

inline t_side_id CXCCEditorView::main_opponent() const
{
	return level().basic_data.player == s_goodguy ? s_badguy : s_goodguy;
}
