#include "stdafx.h"

#include "MainFrm.h"
#include "XCC EditorDoc.h"
#include "XCC EditorView.h"
#include "resource.h"
#include "object_selection.h"
#include "shp_images.h"

IMPLEMENT_DYNCREATE(Cobject_selection, CScrollView)

Cobject_selection::Cobject_selection()
{
	m_mem_surface_size = CSize(8 * 24, 12 * 1024);
	SetScrollSizes(MM_TEXT, m_mem_surface_size);
}

Cobject_selection::~Cobject_selection()
{
	if (m_mem_surface_created)
		DeleteObject(mh_dib);
}

BEGIN_MESSAGE_MAP(Cobject_selection, CScrollView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(Cobject_selection)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_POPUP_INFANTRY, OnPopupInfantry)
	ON_COMMAND(ID_POPUP_OVERLAY, OnPopupOverlay)
	ON_COMMAND(ID_POPUP_STRUCTURES, OnPopupStructures)
	ON_COMMAND(ID_POPUP_TEMPLATES, OnPopupTemplates)
	ON_COMMAND(ID_POPUP_TEMPLATES_ROAD, OnPopupTemplatesRoad)
	ON_COMMAND(ID_POPUP_TEMPLATES_SHORE, OnPopupTemplatesShore)
	ON_COMMAND(ID_POPUP_TEMPLATES_RIDGE, OnPopupTemplatesRidge)
	ON_COMMAND(ID_POPUP_TEMPLATES_RIVER, OnPopupTemplatesRiver)
	ON_COMMAND(ID_POPUP_TERRAIN, OnPopupTerrain)
	ON_COMMAND(ID_POPUP_UNITS, OnPopupUnits)
	ON_UPDATE_COMMAND_UI(ID_POPUP_INFANTRY, OnUpdatePopupInfantry)
	ON_UPDATE_COMMAND_UI(ID_POPUP_OVERLAY, OnUpdatePopupOverlay)
	ON_UPDATE_COMMAND_UI(ID_POPUP_STRUCTURES, OnUpdatePopupStructures)
	ON_UPDATE_COMMAND_UI(ID_POPUP_TEMPLATES, OnUpdatePopupTemplates)
	ON_UPDATE_COMMAND_UI(ID_POPUP_TEMPLATES_RIDGE, OnUpdatePopupTemplatesRidge)
	ON_UPDATE_COMMAND_UI(ID_POPUP_TEMPLATES_RIVER, OnUpdatePopupTemplatesRiver)
	ON_UPDATE_COMMAND_UI(ID_POPUP_TERRAIN, OnUpdatePopupTerrain)
	ON_UPDATE_COMMAND_UI(ID_POPUP_UNITS, OnUpdatePopupUnits)
	ON_UPDATE_COMMAND_UI(ID_POPUP_TEMPLATES_ROAD, OnUpdatePopupTemplatesRoad)
	ON_UPDATE_COMMAND_UI(ID_POPUP_TEMPLATES_SHORE, OnUpdatePopupTemplatesShore)
	ON_COMMAND(ID_POPUP_STRUCTURES_CIVILIAN, OnPopupStructuresCivilian)
	ON_UPDATE_COMMAND_UI(ID_POPUP_STRUCTURES_CIVILIAN, OnUpdatePopupStructuresCivilian)
	ON_COMMAND(ID_POPUP_BLOCKED, OnPopupBlocked)
	ON_UPDATE_COMMAND_UI(ID_POPUP_BLOCKED, OnUpdatePopupBlocked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static CMainFrame* main_frame()
{
	return static_cast<CMainFrame*>(AfxGetMainWnd());
}

void Cobject_selection::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	m_color_table_valid = false;
	load(oi_template);
}

void Cobject_selection::OnDraw(CDC* pDC)
{
	if (!m_mem_surface_created)
	{
		// create memory surface
		m_mem_dc.CreateCompatibleDC(pDC);

		BITMAPINFO bmi;
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = m_mem_surface_size.cx;
		bmi.bmiHeader.biHeight = -m_mem_surface_size.cy;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = bmi.bmiHeader.biWidth * bmi.bmiHeader.biHeight * (bmi.bmiHeader.biBitCount >> 3);
		bmi.bmiHeader.biXPelsPerMeter = 24000;
		bmi.bmiHeader.biYPelsPerMeter = 24000;
		bmi.bmiHeader.biClrUsed = 0;
		bmi.bmiHeader.biClrImportant = 0;
		
		mh_dib = CreateDIBSection(*pDC, &bmi, DIB_RGB_COLORS, reinterpret_cast<void**>(&mp_dib), 0, 0);
		assert(mh_dib && mp_dib);
		m_mem_dc.SelectObject(mh_dib);

		SetScrollSizes(MM_TEXT, m_mem_surface_size);

		m_mem_surface_created = true;
	}

	if (!m_mem_surface_valid)
		update_mem_surface();

	pDC->BitBlt(0, 0, m_mem_surface_size.cx, m_mem_surface_size.cy, &m_mem_dc, 0, 0, SRCCOPY);
}

void Cobject_selection::draw_image(const byte* s, t_palet32bgr_entry* d, int sx, int sy, int dx, int dy, int cx, int cy)
{
	const int shadow_mask = 0x7f7f7f;
	d += dx + dy * m_mem_surface_size.cx;
	for (int yp = 0; yp < cy; yp++)
	{
		for (int xp = 0; xp < cx; xp++)
		{
			int v = *s++;
			if (v == 4)
				d->v = d->v >> 1 & shadow_mask;
			else if (v)
				*d = m_color_table[v];
			d++;
		}
		d += m_mem_surface_size.cx - cx;
	}
}

void Cobject_selection::draw_image(shp_images::t_image_data* s0, t_palet32bgr_entry* d, int sx, int sy, int dx, int dy)
{
	draw_image(s0->get(0), d, sx, sy, dx, dy, s0->cx, s0->cy);
}


void Cobject_selection::draw_filter(t_palet32bgr_entry* d, int dx, int dy, int cx, int cy, int tr, int tg, int tb, int vr, int vg, int vb) const
{
	d += dx + dy * m_mem_surface_size.cx;
	vr *= 256 - tr;
	vg *= 256 - tg;
	vb *= 256 - tb;
	for (int yp = 0; yp < cy; yp++)
	{
		for (int xp = 0; xp < cx; xp++)
		{
			t_palet32bgr_entry& v = *d++;
			v.r = (vr + v.r * tr) >> 8;
			v.g = (vg + v.g * tg) >> 8;
			v.b = (vb + v.b * tb) >> 8;
		}
		d += m_mem_surface_size.cx - cx;
	}
}

void Cobject_selection::update_mem_surface()
{
	if (!m_color_table_valid)
	{
		const t_palet& palet = Cxcc_templates::get_palet();
		for (int palet_index = 0; palet_index < 256; palet_index++)
		{
			m_color_table[palet_index].r = palet[palet_index].r;
			m_color_table[palet_index].g = palet[palet_index].g;
			m_color_table[palet_index].b = palet[palet_index].b;
		}
		m_color_table_valid = true;
	}
	m_mem_dc.BitBlt(0, 0, m_mem_surface_size.cx, m_mem_surface_size.cy, 0, 0, 0, WHITENESS);
	clear_object_pos_list();
	switch (m_loaded_selection_type)
	{
	case oi_infantry:
		load_infantry();
		break;
	case oi_overlay:
		load_overlay();
		break;
	case oi_structure:
		load_structures();
		break;
	case oi_template:
		load_templates();
		break;
	case oi_terrain:
		load_terrain();
		break;
	case oi_unit:
		load_units();
		break;
	default:
		assert(false);
	}	
	ScrollToPosition(CPoint(0, 0));
	m_mem_surface_valid = true;
}

const Cxcc_level& Cobject_selection::level() const
{
	return ((CXCCEditorDoc*)GetDocument())->level;
}

const t_theater_id Cobject_selection::theater() const
{
	return level().map_data.theater;
}

void Cobject_selection::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	Invalidate();
}

void Cobject_selection::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CScrollView::OnLButtonDown(nFlags, point);
	point += GetDeviceScrollPosition();
	int i = get_object_at(point);
	m_current_object = i;
	if (i == -1)
		return;
}

void Cobject_selection::clear_object_pos_list()
{
	for (int i = 0; i < 256; i++)
	{
		m_object_pos[i].top = -1;
		m_object_pos[i].bottom = -1;
	}
}

int Cobject_selection::get_object_at(const CPoint& pos) const
{
	for (int i = 0; i < 256; i++)
	{
		if (m_object_pos[i].PtInRect(pos))
			return i;
	}	
	return -1;
}

void Cobject_selection::OnMouseMove(UINT nFlags, CPoint point) 
{
	m_mouse_left = false;
	enable_mouse_event();
	point += GetDeviceScrollPosition();
	int i = get_object_at(point);
	string msg = "";
	if (i != -1)
	{
		switch (m_loaded_selection_type)
		{
		case oi_infantry:
			msg = xcc_infantry::infantry_data[i].long_name;
			break;
		case oi_overlay:
			msg = overlay_code[i];
			break;
		case oi_structure:
			msg = xcc_structures::structure_data[i].long_name;
			break;
		case oi_template:
			msg = template_code[i];
			break;
		case oi_terrain:
			msg = terrain_code[i];
			break;
		case oi_unit:
			msg = xcc_units::unit_data[i].long_name;
			break;
		}
	}
	main_frame()->m_object_name = msg;
	CScrollView::OnMouseMove(nFlags, point);
}

void Cobject_selection::load_infantry()
{
	int y = 0;
	CSize total(0, 0);
	for (int i = 0; i < 256; i++)
	{
		const xcc_infantry::t_infantry_data_entry& id = xcc_infantry::infantry_data[i];
		if (~id.flags & id_flags_in_use)
			continue;
		m_object_pos[i].top = y;
		m_object_pos[i].left = 0;
		m_object_pos[i].right = id.cx;
		if (id.cx > total.cx)
			total.cx = id.cx;
		draw_image(id.images, mp_dib, 0, 0, 0, y);
		y += id.cy;
		m_object_pos[i].bottom = y;
		total.cy = y;
		y += 24;
	}
	SetScrollSizes(MM_TEXT, total);
}

void Cobject_selection::load_overlay()
{
	int y = 0;
	CSize total(24, 0);
	for (int i = 0; i < c_overlay_id; i++)
	{
		int cx, cy, t;
		const byte* image_data = Cxcc_overlays::get_overlay_image(is_tiberium(static_cast<t_overlay_id>(i)) ? o_ti1 | i - o_ti1: i << 8, t, t, cx, cy);
		if (!image_data)
			continue;
		m_object_pos[i].top = y;
		m_object_pos[i].left = 0;
		m_object_pos[i].right = cx;
		draw_image(image_data, mp_dib, 0, 0, 0, y, cx, cy);
		y += cy;
		m_object_pos[i].bottom = y;
		total.cy = y;
		y += 24;
	}
	SetScrollSizes(MM_TEXT, total);
}

void Cobject_selection::load_structures()
{
	int y = 0;
	CSize total(0, 0);
	for (int i = 0; i < 256; i++)
	{
		const xcc_structures::t_structure_data_entry& sd = xcc_structures::structure_data[i];
		switch (m_loaded_selection_subtype)
		{
		case 1:
			if (~sd.flags & sd_flags_civilian)
				continue;
			break;
		default:
			if (sd.flags & (sd_flags_civilian | sd_flags_wall))
				continue;
		}
		if (sd.flags & sd_flags_in_use && (!(sd.flags & sd_flags_theater_specific) || sd.flags >> level().map_data.theater & sd_flags_desert))
		{
			m_object_pos[i].top = y;
			m_object_pos[i].left = 0;
			m_object_pos[i].right = 24 * sd.cx;
			if (24 * sd.cx > total.cx)
				total.cx = 24 * sd.cx;
			draw_image(sd.images, mp_dib, 0, 0, 0, y);
			if (sd.flags & sd_flags_images2)
				draw_image(sd.images2, mp_dib, 0, 0, 0, y);
			int j = 0;
			for (int yp = 0; yp < sd.cy; yp++)
			{
				for (int xp = 0; xp < sd.cx; xp++)
				{
					bool blocked = xcc_structures::structure_data[i].blocked >> j & 1;
					bool ground = xcc_structures::structure_data[i].ground >> j++ & 1;
					if (0) // blocked || ground)
						draw_filter(mp_dib, 24 * xp, y + 24 * yp, 24, 24, 0x80, 0x80, 0x80, blocked ? 0xff : 0x00, ground ? 0x80 : 0x00, 0x00);
				}
			}
			y += 24 * sd.cy;
			m_object_pos[i].bottom = y;
			total.cy = y;
			y += 24;
		}
	}
	SetScrollSizes(MM_TEXT, total);
}

void Cobject_selection::load_templates()
{
	int y = 0;
	CSize total(0, 0);
	for (int i = 0; i < 0xd8; i++)
	{
		const t_template_data_entry& td = Cxcc_templates::get_template_data(i);
		switch (m_loaded_selection_subtype)
		{
		case td_flags_ridge:
			if (~td.flags & td_flags_ridge)
				continue;
			break;
		case td_flags_river:
			if (~td.flags & td_flags_river)
				continue;
			break;
		case td_flags_shore:
			if (~td.flags & td_flags_shore)
				continue;
			break;
		case td_flags_road:
			if (~td.flags & td_flags_road)
				continue;
			break;
		default:
			if (td.flags & td_flags_type_specific)
				continue;
		}
		if (!td.images)
			continue;
		m_object_pos[i].top = y;
		m_object_pos[i].left = 0;
		m_object_pos[i].right = 24 * td.cx;
		if (24 * td.cx > total.cx)
			total.cx = 24 * td.cx;
		int j = 0;
		for (int b = 0; b < td.cy; b++)
		{
			for (int a = 0; a < td.cx; a++)
			{
				int v = Cxcc_templates::convert_bin_data(j++ << 8 | i);
				if ((v & 0xff) != 0xff)
				{
					draw_image(Cxcc_templates::get_image(v), mp_dib, 0, 0, 24 * a, y, 24, 24);
				}
			}
			y += 24;
		}
		m_object_pos[i].bottom = y;
		total.cy = y;
		y += 24;
	}
	SetScrollSizes(MM_TEXT, total);
}

void Cobject_selection::load_terrain()
{
	int y = 0;
	CSize total(0, 0);
	for (int i = 0; i < c_terrain_id; i++)
	{
		int cx, cy, t;
		const byte* image_data = Cxcc_overlays::get_terrain_image(i << 8, t, t, cx, cy);
		if (!image_data)
			continue;
		m_object_pos[i].top = y;
		m_object_pos[i].left = 0;
		m_object_pos[i].right = cx;
		if (cx > total.cx)
			total.cx = cx;
		draw_image(image_data, mp_dib, 0, 0, 0, y, cx, cy);
		int j = 0;
		for (int yp = 0; yp < (cy + 23) / 24; yp++)
		{
			for (int xp = 0; xp < (cx + 23) / 24; xp++)
			{
				if (0) // Cxcc_overlays::terrain_blocked(i << 8 | j++))
					draw_filter(mp_dib, 24 * xp, y + 24 * yp, 24, 24, 0x80, 0x80, 0x80, 0xff, 0x00, 0x00);
			}
		}
		y += cy;
		m_object_pos[i].bottom = y;
		total.cy = y;
		y += 24;
	}
	SetScrollSizes(MM_TEXT, total);
}

void Cobject_selection::load_units()
{
	int y = 0;
	CSize total(0, 0);
	for (int i = 0; i < 256; i++)
	{
		const xcc_units::t_unit_data_entry& ud = xcc_units::unit_data[i];
		if (~ud.flags & ud_flags_in_use)
			continue;
		m_object_pos[i].top = y;
		m_object_pos[i].left = 0;
		m_object_pos[i].right = ud.cx;
		if (ud.cx > total.cx)
			total.cx = ud.cx;
		draw_image(ud.images, mp_dib, 0, 0, 0, y);
		if (ud.flags & ud_flags_top)
		{
			int cx, cy;
			auto image_data = ud.images->get(32, cx, cy);
			draw_image(image_data, mp_dib, 0, 0, 0, y, cx, cy);
		}
		y += ud.cy;
		m_object_pos[i].bottom = y;
		total.cy = y;
		y += 24;
	}
	SetScrollSizes(MM_TEXT, total);
}

void Cobject_selection::load(t_object_id selection_type, int selection_subtype)
{
	if (selection_type == m_loaded_selection_type && selection_subtype == m_loaded_selection_subtype)
		return;
	m_current_object = -1;
	m_loaded_selection_type = selection_type;
	m_loaded_selection_subtype = selection_subtype;
	Invalidate();
}

void Cobject_selection::Invalidate()
{
	m_mem_surface_valid = false;
	CScrollView::Invalidate(false);
}

void Cobject_selection::OnContextMenu(CWnd*, CPoint point)
{
	if (point.x == -1)
		return;
	CPoint context_pos = GetDeviceScrollPosition() + point;
	ScreenToClient(&context_pos);
	int i = get_object_at(context_pos);
	m_current_object = i;
	if (i != -1)
	{
		context_pos -= m_object_pos[i].TopLeft();
		m_context_subpos = context_pos.x / 24 + (m_object_pos[i].Width() + 23) / 24 * (context_pos.y / 24);
	}
	CMenu menu;
	VERIFY(menu.LoadMenu(CG_IDR_POPUP_CTEMPLATE_SELECTION));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup);
	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pWndPopupOwner);
}

void Cobject_selection::OnPopupInfantry() 
{
	load(oi_infantry);
}

void Cobject_selection::OnPopupStructures() 
{
	load(oi_structure);
}

void Cobject_selection::OnPopupStructuresCivilian() 
{
	load(oi_structure, 1);
}

void Cobject_selection::OnPopupUnits() 
{
	load(oi_unit);
}

void Cobject_selection::OnPopupTemplates() 
{
	load(oi_template);
}

void Cobject_selection::OnPopupTemplatesRidge() 
{
	load(oi_template, td_flags_ridge);
}

void Cobject_selection::OnPopupTemplatesRiver() 
{
	load(oi_template, td_flags_river);
}

void Cobject_selection::OnPopupTemplatesRoad() 
{
	load(oi_template, td_flags_road);
}

void Cobject_selection::OnPopupTemplatesShore() 
{
	load(oi_template, td_flags_shore);
}

void Cobject_selection::OnPopupOverlay() 
{
	load(oi_overlay);
}

void Cobject_selection::OnPopupTerrain() 
{
	load(oi_terrain);
}

void Cobject_selection::OnUpdatePopupInfantry(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_loaded_selection_type == oi_infantry);
}

void Cobject_selection::OnUpdatePopupStructures(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_loaded_selection_type == oi_structure && !m_loaded_selection_subtype);
}

void Cobject_selection::OnUpdatePopupStructuresCivilian(CCmdUI* pCmdUI) 
{	
	pCmdUI->SetCheck(m_loaded_selection_type == oi_structure && m_loaded_selection_subtype == 1);
}

void Cobject_selection::OnUpdatePopupUnits(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_loaded_selection_type == oi_unit);
}

void Cobject_selection::OnUpdatePopupTemplates(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_loaded_selection_type == oi_template && !m_loaded_selection_subtype);
}

void Cobject_selection::OnUpdatePopupTemplatesRidge(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_loaded_selection_type == oi_template && m_loaded_selection_subtype == td_flags_ridge);
}

void Cobject_selection::OnUpdatePopupTemplatesRiver(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_loaded_selection_type == oi_template && m_loaded_selection_subtype == td_flags_river);
}

void Cobject_selection::OnUpdatePopupTemplatesRoad(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_loaded_selection_type == oi_template && m_loaded_selection_subtype == td_flags_road);
}

void Cobject_selection::OnUpdatePopupTemplatesShore(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_loaded_selection_type == oi_template && m_loaded_selection_subtype == td_flags_shore);
}

void Cobject_selection::OnUpdatePopupOverlay(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_loaded_selection_type == oi_overlay);
}

void Cobject_selection::OnUpdatePopupTerrain(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_loaded_selection_type == oi_terrain);
}

int Cobject_selection::get_current_object() const
{
	return m_current_object;
}

t_object_id Cobject_selection::get_current_object_type() const
{
	return m_loaded_selection_type;
}

void Cobject_selection::reset_current_object()
{
	m_current_object = -1;
}

void Cobject_selection::enable_mouse_event()
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

LRESULT Cobject_selection::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message)
	{
	case WM_MOUSELEAVE:
		m_mouse_leave_active = false;
		m_mouse_left = true;
		main_frame()->m_object_name.erase();
		break;
	}
	return CScrollView::WindowProc(message, wParam, lParam);
}

void Cobject_selection::OnPopupBlocked() 
{
	switch (m_loaded_selection_type)
	{
	case oi_structure:
		xcc_structures::structure_data[m_current_object].ground ^= 1 << m_context_subpos;
		break;
	case oi_terrain:
		Cxcc_overlays::terrain_switch_blocked(m_current_object << 8 | m_context_subpos);
		break;
	}
}

void Cobject_selection::OnUpdatePopupBlocked(CCmdUI* pCmdUI) 
{
	bool blocked = false;
	bool changeable = false;
	if (m_current_object != -1)
	{
		switch (m_loaded_selection_type)
		{
		case oi_structure:
			{
				blocked = xcc_structures::structure_data[m_current_object].ground >> m_context_subpos & 1;
				changeable = true;
			}
			break;
		case oi_terrain:
			{
				blocked = Cxcc_overlays::terrain_blocked(m_current_object << 8 | m_context_subpos);
				changeable = true;
			}
			break;
		}
	}
	pCmdUI->SetCheck(blocked);
	pCmdUI->Enable(changeable);
}
