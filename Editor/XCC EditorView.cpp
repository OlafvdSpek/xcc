#include "stdafx.h"

#include "MainFrm.h"
#include "XCC EditorDoc.h"
#include "XCC EditorView.h"
#include "resource.h"
#include "edit_basic_dlg.h"
#include "edit_map_dlg.h"
#include "edit_briefing_dlg.h"
#include "edit_side_dlg.h"
#include "edit_infantry_properties_dlg.h"
#include "edit_structure_properties_dlg.h"
#include "edit_unit_properties_dlg.h"
#include "energy_status_dlg.h"
#include "shp_images.h"
#include "xcc_cell_manager.h"
#include "windows.h"

IMPLEMENT_DYNCREATE(CXCCEditorView, CScrollView)

BEGIN_MESSAGE_MAP(CXCCEditorView, CScrollView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CXCCEditorView)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_SWITCH_MOVEABLE, OnSwitchMoveable)
	ON_UPDATE_COMMAND_UI(ID_SWITCH_MOVEABLE, OnUpdateSwitchMoveable)
	ON_COMMAND(ID_VIEW_MOVEABLE_FILTER, OnViewMoveableFilter)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MOVEABLE_FILTER, OnUpdateViewMoveableFilter)
	ON_COMMAND(ID_FILE_OPEN_FROM_MIX, OnFileOpenFromMix)
	ON_COMMAND(ID_VIEW_OVERLAY_LAYER, OnViewOverlayLayer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OVERLAY_LAYER, OnUpdateViewOverlayLayer)
	ON_COMMAND(ID_VIEW_TERRAIN_LAYER, OnViewTerrainLayer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TERRAIN_LAYER, OnUpdateViewTerrainLayer)
	ON_COMMAND(ID_VIEW_UPDATE, OnViewUpdate)
	ON_COMMAND(ID_FILE_SAVE_AS_IMAGE, OnFileSaveAsImage)
	ON_COMMAND(ID_VIEW_BORDER_FILTER, OnViewBorderFilter)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BORDER_FILTER, OnUpdateViewBorderFilter)
	ON_COMMAND(ID_VIEW_STRUCTURE_BLOCKED_FILTER, OnViewStructureblockedfilter)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STRUCTURE_BLOCKED_FILTER, OnUpdateViewStructureblockedfilter)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_EDIT_LOCK_INFANTRY_LAYER, OnEditLockInfantryLayer)
	ON_COMMAND(ID_EDIT_LOCK_OVERLAY_LAYER, OnEditLockOverlayLayer)
	ON_COMMAND(ID_EDIT_LOCK_SMUDGE_LAYER, OnEditLockSmudgeLayer)
	ON_COMMAND(ID_EDIT_LOCK_STRUCTURE_LAYER, OnEditLockStructureLayer)
	ON_COMMAND(ID_EDIT_LOCK_TEMPLATE_LAYER, OnEditLockTemplateLayer)
	ON_COMMAND(ID_EDIT_LOCK_TERRAIN_LAYER, OnEditLockTerrainLayer)
	ON_COMMAND(ID_EDIT_LOCK_UNIT_LAYER, OnEditLockUnitLayer)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LOCK_INFANTRY_LAYER, OnUpdateEditLockInfantryLayer)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LOCK_OVERLAY_LAYER, OnUpdateEditLockOverlayLayer)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LOCK_SMUDGE_LAYER, OnUpdateEditLockSmudgeLayer)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LOCK_STRUCTURE_LAYER, OnUpdateEditLockStructureLayer)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LOCK_TEMPLATE_LAYER, OnUpdateEditLockTemplateLayer)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LOCK_TERRAIN_LAYER, OnUpdateEditLockTerrainLayer)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LOCK_UNIT_LAYER, OnUpdateEditLockUnitLayer)
	ON_COMMAND(ID_VIEW_INFANTRY_LAYER, OnViewInfantryLayer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_INFANTRY_LAYER, OnUpdateViewInfantryLayer)
	ON_COMMAND(ID_VIEW_STRUCTURE_LAYER, OnViewStructureLayer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STRUCTURE_LAYER, OnUpdateViewStructureLayer)
	ON_COMMAND(ID_VIEW_UNIT_LAYER, OnViewUnitLayer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_UNIT_LAYER, OnUpdateViewUnitLayer)
	ON_COMMAND(ID_VIEW_TEMPLATE_LAYER, OnViewTemplateLayer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TEMPLATE_LAYER, OnUpdateViewTemplateLayer)
	ON_COMMAND(ID_VIEW_SMUDGE_LAYER, OnViewSmudgeLayer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SMUDGE_LAYER, OnUpdateViewSmudgeLayer)
	ON_COMMAND(ID_VIEW_CELLTRIGGER_LAYER, OnViewCelltriggerLayer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CELLTRIGGER_LAYER, OnUpdateViewCelltriggerLayer)
	ON_COMMAND(ID_VIEW_WAYPOINT_LAYER, OnViewWaypointLayer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WAYPOINT_LAYER, OnUpdateViewWaypointLayer)
	ON_COMMAND(ID_EDIT_WAYPOINTS, OnEditWaypoints)
	ON_COMMAND(ID_EDIT_TRIGGERS, OnEditTriggers)
	ON_COMMAND(ID_POPUP_SET_WAYPOINT, OnPopupSetWaypoint)
	ON_COMMAND(ID_POPUP_SET_CELLTRIGGER, OnPopupSetCelltrigger)
	ON_COMMAND(ID_EDIT_TEAMTYPES, OnEditTeamtypes)
	ON_COMMAND(ID_EDIT_BASIC, OnEditBasic)
	ON_COMMAND(ID_EDIT_MAP, OnEditMap)
	ON_COMMAND(ID_EDIT_GOODGUY, OnEditGoodguy)
	ON_COMMAND(ID_EDIT_BADGUY, OnEditBadguy)
	ON_COMMAND(ID_EDIT_NEUTRAL, OnEditNeutral)
	ON_COMMAND(ID_EDIT_SPECIAL, OnEditSpecial)
	ON_COMMAND(ID_EDIT_MULTI1, OnEditMulti1)
	ON_COMMAND(ID_EDIT_MULTI2, OnEditMulti2)
	ON_COMMAND(ID_EDIT_MULTI3, OnEditMulti3)
	ON_COMMAND(ID_EDIT_MULTI4, OnEditMulti4)
	ON_COMMAND(ID_EDIT_MULTI5, OnEditMulti5)
	ON_COMMAND(ID_EDIT_MULTI6, OnEditMulti6)
	ON_COMMAND(ID_POPUP_DELETE, OnPopupDelete)
	ON_UPDATE_COMMAND_UI(ID_POPUP_DELETE, OnUpdatePopupDelete)
	ON_COMMAND(ID_POPUP_PROPERTIES, OnPopupProperties)
	ON_UPDATE_COMMAND_UI(ID_POPUP_PROPERTIES, OnUpdatePopupProperties)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_POPUP_FILL_WITH_CELLTRIGGERS, OnPopupFillWithCelltriggers)
	ON_COMMAND(ID_POPUP_FILL_WITH_TIBERIUM, OnPopupFillWithTiberium)
	ON_COMMAND(ID_POPUP_FILL_WITH_WATER, OnPopupFillWithWater)
	ON_UPDATE_COMMAND_UI(ID_POPUP_FILL_WITH_WATER, OnUpdatePopupFillWithWater)
	ON_UPDATE_COMMAND_UI(ID_POPUP_FILL_WITH_TIBERIUM, OnUpdatePopupFillWithTiberium)
	ON_COMMAND(ID_POPUP_FILL_WITH_SANDBAG_WALL, OnPopupFillWithSandbagWall)
	ON_COMMAND(ID_POPUP_FILL_WITH_CONCRETE_WALL, OnPopupFillWithConcreteWall)
	ON_COMMAND(ID_POPUP_FILL_WITH_CHAIN_LINK_FENCE, OnPopupFillWithChainLinkFence)
	ON_COMMAND(ID_TOOLS_ENERGY_STATUS, OnToolsEnergyStatus)
	ON_COMMAND(ID_EDIT_BRIEFING, OnEditBriefing)
	ON_COMMAND(ID_TOOLS_UPGRADE_TIBERIUM, OnToolsUpgradeTiberium)
	ON_UPDATE_COMMAND_UI(ID_POPUP_FILL_WITH_CHAIN_LINK_FENCE, OnUpdatePopupFillWithTiberium)
	ON_UPDATE_COMMAND_UI(ID_POPUP_FILL_WITH_CONCRETE_WALL, OnUpdatePopupFillWithTiberium)
	ON_UPDATE_COMMAND_UI(ID_POPUP_FILL_WITH_SANDBAG_WALL, OnUpdatePopupFillWithTiberium)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_UPGRADE_TIBERIUM, OnUpdatePopupFillWithTiberium)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_POPUP_CLEAR_TEMPLATE_LAYER, ID_POPUP_CLEAR_WAYPOINT_LAYER, OnPopupClearLayer)
	ON_UPDATE_COMMAND_UI_RANGE(ID_POPUP_CLEAR_TEMPLATE_LAYER, ID_POPUP_CLEAR_WAYPOINT_LAYER, OnUpdatePopupClearLayer)
END_MESSAGE_MAP()

CXCCEditorView::CXCCEditorView()
{
	m_mouse_leave_active = false;
	m_mouse_left = true;
	m_MemDCCreated = false;
	m_temp_object_size.cx = 0;
}

CXCCEditorView::~CXCCEditorView()
{
	if (m_MemDCCreated)
		DeleteObject(mh_dib);
}

BOOL CXCCEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

const Cxcc_cell level_topleft(8 << 8, 8 << 8);

void CXCCEditorView::OnDraw(CDC* pDC)
{
	if (!m_MemDCCreated)
	{
		// create memory device context
		m_MemDC.CreateCompatibleDC(pDC);

		BITMAPINFO bmi;
		ZeroMemory(&bmi, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = 24 * 64;
		bmi.bmiHeader.biHeight = -24 * 64;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = bmi.bmiHeader.biWidth * -bmi.bmiHeader.biHeight * (bmi.bmiHeader.biBitCount >> 3);
		
		mh_dib = CreateDIBSection(*pDC, &bmi, DIB_RGB_COLORS, reinterpret_cast<void**>(&mp_dib), 0, 0);
		assert(mh_dib && mp_dib);
		m_MemDC.SelectObject(mh_dib);
		m_MemDC.SetBkMode(TRANSPARENT);
		m_MemDCCreated = true;
	}

	update_mem_surface();
	erase_temp_object();

	pDC->BitBlt(24 * 8, 24 * 8, 24 * 64, 24 * 64, &m_MemDC, 0, 0, SRCCOPY);
	// selection
	if (m_sel_bp.x != -1)
	{
		CRect rect((m_sel_bp + level_topleft).pixel(), (m_sel_ep + level_topleft).pixel());
		rect.NormalizeRect();
		rect.InflateRect(12, 12);
		pDC->FrameRect(rect, &CBrush(RGB(0xff, 0xff, 0xff)));
	}
}

inline static CMainFrame* main_frame()
{
	return static_cast<CMainFrame*>(AfxGetMainWnd());
}

inline static bool in_level(int x, int y)
{
	return CRect(0, 0, 64, 64).PtInRect(CPoint(x, y));
}

inline static bool in_level(const Cxcc_cell& v)
{
	return !(v.x < 0 || v.y < 0) && v.x < 64 << 8 && v.y < 64 << 8;
}

void CXCCEditorView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 24 * 80;
	SetScrollSizes(MM_TEXT, sizeTotal);
	ScrollToPosition(CPoint(8 * 24, 8 * 24));
	m_MemDCValid = false;
	m_creating_sel = false;
	m_sel_bp.x = -1;
	m_view_border_filter = true;
	m_view_moveable_filter = m_view_structure_blocked_filter = false;

	m_view_template_layer = m_view_overlay_layer = m_view_smudge_layer = m_view_terrain_layer = true;
	m_view_infantry_layer = m_view_structure_layer = m_view_unit_layer = true;
	m_view_celltrigger_layer = m_view_waypoint_layer = true;
	m_lock_template_layer = m_lock_overlay_layer = m_lock_smudge_layer = m_lock_terrain_layer = false;
	m_lock_infantry_layer = m_lock_structure_layer = m_lock_unit_layer = false;

	shp_images::set_theater(level().map_data.theater);
	if (overlays.load_images(level().map_data.theater))
	{
		AfxMessageBox("Overlay load failed", MB_ICONEXCLAMATION);
	}
	if (templates.load_images(level().map_data.theater))
	{
		AfxMessageBox("Template load failed", MB_ICONEXCLAMATION);
	}
	if (xcc_infantry::load_images())
	{
		AfxMessageBox("Infantry load failed", MB_ICONEXCLAMATION);
	}
	if (xcc_structures::load_images(level().map_data.theater))
	{
		AfxMessageBox("Structures load failed", MB_ICONEXCLAMATION);
	}
	if (xcc_units::load_images())
	{
		AfxMessageBox("Units load failed", MB_ICONEXCLAMATION);
	}
	const t_palet& palet = templates.get_palet();
	for (int palet_index = 0; palet_index < 256; palet_index++)
	{
		m_color_table[palet_index].r = palet[palet_index].r;
		m_color_table[palet_index].g = palet[palet_index].g;
		m_color_table[palet_index].b = palet[palet_index].b;
	}
}

void CXCCEditorView::draw_image(const byte* s, const byte* rp, dword* d, dword sx, dword sy, dword dx, dword dy, dword cx, dword cy, dword dpitch)
{
	const dword shadow_mask = 0x007f7f7f;
	d += dx + dy * dpitch;
	for (int yp = 0; yp < cy; yp++)
	{
		for (int xp = 0; xp < cx; xp++)
		{
			dword v = *s++;
			if (v)
			{
				if (v == 4)
					*d = *d >> 1 & shadow_mask;
				else
					*d = m_color_table[rp ? rp[v] : v].v;
			}
			d++;
		}
		d += dpitch - cx;
	}
}

void CXCCEditorView::update_mem_surface()
{
	if (m_MemDCValid)
		return;
	xcc_cell_manager::add_all(level());

	// const byte* shade_rp = templates.get_shade_rp();
	const t_bin_data& bin_data = level().bin_data;
	const t_map_data& map_data = level().map_data;
	
	dword* dib = reinterpret_cast<dword*>(mp_dib);
	const int dib_cx = 24 * 64;
	const int dib_cy = 24 * 64;
	CRect a(CPoint(map_data.x, map_data.y), CSize(map_data.cx, map_data.cy));
	if (m_view_template_layer)
	{
		int cell_i = 0;
		for (int yi = 0; yi < 64; yi++)
		{
			for (int xi = 0; xi < 64; xi++)
			{
				int v = bin_data[cell_i++];
				draw_template(v, mp_dib, 24 * xi, 24 * yi, dib_cx, m_view_moveable_filter && templates.moveable(v), m_view_border_filter && !a.PtInRect(CPoint(xi, yi)));
			}
		}
	}
	else
		m_MemDC.BitBlt(0, 0, dib_cx, dib_cy, 0, 0, 0, BLACKNESS);
	if (m_view_overlay_layer)
	{
		for (auto& i : level().overlay_data)
		{
			Cxcc_cell cell;
			cell.set_xcc(i.first);
			int x = (cell.x >> 8) * 24;
			int y = (cell.y >> 8) * 24;
			draw_overlay(i.second, mp_dib, x, y, dib_cx);
		}
	}
	if (m_view_terrain_layer)
	{
		for (auto& i : level().terrain_data)
		{
			Cxcc_cell cell;
			cell.set_xcc(i.first);
			int x = (cell.x >> 8) * 24;
			int y = (cell.y >> 8) * 24;
			draw_terrain(i.second, mp_dib, x, y, dib_cx);
		}
	}
	if (m_view_structure_layer)
	{
		for (auto& i : level().structure_data)
		{
			int x = (i.cell.x >> 8) * 24;
			int y = (i.cell.y >> 8) * 24;
			draw_structure(*i.t, i.angle, xcc_draw::side_rp[i.side], mp_dib, x, y, dib_cx, true);
		}
	}
	if (m_view_infantry_layer)
	{
		for (auto& i : level().infantry_data)
		{
			int x = (24 * i.cell.x >> 8) - 27;
			int y = (24 * i.cell.y >> 8) - 15;
			draw_infantry(*i.t, i.angle, i.side == s_badguy ? xcc_draw::multi4_rp : xcc_draw::side_rp[i.side], mp_dib, x, y, dib_cx);
		}
	}
	if (m_view_unit_layer)
	{
		for (auto& i : level().unit_data)
		{
			const xcc_units::t_unit_data_entry& ud = *i.t;
			int x = (i.cell.x >> 8) * 24 + ud.base_ox;
			int y = (i.cell.y >> 8) * 24 + ud.base_oy;
			draw_unit(*i.t, i.angle, i.side == s_badguy && ~ud.flags & ud_flags_red ? xcc_draw::multi4_rp : xcc_draw::side_rp[i.side], mp_dib, x, y, dib_cx);
		}
	}
	if (m_view_celltrigger_layer)
	{
		for (auto& i : level().celltrigger_data)
		{
			Cxcc_cell cell;
			cell.set_cc(i.first);
			const CPoint p = cell.pixel();
			m_MemDC.SetTextColor(0xff8080);
			m_MemDC.TextOut(p.x - 12, p.y - 12, i.second.substr(0, 3).c_str());
		}
	}
	if (m_view_waypoint_layer)
	{
		for (int i = 0; i < 100; i++)
		{
			int v = level().waypoint_data[i];
			if (v == -1)
				continue;
			Cxcc_cell cell;
			cell.set_cc(v);
			const CPoint p = cell.pixel();
			m_MemDC.SetTextColor(0x00ffff);
			m_MemDC.TextOut(p.x - 12, p.y - 12, n(i).c_str());
		}
	}

	m_MemDCValid = true;
}

void CXCCEditorView::OnUpdate() 
{
#ifndef _DEBUG
	GetDocument()->SetModifiedFlag();
#endif
	Invalidate(true);
}

void CXCCEditorView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	const Cobject_selection& object_selection = *main_frame()->m_selection_pane;
	const t_object_id type = object_selection.get_current_object_type();
	const int lx = m_temp_object_pos.x >> 8;
	const int ly = m_temp_object_pos.y >> 8;
	int i = object_selection.get_current_object();
	if (i != -1)
	{
		switch (type)		
		{
		case oi_template:
			if (!m_lock_template_layer)
			{
				const t_template_data_entry& d = Cxcc_templates::get_template_data(i);
				int a = 0, b = 0;
				for (int y = 0; y < d.cy; y++)
				{
					for (int x = 0; x < d.cx; x++)
					{
						int x1 = lx + x;
						int y1 = ly + y;
						if ((Cxcc_templates::convert_bin_data(a++ << 8 | i) & 0xff) != 0xff)
						{
							if (in_level(x1, y1))
								level().bin_data[x1 | y1 << 6] = i << 8 | b;
							b++;
						}
					}
				}	
				OnUpdate();
			}
			break;
		case oi_overlay:
			if (!m_lock_overlay_layer && in_level(lx, ly))
			{
				level().overlay_data[lx | ly << 8] = convert_overlay_edit(i << 8);
				level().process();
				OnUpdate();
			}
			break;
		case oi_terrain:
			if (!m_lock_terrain_layer && in_level(lx, ly))
			{
				int t, cx, cy;
				Cxcc_overlays::get_terrain_image(i << 8, t, t, cx, cy);
				if (in_level(lx + cx / 24 - 1, ly + cy / 24 - 1))
				{
					level().terrain_data[lx | ly << 8] = i << 8;
					OnUpdate();			
				}
			}
			break;
		case oi_infantry:
			if (!m_lock_infantry_layer && in_level(lx + 1, ly + 1))
			{
				t_infantry_data_entry d;
				d.side = main_frame()->default_side();
				d.t = &xcc_infantry::infantry_data[i];
				d.health = 256;
				d.cell = Cxcc_cell(lx  + 1 << 8, ly + 1 << 8);
				d.cell.subcell(m_temp_object_pos.subcell());
				d.angle = 0;
				d.action = main_frame()->default_action();
				d.trigger = "none";
				level().infantry_data.push_back(d);
				OnUpdate();
			}
			break;
		case oi_structure:
			if (!m_lock_structure_layer && in_level(lx, ly))
			{
				const xcc_structures::t_structure_data_entry& td = xcc_structures::structure_data[i];
				if (in_level(lx + td.cx - 1, ly + td.cy - (td.flags & sd_flags_bib ? 0 : 1)))
				{
					t_structure_data_entry d;
					d.side = main_frame()->default_side();
					d.t = &xcc_structures::structure_data[i];
					d.health = 256;
					d.cell = m_temp_object_pos.center();
					d.angle = 0;
					d.trigger = "none";
					d.flags = sd_flags_start;
					if (main_opponent() == d.side)
						d.flags |= sd_flags_replace;
					level().structure_data.push_back(d);
					OnUpdate();
				}
			}
			break;
		case oi_unit:
			if (!m_lock_unit_layer && in_level(lx + 1, ly + 1))
			{
				t_unit_data_entry d;
				d.side = main_frame()->default_side();
				d.t = &xcc_units::unit_data[i];
				d.health = 256;
				d.cell = Cxcc_cell(lx + 1 << 8, ly + 1 << 8).center();
				d.angle = 0;
				d.action = main_frame()->default_action();
				d.trigger = "none";
				level().unit_data.push_back(d);
				OnUpdate();
			}
			break;
		}
	}	
	else
	{
		const Cxcc_cell cell = get_cell_from_point(point);
		if (in_level(cell))
		{
			m_sel_bp = m_sel_ep = cell.center();
			m_creating_sel = true;
		}
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

void CXCCEditorView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_creating_sel)
	{
		m_sel_ep = get_cell_from_point(point).center();
		if (!in_level(m_sel_ep) || m_sel_bp.x == m_sel_ep.x && m_sel_bp.y == m_sel_ep.y)
		{
			m_sel_bp.x = -1;
			Invalidate(false);
		}
		else
		{
			CRect rect(m_sel_bp.x, m_sel_bp.y, m_sel_ep.x, m_sel_ep.y);
			rect.NormalizeRect();
			m_sel_bp.x = rect.TopLeft().x;
			m_sel_bp.y = rect.TopLeft().y;
			m_sel_ep.x = rect.BottomRight().x;
			m_sel_ep.y = rect.BottomRight().y;
		}
		m_creating_sel = false;
	}
	CScrollView::OnLButtonUp(nFlags, point);
}

void CXCCEditorView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CScrollView::OnMouseMove(nFlags, point);
	m_mouse_left = false;
	enable_mouse_event();
	point += GetDeviceScrollPosition();
	point -= CPoint(8 * 24, 8 * 24);
	m_mouse_pos.pixel(point);
	update_current_object(m_mouse_pos);
	if (CRect(CPoint(0, 0), CSize(24 * 64, 24 * 64)).PtInRect(point))
	{
		main_frame()->m_mouse_pos = m_mouse_pos;	
		string& object_name = main_frame()->m_object_name;
		switch (m_current_object_type)
		{
		case oi_overlay:
			if (level().overlay_data.find(m_current_object) != level().overlay_data.end())
				object_name = overlay_code[level().overlay_data.find(m_current_object)->second >> 8];
			break;
		case oi_terrain:			
			if (level().terrain_data.find(m_current_object) != level().terrain_data.end())
				object_name = terrain_code[level().terrain_data.find(m_current_object)->second >> 8];
			break;
		case oi_infantry:
			object_name = level().infantry_data[m_current_object].t->long_name;
			break;
		case oi_structure:
			object_name = level().structure_data[m_current_object].t->long_name;
			break;
		case oi_unit:
			object_name = level().unit_data[m_current_object].t->long_name;
			break;
		default:
			object_name = template_code[level().bin_data[m_mouse_pos.get_cc()] >> 8];
		}
	}
	else
	{
		main_frame()->m_mouse_pos.x = -1;
		main_frame()->m_object_name.erase();
	}
	Cobject_selection& object_selection = *main_frame()->m_selection_pane;
	int i = object_selection.get_current_object();
	if (i == -1)
	{
		if (m_sel_bp.x != -1 && m_creating_sel && 
			in_level(m_mouse_pos) && m_sel_ep != m_mouse_pos.center())
		{
			m_sel_ep = m_mouse_pos.center();
			CRect rect(get_point_from_cell(m_sel_bp), get_point_from_cell(m_sel_ep));
			rect.NormalizeRect();
			rect.InflateRect(12, 12);
			// InvalidateRect(rect, false);
			Invalidate(false);
		}
		return;
	}
	else if (m_sel_bp.x != -1)
	{
		m_sel_bp.x = -1;
		Invalidate(false);
	}

	{
		Cxcc_cell temp_object_pos = m_mouse_pos;
		if (object_selection.get_current_object_type() != oi_infantry)
			temp_object_pos.force_center();
		switch (object_selection.get_current_object_type())		
		{
		case oi_infantry:
			temp_object_pos.force_subcell();
			// fall through
		case oi_unit:
			temp_object_pos -= Cxcc_cell(1 << 8, 1 << 8);
		}
		if (m_temp_object_size.cx && m_temp_object_pos == temp_object_pos)
			return;
		erase_temp_object();
		m_temp_object_pos = temp_object_pos;
	}
	point = (m_temp_object_pos.topleft() + Cxcc_cell(8 << 8, 8 << 8)).pixel() - GetDeviceScrollPosition();

	const int dib_cx = 8 * 24;
	const int dib_cy = 8 * 24;
	CDC* pDC = GetDC();
	CDC mem_dc;
	HBITMAP h_last_dib;
	HBITMAP h_dib;
	dword* p_dib;

	{
		mem_dc.CreateCompatibleDC(pDC);

		BITMAPINFO bmi;
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = dib_cx;
		bmi.bmiHeader.biHeight = -dib_cy;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = bmi.bmiHeader.biWidth * bmi.bmiHeader.biHeight * (bmi.bmiHeader.biBitCount >> 3);
		h_dib = CreateDIBSection(*pDC, &bmi, DIB_RGB_COLORS, reinterpret_cast<void**>(&p_dib), 0, 0);
		assert(h_dib && p_dib);
		h_last_dib = static_cast<HBITMAP>(mem_dc.SelectObject(h_dib));
	}
	
	mem_dc.BitBlt(0, 0, dib_cx, dib_cy, pDC, point.x, point.y, SRCCOPY);

	CSize& size = m_temp_object_size;

	switch (object_selection.get_current_object_type())
	{
	case oi_template:
		{
			const t_template_data_entry& td = Cxcc_templates::get_template_data(i);
			int j = 0;
			for (int y = 0; y < td.cy; y++)
			{
				for (int x = 0; x < td.cx; x++)
				{
					if ((Cxcc_templates::convert_bin_data(x + y * td.cx << 8 | i) & 0xff) != 0xff)
						draw_template(i << 8 | j++, p_dib, 24 * x, 24 * y, dib_cx, false, false);
				}
			}
			size.cx = 24 * td.cx;
			size.cy = 24 * td.cy;
			break;
		}
	case oi_overlay:
		{
			draw_overlay(convert_overlay_edit(i << 8), p_dib, 0, 0, dib_cx);
			size.cx = size.cy = 24;
			break;
		}
	case oi_terrain:
		{
			draw_terrain(i << 8, p_dib, 0, 0, dib_cx);
			int t;
			Cxcc_overlays::get_terrain_image(i << 8, t, t, size.cx, size.cy);
			break;
		}
	case oi_infantry:
		{
			const xcc_infantry::t_infantry_data_entry& id = xcc_infantry::infantry_data[i];
			Cxcc_cell base_cell;
			base_cell.subcell(m_mouse_pos.subcell());
			CPoint base_point = base_cell.pixel();
			draw_infantry(id, 0, get_rp(oi_infantry, main_frame()->default_side()), p_dib, 9 + base_point.x - 12, 21 + base_point.y - 12, dib_cx);			
			size.SetSize(id.images->cx + 24, id.images->cy + 24);
			break;
		}
	case oi_structure:
		{
			const xcc_structures::t_structure_data_entry& sd = xcc_structures::structure_data[i];
			draw_structure(sd, 0, get_rp(oi_structure, main_frame()->default_side()), p_dib, 0, 0, dib_cx, false);			
			size.SetSize(sd.images->cx, sd.images->cy);
			break;
		}
	case oi_unit:
		{
			const xcc_units::t_unit_data_entry& ud = xcc_units::unit_data[i];
			draw_unit(ud, 0, get_rp(oi_unit, main_frame()->default_side()), p_dib, 24 + ud.base_ox, 24 + ud.base_oy, dib_cx);			
			size.SetSize(ud.images->cx + 24, ud.images->cy + 24);
			break;
		}
	}
	pDC->BitBlt(point.x, point.y, size.cx, size.cy, &mem_dc, 0, 0, SRCCOPY);
	mem_dc.SelectObject(h_last_dib);
	DeleteObject(h_dib);
	ReleaseDC(pDC);
}

void CXCCEditorView::OnContextMenu(CWnd*, CPoint point)
{
	if (point.x == -1)
		return;
	Cobject_selection& object_selection = *main_frame()->m_selection_pane;
	if (object_selection.get_current_object() != -1)
	{
		object_selection.reset_current_object();
		erase_temp_object();
		return;
	}
	CPoint context_menu_pos = GetDeviceScrollPosition() + point - CPoint(8 * 24, 8 * 24);
	ScreenToClient(&context_menu_pos);
	if (!CRect(CPoint(0, 0), CSize(24 * 64, 24 * 64)).PtInRect(context_menu_pos))
		return;
	m_context_pos.pixel(context_menu_pos);
	CMenu menu;
	VERIFY(menu.LoadMenu(CG_IDR_POPUP_XCCEDITOR_VIEW));
	
	CMenu* pPopup = menu.GetSubMenu(m_sel_bp.x == -1 ? 0 : 1);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;
	
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
	
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
}

void CXCCEditorView::OnSwitchMoveable() 
{
	const dword v = level().bin_data[m_context_pos.get_cc()];
	templates.moveable(v, !templates.moveable(v));
	Invalidate(true);
}

void CXCCEditorView::OnUpdateSwitchMoveable(CCmdUI* pCmdUI) 
{
	const dword v = level().bin_data[m_context_pos.get_cc()];
	pCmdUI->Enable(m_view_moveable_filter && !m_view_terrain_layer);
	pCmdUI->SetCheck(!templates.moveable(v));
}

void CXCCEditorView::OnViewBorderFilter() 
{
	m_view_border_filter = !m_view_border_filter;
	Invalidate(true);
}

void CXCCEditorView::OnUpdateViewBorderFilter(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_view_border_filter);
}

void CXCCEditorView::OnViewMoveableFilter() 
{
	m_view_moveable_filter = !m_view_moveable_filter;
	Invalidate(true);
}

void CXCCEditorView::OnUpdateViewMoveableFilter(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_view_moveable_filter);
}


void CXCCEditorView::OnViewStructureblockedfilter() 
{
	m_view_structure_blocked_filter = !m_view_structure_blocked_filter;
	Invalidate(true);
}

void CXCCEditorView::OnUpdateViewStructureblockedfilter(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_view_structure_blocked_filter);
}

void CXCCEditorView::Invalidate(bool mem_surface)
{
	if (mem_surface)
		m_MemDCValid = false;
	CScrollView::Invalidate(false);
}

void CXCCEditorView::OnFileOpenFromMix() 
{
	CXCCEditorDoc* pDoc = GetDocument();
	Copen_from_mix_dlg dlg;
	if (dlg.DoModal() != IDOK 
		|| !pDoc->OnNewDocument())
		return;
	Cvirtual_binary bin_d;
	Cvirtual_binary ini_d;
	string name;
	dlg.get_selected_f(bin_d, ini_d, name);
	pDoc->load(bin_d, ini_d);
	main_frame()->InitialUpdateFrame(GetDocument(), true);
	pDoc->SetTitle(name.c_str());
}

void CXCCEditorView::OnViewUpdate() 
{
	Invalidate(true);	
}

void CXCCEditorView::OnFileSaveAsImage() 
{
	CFileDialog dlg(false, "bmp", 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, "BMP files|*.bmp|", this);
	Cfname fname = static_cast<string>(GetDocument()->GetTitle());
	fname.set_ext("");
	char s[MAX_PATH];
	strcpy(s, fname.get_all().c_str()); 
	dlg.m_ofn.lpstrFile = s;
	if (IDOK == dlg.DoModal())
	{
		update_mem_surface();
		const int cx = 24 * 64;
		const int cy = 24 * 64;
		t_palet24bgr_entry* memory_image = new t_palet24bgr_entry[cx * cy];
		t_palet32bgr_entry* read_p = reinterpret_cast<t_palet32bgr_entry*>(mp_dib);
		for (int y = 0; y < cy; y++)
		{
			t_palet24bgr_entry* write_p = memory_image + cx * (cy - 1 - y);
			for (int x = 0; x < cx; x++)
			{
				write_p->r = read_p->r;
				write_p->g = read_p->g;
				write_p->b = read_p->b;
				read_p++;
				write_p++;
			}
		}
		Cfile32 f;
		BITMAPFILEHEADER bmfh;
		ZeroMemory(&bmfh, sizeof(BITMAPFILEHEADER));
		bmfh.bfType = 'M' << 8 | 'B';
		bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO);
		bmfh.bfSize = bmfh.bfOffBits + 3 * cx * cy;
		BITMAPINFO bmi;
		ZeroMemory(&bmi, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = cx;
		bmi.bmiHeader.biHeight = cy;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 24;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = 3 * cx * cy;
		bmi.bmiHeader.biXPelsPerMeter = 24000;
		bmi.bmiHeader.biYPelsPerMeter = 24000;

		if (f.open_write(static_cast<string>(dlg.GetPathName())))
		{
			AfxMessageBox("Error saving file");
			return;
		}
		f.write(&bmfh, sizeof(BITMAPFILEHEADER));
		f.write(&bmi, sizeof(BITMAPINFO));
		f.write(memory_image, 3 * cx * cy);
		delete[] memory_image;
	}	
}

void CXCCEditorView::draw_template(dword v, dword* d, dword dx, dword dy, dword dpitch, bool red, bool blue)
{
	d += dx + dy * dpitch;
	const byte* s = templates.get_image(v);
	for (int yp = 0; yp < 24; yp++)
	{
		for (int xp = 0; xp < 24; xp++)
		{
			t_palet32bgr_entry v = m_color_table[*s++];
			if (blue)
				v.b = v.b >> 1 | 0x80;
			if (red)
			{
				v.g >>= 1;
				v.r = v.r >> 2 | 0xc0;
			}
			*d++ = v.v;
		}
		d += dpitch - 24;
	}
}

void CXCCEditorView::draw_overlay(dword v, dword* d, dword dx, dword dy, dword dpitch)
{
	int ox, oy, cx, cy;
	const byte* s = overlays.get_overlay_image(v, ox, oy, cx, cy);
	draw_image(s, 0, d, 0, 0, dx + ox, dy + oy, cx, cy, dpitch);
}

void CXCCEditorView::draw_terrain(dword v, dword* d, dword dx, dword dy, dword dpitch)
{
	int ox, oy, cx, cy;
	const byte* s = overlays.get_terrain_image(v, ox, oy, cx, cy);
	draw_image(s, 0, d, 0, 0, dx + ox, dy + oy, cx, cy, dpitch);
}

int convert_angle(int angle, int c_rotations)
{
	return (256 - angle & 0xff) * c_rotations >> 8;
}

void CXCCEditorView::draw_structure(const xcc_structures::t_structure_data_entry& sd, int angle, const byte* rp,dword* d, dword dx, dword dy, dword dpitch, bool bib)
{
	int cx, cy;
	if (bib && sd.flags & sd_flags_bib)
	{
		int i = 0;
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < sd.cx; x++)
				draw_image(templates.get_bib(sd.cx - 2)->get(i++), 0, d, 0, 0, dx + 24 * x, dy + 24 * (sd.cy - 1 + y), 24, 24, dpitch);
		}
	}
	const int sub_image = convert_angle(angle, sd.short_name == "gun" ? 0 : 32);
	const byte* s = sd.images->get(sub_image, cx, cy);
	draw_image(s, rp, d, 0, 0, dx, dy, cx, cy, dpitch);
	if (sd.flags & sd_flags_images2)
	{
		s = sd.images2->get(sub_image, cx, cy);
		draw_image(s, rp, d, 0, 0, dx, dy, cx, cy, dpitch);
	}
}

void CXCCEditorView::draw_infantry(const xcc_infantry::t_infantry_data_entry& id, int angle, const byte* rp, dword* d, dword dx, dword dy, dword dpitch)
{
	int cx, cy;
	const byte* s = id.images->get((256 - angle & 0xff) * 8 >> 8, cx, cy);
	draw_image(s, rp, d, 0, 0, dx, dy, cx, cy, dpitch);
}

void CXCCEditorView::draw_unit(const xcc_units::t_unit_data_entry& ud, int angle, const byte* rp, dword* d, dword dx, dword dy, dword dpitch)
{
	int cx, cy;
	const byte* s = ud.images->get((256 - angle & 0xff) * ud.c_rotations >> 8, cx, cy);
	draw_image(s, rp, d, 0, 0, dx, dy, cx, cy, dpitch);
	if (ud.flags & ud_flags_top)
	{
		s = ud.images->get(32, cx, cy);
		draw_image(s, rp, d, 0, 0, dx, dy, cx, cy, dpitch);
	}
}

void CXCCEditorView::erase_temp_object()
{
	if (!m_temp_object_size.cx)
		return;
	CDC* pDC = GetDC();
	const Cxcc_cell draw_pos = m_temp_object_pos.topleft();
	const CPoint window_pos = (draw_pos + Cxcc_cell(8 << 8, 8 << 8)).pixel() - GetDeviceScrollPosition();
	for (int y = 0; y < (m_temp_object_size.cy + 23) / 24; y++)
	{
		for (int x = 0; x < (m_temp_object_size.cx + 23) / 24; x++)
		{
			if (!CRect(0, 0, 64, 64).PtInRect(CPoint((draw_pos.x >> 8) + x, (draw_pos.y >> 8) + y)))
			{
				pDC->BitBlt(window_pos.x + 24 * x, window_pos.y + 24 * y, 
					24, 24, 0,
					0, 0, WHITENESS);
			}
		}
	}
	update_mem_surface();
	pDC->BitBlt(window_pos.x, window_pos.y, 
		m_temp_object_size.cx, m_temp_object_size.cy, &m_MemDC, 
		draw_pos.pixel().x, draw_pos.pixel().y, SRCCOPY);
	ReleaseDC(pDC);
	m_temp_object_size.cx = 0;
}

void CXCCEditorView::enable_mouse_event()
{
	if (m_mouse_leave_active)
		return;
	TRACKMOUSEEVENT d;
	d.cbSize = sizeof(TRACKMOUSEEVENT);
	d.dwFlags = TME_LEAVE;
	d.hwndTrack = m_hWnd;
	m_mouse_leave_active = true;
	_TrackMouseEvent(&d);
}

LRESULT CXCCEditorView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message)
	{
	case WM_MOUSELEAVE:
		m_mouse_leave_active = false;
		m_mouse_left = true;
		on_mouse_left();
		break;
	}

	return CScrollView::WindowProc(message, wParam, lParam);
}

void CXCCEditorView::on_mouse_entered()
{

}

void CXCCEditorView::on_mouse_left()
{
	erase_temp_object();
	main_frame()->m_object_name.erase();
}

void CXCCEditorView::OnEditLockInfantryLayer() 
{
	m_lock_infantry_layer = !m_lock_infantry_layer;
}

void CXCCEditorView::OnEditLockOverlayLayer() 
{
	m_lock_overlay_layer = !m_lock_overlay_layer;
}

void CXCCEditorView::OnEditLockSmudgeLayer() 
{
	m_lock_smudge_layer = !m_lock_smudge_layer;
}

void CXCCEditorView::OnEditLockStructureLayer() 
{
	m_lock_structure_layer = !m_lock_structure_layer;
}

void CXCCEditorView::OnEditLockTemplateLayer() 
{
	m_lock_template_layer = !m_lock_template_layer;
}

void CXCCEditorView::OnEditLockTerrainLayer() 
{
	m_lock_terrain_layer = !m_lock_terrain_layer;
}

void CXCCEditorView::OnEditLockUnitLayer() 
{
	m_lock_unit_layer = !m_lock_unit_layer;
}

void CXCCEditorView::OnUpdateEditLockTemplateLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_view_template_layer);
	pCmdUI->SetCheck(m_lock_template_layer);
}

void CXCCEditorView::OnUpdateEditLockOverlayLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_view_overlay_layer);
	pCmdUI->SetCheck(m_lock_overlay_layer);
}

void CXCCEditorView::OnUpdateEditLockSmudgeLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_view_smudge_layer);
	pCmdUI->SetCheck(m_lock_smudge_layer);
}

void CXCCEditorView::OnUpdateEditLockTerrainLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_view_terrain_layer);
	pCmdUI->SetCheck(m_lock_terrain_layer);
}

void CXCCEditorView::OnUpdateEditLockInfantryLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_view_infantry_layer);
	pCmdUI->SetCheck(m_lock_infantry_layer);
}

void CXCCEditorView::OnUpdateEditLockStructureLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_view_structure_layer);
	pCmdUI->SetCheck(m_lock_structure_layer);
}

void CXCCEditorView::OnUpdateEditLockUnitLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_view_unit_layer);
	pCmdUI->SetCheck(m_lock_unit_layer);
}

void CXCCEditorView::OnViewTemplateLayer() 
{
	m_view_template_layer = !m_view_template_layer;
	if (!m_view_template_layer)
		m_lock_template_layer = true;
	Invalidate(true);	
}

void CXCCEditorView::OnViewOverlayLayer() 
{
	m_view_overlay_layer = !m_view_overlay_layer;
	if (!m_view_overlay_layer)
		m_lock_overlay_layer = true;
	Invalidate(true);
}

void CXCCEditorView::OnViewSmudgeLayer() 
{
	m_view_smudge_layer = !m_view_smudge_layer;
	if (!m_view_smudge_layer)
		m_lock_smudge_layer = true;
	Invalidate(true);
}

void CXCCEditorView::OnViewTerrainLayer() 
{
	m_view_terrain_layer = !m_view_terrain_layer;
	if (!m_view_terrain_layer)
		m_lock_terrain_layer = true;
	Invalidate(true);	
}

void CXCCEditorView::OnViewInfantryLayer() 
{
	m_view_infantry_layer = !m_view_infantry_layer;
	if (!m_view_infantry_layer)
		m_lock_infantry_layer = true;
	Invalidate(true);	
}

void CXCCEditorView::OnViewStructureLayer() 
{
	m_view_structure_layer = !m_view_structure_layer;
	if (!m_view_structure_layer)
		m_lock_structure_layer = true;
	Invalidate(true);	
}

void CXCCEditorView::OnViewUnitLayer() 
{
	m_view_unit_layer = !m_view_unit_layer;
	if (!m_view_unit_layer)
		m_lock_unit_layer = true;
	Invalidate(true);	
}

void CXCCEditorView::OnViewCelltriggerLayer() 
{
	m_view_celltrigger_layer = !m_view_celltrigger_layer;
	Invalidate(true);	
}

void CXCCEditorView::OnViewWaypointLayer() 
{
	m_view_waypoint_layer = !m_view_waypoint_layer;
	Invalidate(true);	
}

void CXCCEditorView::OnUpdateViewTemplateLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_view_template_layer);
}

void CXCCEditorView::OnUpdateViewOverlayLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_view_overlay_layer);
}

void CXCCEditorView::OnUpdateViewSmudgeLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_view_smudge_layer);
}

void CXCCEditorView::OnUpdateViewTerrainLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_view_terrain_layer);
}

void CXCCEditorView::OnUpdateViewInfantryLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_view_infantry_layer);
}

void CXCCEditorView::OnUpdateViewStructureLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_view_structure_layer);
}

void CXCCEditorView::OnUpdateViewUnitLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_view_unit_layer);
}

void CXCCEditorView::OnUpdateViewCelltriggerLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_view_celltrigger_layer);
}

void CXCCEditorView::OnUpdateViewWaypointLayer(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_view_waypoint_layer);
}

void CXCCEditorView::OnEditTeamtypes() 
{
	Cedit_teamtypes_dlg dlg(level());
	dlg.DoModal();
	OnUpdate();
}

void CXCCEditorView::OnEditTriggers() 
{
	Cedit_triggers_dlg dlg(level());
	dlg.DoModal();
	OnUpdate();
}

void CXCCEditorView::OnEditWaypoints() 
{
	Cedit_waypoints_dlg dlg(level());
	dlg.DoModal();
	OnUpdate();
}

void CXCCEditorView::OnPopupSetCelltrigger() 
{
	Cedit_triggers_dlg dlg(level(), true);
	if (dlg.DoModal() == IDOK)
	{
		level().celltrigger_data[m_context_pos.get_cc()] = dlg.get_selected_name();
		OnUpdate();
	}
}

void CXCCEditorView::OnPopupSetWaypoint() 
{
	Cedit_waypoints_dlg dlg(level(), true);
	if (dlg.DoModal() == IDOK)
	{
		level().waypoint_data[dlg.get_selected_i()] = m_context_pos.get_cc();
		OnUpdate();
	}
}

void CXCCEditorView::OnEditBasic() 
{
	Cedit_basic_dlg dlg(level());
	if (dlg.DoModal() == IDOK)
		OnUpdate();
}

void CXCCEditorView::OnEditMap() 
{
	t_theater_id current_theater = level().map_data.theater;
	Cedit_map_dlg dlg(level());
	if (dlg.DoModal() == IDOK)
	{
		if (current_theater != level().map_data.theater)
			main_frame()->InitialUpdateFrame(GetDocument(), true);
		OnUpdate();
	}
}

void CXCCEditorView::OnEditBriefing() 
{
	Cedit_briefing_dlg dlg(level());
	if (dlg.DoModal() == IDOK)
		OnUpdate();
}

void CXCCEditorView::OnEditGoodguy() 
{
	Cedit_side_dlg dlg(level().side_data[s_goodguy]);
	if (dlg.DoModal() == IDOK)
		OnUpdate();
}

void CXCCEditorView::OnEditBadguy() 
{
	Cedit_side_dlg dlg(level().side_data[s_badguy]);
	if (dlg.DoModal() == IDOK)
		OnUpdate();
}

void CXCCEditorView::OnEditNeutral() 
{
	Cedit_side_dlg dlg(level().side_data[s_neutral]);
	if (dlg.DoModal() == IDOK)
		OnUpdate();
}

void CXCCEditorView::OnEditSpecial() 
{
	Cedit_side_dlg dlg(level().side_data[s_special]);
	if (dlg.DoModal() == IDOK)
		OnUpdate();
}

void CXCCEditorView::OnEditMulti1() 
{
	Cedit_side_dlg dlg(level().side_data[s_multi1]);
	if (dlg.DoModal() == IDOK)
		OnUpdate();
}

void CXCCEditorView::OnEditMulti2() 
{
	Cedit_side_dlg dlg(level().side_data[s_multi2]);
	if (dlg.DoModal() == IDOK)
		OnUpdate();
}

void CXCCEditorView::OnEditMulti3() 
{
	Cedit_side_dlg dlg(level().side_data[s_multi3]);
	if (dlg.DoModal() == IDOK)
		OnUpdate();
}

void CXCCEditorView::OnEditMulti4() 
{
	Cedit_side_dlg dlg(level().side_data[s_multi4]);
	if (dlg.DoModal() == IDOK)
		OnUpdate();
}

void CXCCEditorView::OnEditMulti5() 
{
	Cedit_side_dlg dlg(level().side_data[s_multi5]);
	if (dlg.DoModal() == IDOK)
		OnUpdate();
}

void CXCCEditorView::OnEditMulti6() 
{
	Cedit_side_dlg dlg(level().side_data[s_multi6]);
	if (dlg.DoModal() == IDOK)
		OnUpdate();
}

void CXCCEditorView::update_current_object(const Cxcc_cell& cell)
{
	dword min_distance = -1;
	if (m_MemDCValid && in_level(cell))
	for (int b = -1; b < 2; b++)
	{
		for (int a = -1; a < 2; a++)
		{
			Cxcc_cell area_cell = cell + Cxcc_cell(a << 10, b << 10);
			if (!in_level(area_cell.x >> 8, area_cell.y >> 8))
				continue;
			const xcc_cell_manager::t_cell_info* ci = xcc_cell_manager::get_cell_info(area_cell);
			while (ci)
			{
				for (int i = 0; i < 16; i++)
				{
					dword v = ci->entry[i];
					if (!v)
						continue;
					const t_object_id type = static_cast<t_object_id>(v >> 24);
					const int index = v & 0xffffff;
					dword distance = -1;
					switch (type)
					{
					case oi_overlay:
						if (m_view_overlay_layer)
						{
							Cxcc_cell obj_cell;
							obj_cell.set_xcc(index);
							distance = Cxcc_cell::distance(cell, obj_cell);
						}
						break;
					case oi_terrain:
						if (m_view_terrain_layer)
						{
							Cxcc_cell obj_cell;
							obj_cell.set_xcc(index);
							const dword v = level().terrain_data[obj_cell.get_xcc()];
							int cx, cy, t;
							Cxcc_overlays::get_terrain_image(v, t, t, cx, cy);
							bool done = false;
							int w = 0;
							for (int j = 0; j < (cy + 23) / 24; j++)
							{
								for (int i = 0; i < (cx + 23) / 24; i++)
								{
									if (!Cxcc_overlays::terrain_blocked(v | w++))
										continue;
									distance = Cxcc_cell::distance(cell, obj_cell + Cxcc_cell(i << 8, j << 8));
									if (distance < min_distance)
									{
										min_distance = distance;
										done = true;
									}
								}
							}
							if (done)
							{
								if (min_distance < 0x100)
									min_distance = 0x80;
								distance = min_distance;
								min_distance++;
							}
						}
						break;
					case oi_infantry:
						if (m_view_infantry_layer)
							distance = Cxcc_cell::distance(cell, level().infantry_data[index].cell);
						break;
					case oi_structure:
						if (m_view_structure_layer)
						{
							const xcc_structures::t_structure_data_entry& d = *level().structure_data[index].t;
							bool done = false;
							int w = 0;
							for (int j = 0; j < d.cy; j++)
							{
								for (int i = 0; i < d.cx; i++)
								{
									if (~d.blocked >> w++ & 1)
										continue;
									distance = Cxcc_cell::distance(cell, Cxcc_cell(level().structure_data[index].cell) + Cxcc_cell(i << 8, j << 8));
									if (distance < min_distance)
									{
										min_distance = distance;
										done = true;
									}
								}
							}
							if (done)
							{
								if (min_distance < 0x100)
									min_distance = 0x80;
								distance = min_distance;
								min_distance++;
							}
						}
						break;
					case oi_unit:
						if (m_view_unit_layer)
							distance = Cxcc_cell::distance(cell, level().unit_data[index].cell);
						break;
					}
					if (distance < min_distance)
					{
						min_distance = distance;
						m_current_object = index;
						m_current_object_type = type;
					}
				}
				ci = xcc_cell_manager::get_next(ci);
			}
		}
	}
	if (min_distance > 0x80)
		m_current_object_type = static_cast<t_object_id>(-1);
}

void CXCCEditorView::OnPopupDelete() 
{
	switch (m_current_object_type)
	{
	case oi_overlay:
		{
			Cxcc_cell obj_cell;
			obj_cell.set_xcc(m_current_object);
			level().overlay_data.erase(obj_cell.get_xcc());
			level().process();
		}
		break;
	case oi_terrain:
		{
			Cxcc_cell obj_cell;
			obj_cell.set_xcc(m_current_object);
			level().terrain_data.erase(obj_cell.get_xcc());
		}
		break;
	case oi_infantry:
		level().infantry_data.erase(level().infantry_data.begin() + m_current_object);
		break;
	case oi_structure:
		level().structure_data.erase(level().structure_data.begin() + m_current_object);
		break;
	case oi_unit:
		level().unit_data.erase(level().unit_data.begin() + m_current_object);
		break;
	}
	OnUpdate();
}

void CXCCEditorView::OnUpdatePopupDelete(CCmdUI* pCmdUI) 
{
	bool enable = false;
	switch (m_current_object_type)
	{
	case oi_overlay:
		if (!m_lock_overlay_layer)
			enable = true;
		break;
	case oi_terrain:
		if (!m_lock_terrain_layer)
			enable = true;
		break;
	case oi_infantry:
		if (!m_lock_infantry_layer)
			enable = true;
		break;
	case oi_structure:
		if (!m_lock_structure_layer)
			enable = true;
		break;
	case oi_unit:
		if (!m_lock_unit_layer)
			enable = true;
		break;
	}
	pCmdUI->Enable(enable);
}

void CXCCEditorView::OnPopupProperties() 
{
	switch (m_current_object_type)
	{
	case oi_infantry:
		{
			Cedit_infantry_properties_dlg dlg(level());
			dlg.load(level().infantry_data[m_current_object]);
			if (dlg.DoModal() == IDOK)
			{
				dlg.save(level().infantry_data[m_current_object]);
				OnUpdate();
			}
		}
		break;
	case oi_structure:
		{
			Cedit_structure_properties_dlg dlg(level());
			dlg.load(level().structure_data[m_current_object]);
			if (dlg.DoModal() == IDOK)
			{
				dlg.save(level().structure_data[m_current_object]);
				OnUpdate();
			}
		}
		break;
	case oi_unit:
		{
			Cedit_unit_properties_dlg dlg(level());
			dlg.load(level().unit_data[m_current_object]);
			if (dlg.DoModal() == IDOK)
			{
				dlg.save(level().unit_data[m_current_object]);
				OnUpdate();
			}
		}
		break;
	}
}

void CXCCEditorView::OnUpdatePopupProperties(CCmdUI* pCmdUI) 
{
	bool enable = false;
	switch (m_current_object_type)
	{
	case oi_infantry:
	case oi_structure:
	case oi_unit:
		enable = true;
	}
	pCmdUI->Enable(enable);
}

const byte* CXCCEditorView::get_rp(t_object_id type, t_side_id side)
{
	switch (type)
	{
	case oi_infantry:
		if (side == s_badguy)
			return xcc_draw::multi4_rp;
		// fall through
	case oi_structure:
		// fall through
	case oi_unit:
		return xcc_draw::side_rp[side];
	}
	return 0;
}


Cxcc_cell CXCCEditorView::get_cell_from_point(const CPoint& point)
{
	Cxcc_cell r;
	r.pixel(GetDeviceScrollPosition() + point);
	return r - Cxcc_cell(8 << 8, 8 << 8);
}

CPoint CXCCEditorView::get_point_from_cell(const Cxcc_cell& cell)
{
	return (cell + Cxcc_cell(8 << 8, 8 << 8)).pixel() - GetDeviceScrollPosition();
}

void CXCCEditorView::OnPopupClearLayer(UINT nID) 
{
	const CRect sel = get_selection();
	switch (nID)
	{
	case ID_POPUP_CLEAR_TEMPLATE_LAYER:
	case ID_POPUP_CLEAR_OVERLAY_LAYER:
	case ID_POPUP_CLEAR_SMUDGE_LAYER:
	case ID_POPUP_CLEAR_INFANTRY_LAYER:
	case ID_POPUP_CLEAR_UNIT_LAYER:
	case ID_POPUP_CLEAR_CELLTRIGGER_LAYER:
	case ID_POPUP_CLEAR_WAYPOINT_LAYER:
		for (int y = sel.TopLeft().y; y < sel.BottomRight().y; y++)
		{
			for (int x = sel.TopLeft().x; x < sel.BottomRight().x; x++)
			{
				Cxcc_cell cell(x << 8 | 0x80, y << 8 | 0x80);
				switch (nID)
				{
				case ID_POPUP_CLEAR_TEMPLATE_LAYER:
					level().bin_data[Cxcc_cell(x << 8, y << 8).get_cc()] = 0;
					break;
				case ID_POPUP_CLEAR_OVERLAY_LAYER:
					level().overlay_data.erase(Cxcc_cell(x << 8, y << 8).get_xcc());
					break;
				case ID_POPUP_CLEAR_SMUDGE_LAYER:
					break;
				case ID_POPUP_CLEAR_INFANTRY_LAYER:
					for (t_infantry_data::iterator i = level().infantry_data.begin(); i != level().infantry_data.end(); )
					{
						if (i->cell.center() == cell)
							i = level().infantry_data.erase(i);
						else
							i++;
					}
					break;
				case ID_POPUP_CLEAR_UNIT_LAYER:
					for (t_unit_data::iterator i = level().unit_data.begin(); i != level().unit_data.end(); )
					{
						if (i->cell.center() == cell)
							i = level().unit_data.erase(i);
						else
							i++;
					}
					break;
				case ID_POPUP_CLEAR_CELLTRIGGER_LAYER:
					level().celltrigger_data.erase(Cxcc_cell(x << 8, y << 8).get_cc());
					break;
				case ID_POPUP_CLEAR_WAYPOINT_LAYER:
					for (int i = 0; i < 100; i++)
					{
						if (level().waypoint_data[i] == cell.get_cc())
							level().waypoint_data[i] = -1;
					}						
					break;				
				}
			}
		}
		break;
	case ID_POPUP_CLEAR_TERRAIN_LAYER:
		for (t_terrain_data::iterator i = level().terrain_data.begin(); i != level().terrain_data.end(); )
		{
			Cxcc_cell cell;
			cell.set_xcc(i->first);
			const CPoint ul(cell.x >> 8, cell.y >> 8);
			const int t = i->second;
			int cx, cy, ox, oy;
			Cxcc_overlays::get_terrain_image(t, ox, oy, cx, cy);
			cx = (cx + 23) / 24;
			cy = (cy + 23) / 24;
			int j = 0;
			int outside = false;
			for (int y = 0; y < cy; y++)
			{
				for (int x = 0; x < cx; x++)
				{
					if (Cxcc_overlays::terrain_blocked(t & 0xff00 | j) && !sel.PtInRect(ul + CPoint(x, y)))
					{
						outside = true;
						break;						
					}
					j++;
				}
				if (outside)
					break;
			}
			if (outside)
				i++;
			else
				i = level().terrain_data.erase(i);
		}
		break;
	case ID_POPUP_CLEAR_STRUCTURE_LAYER:
		for (t_structure_data::iterator i = level().structure_data.begin(); i != level().structure_data.end(); )
		{
			const Cxcc_cell cell = i->cell;
			const CPoint ul(cell.x >> 8, cell.y >> 8);
			const xcc_structures::t_structure_data_entry d = *i->t;
			int j = 0;
			int outside = false;
			for (int y = 0; y < d.cy; y++)
			{
				for (int x = 0; x < d.cx; x++)
				{
					if (d.blocked >> j & 1 && !sel.PtInRect(ul + CPoint(x, y)))
					{
						outside = true;
						break;						
					}
					j++;
				}
				if (outside)
					break;
			}
			if (outside)
				i++;
			else
				i = level().structure_data.erase(i);
		}
		break;
	}
	if (nID == ID_POPUP_CLEAR_TEMPLATE_LAYER || nID == ID_POPUP_CLEAR_OVERLAY_LAYER)
		level().process();
	OnUpdate();
}

void CXCCEditorView::OnUpdatePopupClearLayer(CCmdUI* pCmdUI) 
{
	bool enable = false;
	switch (pCmdUI->m_nID)
	{
	case ID_POPUP_CLEAR_TEMPLATE_LAYER:
		enable = !m_lock_template_layer;
		break;
	case ID_POPUP_CLEAR_OVERLAY_LAYER:
		enable = !m_lock_overlay_layer;
		break;
	case ID_POPUP_CLEAR_SMUDGE_LAYER:
		enable = !m_lock_smudge_layer;
		break;
	case ID_POPUP_CLEAR_TERRAIN_LAYER:
		enable = !m_lock_terrain_layer;
		break;
	case ID_POPUP_CLEAR_INFANTRY_LAYER:
		enable = !m_lock_infantry_layer;
		break;
	case ID_POPUP_CLEAR_STRUCTURE_LAYER:
		enable = !m_lock_structure_layer;
		break;
	case ID_POPUP_CLEAR_UNIT_LAYER:
		enable = !m_lock_unit_layer;
		break;
	case ID_POPUP_CLEAR_CELLTRIGGER_LAYER:
		// fall through
	case ID_POPUP_CLEAR_WAYPOINT_LAYER:
		enable = true;
		break;
	}
	pCmdUI->Enable(enable);
}

void CXCCEditorView::OnPopupFillWithCelltriggers() 
{
	Cedit_triggers_dlg dlg(level(), true);
	if (dlg.DoModal() == IDOK)
	{
		const CRect sel = get_selection();
		for (int y = sel.TopLeft().y; y < sel.BottomRight().y; y++)
		{
			for (int x = sel.TopLeft().x; x < sel.BottomRight().x; x++)
			{
				const int cell = Cxcc_cell(x << 8, y << 8).get_cc();
				level().celltrigger_data[cell] = dlg.get_selected_name();
			}
		}
		OnUpdate();
	}
}

void CXCCEditorView::OnPopupFillWithTiberium() 
{
	t_overlay_data& data = level().overlay_data;
	const CRect sel = get_selection();
	for (int y = sel.TopLeft().y; y < sel.BottomRight().y; y++)
	{
		for (int x = sel.TopLeft().x; x < sel.BottomRight().x; x++)
		{
			const int cell = Cxcc_cell(x << 8, y << 8).get_xcc();
			if (data.find(cell) == data.end())
				data[cell] = rand() % 12 << 8 | 11;
		}
	}
	OnUpdate();
}

void CXCCEditorView::OnPopupFillWithWater() 
{
	const CRect sel = get_selection();
	for (int y = sel.TopLeft().y; y < sel.BottomRight().y; y++)
	{
		for (int x = sel.TopLeft().x; x < sel.BottomRight().x; x++)
		{
			unsigned short& v = level().bin_data[Cxcc_cell(x << 8, y << 8).get_cc()];
			if (v >> 8 == 0)
				v = 2 << 8;
		}
	}
	level().process();
	OnUpdate();
}

void CXCCEditorView::OnPopupFillWithSandbagWall() 
{
	sel_fill_with_wall(o_sbag);
}

void CXCCEditorView::OnPopupFillWithChainLinkFence() 
{
	sel_fill_with_wall(o_cycl);
}

void CXCCEditorView::OnPopupFillWithConcreteWall() 
{
	sel_fill_with_wall(o_brik);
}

void CXCCEditorView::sel_fill_with_wall(dword t) 
{
	t_overlay_data& data = level().overlay_data;
	const CRect sel = get_selection();
	t <<= 8;
	if (sel.Width() < 5 || sel.Height() < 5)
	{
		for (int y = sel.TopLeft().y; y < sel.BottomRight().y; y++)
		{
			for (int x = sel.TopLeft().x; x < sel.BottomRight().x; x++)
			{
				const int cell = Cxcc_cell(x << 8, y << 8).get_xcc();
				if (data.find(cell) == data.end())
					data[cell] = t;
			}
		}
	}
	else
	{
		const CPoint& tl = sel.TopLeft();
		const CPoint& br = sel.BottomRight();
		for (int x = sel.TopLeft().x; x < sel.BottomRight().x; x++)
		{
			data[Cxcc_cell(x << 8, sel.TopLeft().y << 8).get_xcc()] = t;
			data[Cxcc_cell(x << 8, sel.BottomRight().y - 1 << 8).get_xcc()] = t;
		}
		for (int y = sel.TopLeft().y; y < sel.BottomRight().y; y++)
		{
			data[Cxcc_cell(sel.TopLeft().x << 8, y << 8).get_xcc()] = t;
			data[Cxcc_cell(sel.BottomRight().x - 1 << 8, y << 8).get_xcc()] = t;
		}
		data[Cxcc_cell(tl.x + 1 << 8, tl.y + 1 << 8).get_xcc()] = t;
		data[Cxcc_cell(br.x - 2 << 8, tl.y + 1 << 8).get_xcc()] = t;
		data[Cxcc_cell(tl.x + 1 << 8, br.y - 2 << 8).get_xcc()] = t;
		data[Cxcc_cell(br.x - 2 << 8, br.y - 2 << 8).get_xcc()] = t;
	}
	level().process();
	OnUpdate();
}

void CXCCEditorView::OnToolsUpgradeTiberium() 
{
	t_overlay_data& data = level().overlay_data;
	for (auto& i : data)
	{
		t_overlay_id v = static_cast<t_overlay_id>(i.second >> 8);
		if (is_tiberium(v))
			i.second = v << 8 | 11;
	}
	OnUpdate();
}

void CXCCEditorView::OnUpdatePopupFillWithWater(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_lock_template_layer);
}

void CXCCEditorView::OnUpdatePopupFillWithTiberium(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_lock_overlay_layer);
}

void CXCCEditorView::get_selection(Cxcc_cell& a, Cxcc_cell& b) const
{
	CRect rect(m_sel_bp.x, m_sel_bp.y, m_sel_ep.x, m_sel_ep.y);
	rect.NormalizeRect();
	a.x = rect.TopLeft().x;
	a.y = rect.TopLeft().y;
	b.x = rect.BottomRight().x;
	b.y = rect.BottomRight().y;
}

CRect CXCCEditorView::get_selection() const
{
	Cxcc_cell a, b;
	get_selection(a, b);
	return CRect(a.x >> 8, a.y >> 8, (b.x >> 8) + 1, (b.y >> 8) + 1);
}

void CXCCEditorView::OnToolsEnergyStatus() 
{
	Cenergy_status_dlg dlg(level());
	dlg.DoModal();
}

void CXCCEditorView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	switch (m_current_object_type)
	{
	case oi_infantry:
	case oi_structure:
	case oi_unit:
		OnPopupProperties();
		break;
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}
