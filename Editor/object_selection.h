#pragma once

#include "palet.h"
#include "xcc_infantry.h"
#include "xcc_level.h"
#include "xcc_overlays.h"
#include "xcc_structures.h"
#include "xcc_templates.h"
#include "xcc_units.h"

class Cobject_selection : public CScrollView
{
private:
	int m_context_subpos;
	bool m_mouse_leave_active;
	bool m_mouse_left;
	t_palet32bgr_entry m_color_table[256];
	bool m_color_table_valid;
	int m_current_object;

	CDC m_mem_dc;
	t_object_id m_loaded_selection_type = static_cast<t_object_id>(-1);
	dword m_loaded_selection_subtype;
	bool m_mem_surface_created = false;
	CSize m_mem_surface_size;
	bool m_mem_surface_valid = false;
	CRect m_object_pos[256];
	HBITMAP mh_dib;
	t_palet32bgr_entry* mp_dib;

	void draw_image(const byte* s, t_palet32bgr_entry* d, int sx, int sy, int dx, int dy, int cx, int cy);
	void draw_image(shp_images::t_image_data*, t_palet32bgr_entry* d, int sx, int sy, int dx, int dy);
protected:
	Cobject_selection();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(Cobject_selection)
public:
	void draw_filter(t_palet32bgr_entry* d, int dx, int dy, int cx, int cy, int tr, int tg, int tb, int vr = 0, int vg = 0, int vb = 0) const;
	void enable_mouse_event();
	void reset_current_object();
	t_object_id get_current_object_type() const;
	int get_current_object() const;
	void Invalidate();
	void load(t_object_id t, int i = 0);
	void load_infantry();
	void load_overlay();
	void load_structures();
	void load_templates();
	void load_units();
	void load_terrain();
	int get_object_at(const CPoint& pos) const;
	void clear_object_pos_list();
	const Cxcc_level& level() const;
	const t_theater_id theater() const;
	void update_mem_surface();

	//{{AFX_VIRTUAL(Cobject_selection)
public:
	virtual void OnInitialUpdate();     // first time after construct
protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	virtual ~Cobject_selection();
	//{{AFX_MSG(Cobject_selection)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPopupInfantry();
	afx_msg void OnPopupOverlay();
	afx_msg void OnPopupStructures();
	afx_msg void OnPopupTemplates();
	afx_msg void OnPopupTemplatesRoad();
	afx_msg void OnPopupTemplatesShore();
	afx_msg void OnPopupTemplatesRidge();
	afx_msg void OnPopupTemplatesRiver();
	afx_msg void OnPopupTerrain();
	afx_msg void OnPopupUnits();
	afx_msg void OnUpdatePopupInfantry(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePopupOverlay(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePopupStructures(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePopupTemplates(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePopupTemplatesRidge(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePopupTemplatesRiver(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePopupTerrain(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePopupUnits(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePopupTemplatesRoad(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePopupTemplatesShore(CCmdUI* pCmdUI);
	afx_msg void OnPopupStructuresCivilian();
	afx_msg void OnUpdatePopupStructuresCivilian(CCmdUI* pCmdUI);
	afx_msg void OnPopupBlocked();
	afx_msg void OnUpdatePopupBlocked(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
