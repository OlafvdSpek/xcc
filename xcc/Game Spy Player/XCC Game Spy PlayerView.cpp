#include "stdafx.h"

#include "XCC Game Spy PlayerDoc.h"
#include "XCC Game Spy PlayerView.h"

#include <strstream>
#include "wol/ra2_names.h"
#include "map_ts_ini_reader.h"
#include "mix_file.h"
#include "resource.h"
#include "string_conversion.h"
#include "virtual_image.h"
#include "xcc_dirs.h"

const bool live = false;
HANDLE h;

IMPLEMENT_DYNCREATE(CXCCGameSpyPlayerView, CView)

BEGIN_MESSAGE_MAP(CXCCGameSpyPlayerView, CView)
	//{{AFX_MSG_MAP(CXCCGameSpyPlayerView)
	ON_WM_CHAR()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_NON_HUMAN_OBJECTS, OnViewNonHumanObjects)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NON_HUMAN_OBJECTS, OnUpdateViewNonHumanObjects)
	ON_COMMAND(ID_VIEW_OBJECT_SUMMARY, OnViewObjectSummary)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OBJECT_SUMMARY, OnUpdateViewObjectSummary)
	ON_COMMAND(ID_VIEW_TERRAIN, OnViewTerrain)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TERRAIN, OnUpdateViewTerrain)
	ON_COMMAND(ID_VIEW_NAMES, OnViewNames)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NAMES, OnUpdateViewNames)
	ON_COMMAND(ID_VIEW_HISTORY, OnViewHistory)
	ON_UPDATE_COMMAND_UI(ID_VIEW_HISTORY, OnUpdateViewHistory)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CXCCGameSpyPlayerView::CXCCGameSpyPlayerView()
{
	m_replay_time = 0;
}

BOOL CXCCGameSpyPlayerView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

const char* mission_names[] =
{
	"sleep",
	"attack",
	"move",
	"qmove",
	"retreat",
	"guard",
	"sticky (never recruit)",
	"enter",
	"capture",
	"move into & get eaten",
	"harvest",
	"area guard",
	"return",
	"stop",
	"ambush",
	"hunt",
	"unload",
	"sabotage",
	"construction",
	"deconstruction",
	"repair",
	"rescue",
	"missile",
	"harmless",
	"open",
	"patrol",
	"paradrop approach drop zone",
	"paradrop overlay drop zone",
	"wait",
	"attack move",
	"spyplane approach",
	"spyplane retreat",
	"auto deploy",
};

static const t_palet_entry* get_radar_colors(Cvirtual_binary& s, int tile, int sub_tile)
{
	const byte* r = s.data();
	if (tile != -1)
	{
		while (tile--)
		{
			int count = *r++;
			r += 6 * count;
		}
	}
	int count = *r++;
	r += 6 * sub_tile;
	return reinterpret_cast<const t_palet_entry*>(r);
}

void CXCCGameSpyPlayerView::OnDraw(CDC* pDC)
{
	if (live)
	{
		m_shot_time = 0;
		m_game_state = Cgame_state(h);
		m_center_map = false;
		m_map_limits.left = m_map_limits.top = INT_MAX;
		m_map_limits.right = m_map_limits.bottom = INT_MIN;
		for (auto& i : m_game_state.objects)
		{
			const Cobject& object = i.second;
			if (!object.x || !object.y)
				continue;
			int x, y;
			transform(object.x, object.y, x, y);
			m_map_limits.left = min(m_map_limits.left, x);
			m_map_limits.right = max(m_map_limits.right, x);
			m_map_limits.top = min(m_map_limits.top, y);
			m_map_limits.bottom = max(m_map_limits.bottom, y);
		}
		m_map_limits.left -= 8 << 8;
		m_map_limits.top -= 8 << 8;
		m_map_limits.right += 8 << 8;
		m_map_limits.bottom += 8 << 8;
		m_center_map = true;
	}
	else if (!m_replay_time)
		return;
	CXCCGameSpyPlayerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect rect;
	GetClientRect(&rect);
	if (rect.Size() != m_mem_dc_size && m_mem_dc.GetSafeHdc())
	{
		DeleteObject(mh_terrain_dib);
		DeleteObject(mh_dib);
		m_terrain_dc.DeleteDC();
		m_mem_dc.DeleteDC();
	}
	if (!m_mem_dc.GetSafeHdc())
	{
		BITMAPINFO bmi;
		ZeroMemory(&bmi, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = rect.Width();
		bmi.bmiHeader.biHeight = -rect.Height();
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = bmi.bmiHeader.biWidth * -bmi.bmiHeader.biHeight * bmi.bmiHeader.biBitCount >> 3;
		
		void* p_dib;
		m_mem_dc.CreateCompatibleDC(pDC);
		mh_dib = CreateDIBSection(*pDC, &bmi, DIB_RGB_COLORS, &p_dib, 0, 0);
		m_mem_dc.SelectObject(mh_dib);
		m_mem_dc.SelectObject(GetStockObject(ANSI_FIXED_FONT));
		m_mem_dc.SetBkMode(TRANSPARENT);
		m_mem_dc.SetTextColor(RGB(0xff, 0xff, 0xff));

		void* p_terrain_dib;
		m_terrain_dc.CreateCompatibleDC(pDC);
		mh_terrain_dib = CreateDIBSection(*pDC, &bmi, DIB_RGB_COLORS, &p_terrain_dib, 0, 0);
		m_terrain_dc.SelectObject(mh_terrain_dib);

		m_mem_dc_size = rect.Size();
		m_mem_dc_valid = false;
		m_terrain_dc_valid = false;
	}
	if (!m_mem_dc_valid)
	{
		if (m_show_terrain && m_terrain_colormap.data())
		{
			if (!m_terrain_dc_valid)
			{
				FillRect(m_terrain_dc, &rect, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
				for (int y = 0; y < 512; y++)
				{
					for (int x = 0; x < 512; x++)
					{
						if (m_terrain_map[x][y].z == -1)
							continue;
						const t_iso_map_pack_entry4& e = m_terrain_map[x][y];
						const t_palet_entry* c = get_radar_colors(m_terrain_colormap, e.tile, e.sub_tile);
						CBrush brush;
						// brush.CreateSolidBrush(RGB(0, 0, (m_terrain_map[x][y].z - m_min_z) * 0x80 / (m_max_z - m_min_z)));
						brush.CreateSolidBrush(RGB(c->r / 1, c->g / 1, c->b / 1));
						int tx, ty;
						transform(x << 8 | 0x80, y << 8 | 0x80, tx, ty);
						if (0)
						{
							CBrush* old_brush = m_terrain_dc.SelectObject(&brush);
							m_terrain_dc.Ellipse(tx - 0, ty - 0, tx + 1, ty + 1);
							// m_terrain_dc.SelectObject(old_brush);
						}
						else
							m_terrain_dc.FrameRect(&CRect(tx - 0, ty - 0, tx + 1, ty + 1), &brush);
					}
				}
				m_terrain_dc_valid = true;
			}
			m_mem_dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_terrain_dc, 0, 0, SRCCOPY);
		}
		else
			FillRect(m_mem_dc, &rect, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
		
		int cx = rect.Width();
		int cy = rect.Height();
		const Cgame_state& game_state = live ? m_game_state : get_game_state(m_shot_time);
		map<int, map<int, int>> objects_counts;
		{
			if (m_show_history)
			{
				for (int y = 0; y < 512; y++)
				{
					for (int x = 0; x < 512; x++)
					{
						if (game_state.history_map[x][y] == -1)
							continue;
						CBrush brush;
						brush.CreateSolidBrush(player_color(game_state.history_map[x][y], 0x7f));
						CBrush* old_brush = m_mem_dc.SelectObject(&brush);
						int tx, ty;
						transform(x << 8 | 0x80, y << 8 | 0x80, tx, ty);
						m_mem_dc.Ellipse(tx - 3, ty - 3, tx + 4, ty + 4);
						// m_mem_dc.SelectObject(old_brush);
					}
				}
			}
			for (auto& i : game_state.objects)
			{
				const Cobject& object = i.second;
				if (!object.x || !object.y || !object.target || !game_state.objects.count(object.target))
					continue;
				const Cobject& target = *find_ptr(game_state.objects, object.target);
				CPen pen;
				pen.CreatePen(PS_SOLID, 1, player_color(find_ptr(game_state.players, object.owner)->id, 0xff));
				CPen* old_pen = m_mem_dc.SelectObject(&pen);
				int x, y;
				transform(object.x, object.y, x, y);
				m_mem_dc.MoveTo(x, y);
				transform(target.x, target.y, x, y);
				m_mem_dc.LineTo(x, y);
				m_mem_dc.SelectObject(old_pen);
			}
			for (auto& i : game_state.objects)
			{
				const Cobject& object = i.second;
				if (!object.x || !object.y)
					continue;
				auto player_i = find_ptr(game_state.players, object.owner);
				if (!player_i)
					continue;
				const Cplayer& player = *player_i;
				if (!m_view_non_human_objects && !player.human)
					continue;
				int x, y;
				transform(object.x, object.y, x, y);
				CBrush brush;
				brush.CreateSolidBrush(player_color(player.id, 0xff));
				CBrush* old_brush = m_mem_dc.SelectObject(&brush);
				if (object.building_type == -1)
					m_mem_dc.Ellipse(x - 2, y - 2, x + 3, y + 3);
				else
					m_mem_dc.Ellipse(x - 3, y - 3, x + 4, y + 4);
				if (!m_show_names)
					continue;
				Cobject_type object_type;
				object_type.strength = 0;
				{
					auto i = m_object_types.object_types.find(object.building_type == -1 ? object.vehicle_type : object.building_type);
					if (i == m_object_types.object_types.end())
						i = m_object_types.object_types.find(object.infantry_type);
					if (i != m_object_types.object_types.end())
					{
						object_type = i->second;
						if (player.human && m_view_object_summary)
							objects_counts[i->first][object.owner]++;
					}
				}
				string type_name = object_type.name;
				if (object.building_type == -1)
					type_name += object.mission >= 0 && object.mission < 33 ? string(": ") + mission_names[object.mission] : "";
				if (type_name.empty())
					continue;
				{
					CPen pen;
					pen.CreatePen(PS_SOLID, 1, player_color(find_ptr(game_state.players, object.owner)->id, 0x7f));
					CPen* old_pen = m_mem_dc.SelectObject(&pen);
					m_mem_dc.MoveTo(x + 26, y + 4);
					m_mem_dc.LineTo(x + 6, y + 4);
					m_mem_dc.SelectObject(old_pen);
				}
				if (object_type.strength)
				{
					CPen pen;
					pen.CreatePen(PS_SOLID, 1, player_color(find_ptr(game_state.players, object.owner)->id, 0xff));
					CPen* old_pen = m_mem_dc.SelectObject(&pen);
					m_mem_dc.LineTo(x + 6 + 20 * object.health / object_type.strength, y + 4);
					m_mem_dc.SelectObject(old_pen);
				}
				COLORREF old_color = m_mem_dc.SetTextColor(player_color(player.id, 0xff));
				m_mem_dc.TextOut(x + 6, y + 6, type_name.c_str());
				m_mem_dc.SetTextColor(old_color);
				// m_mem_dc.SelectObject(old_brush);
			}
		}
		m_mem_dc.TextOut(0, 0, (n(m_shot_time) + " / " + n(m_replay_time) + " " + n(game_state.frame) + " " + n(game_state.gid) + " " + n(game_state.time) + " " + get_map_name(game_state.scenario)).c_str());
		int y = 16;
		COLORREF old_color = m_mem_dc.GetTextColor();
		for (auto& i : game_state.players)
		{
			const Cplayer& player = i.second;
			if (player.color == 5)
				continue;
			m_mem_dc.SetTextColor(player_color(i.second.id, 0xff));
			string text = swsr(10, player.name);
			if (player.color != -1)
				text += swsr(11, get_color_name(player.color));
			if (player.country != -1)
				text += swsr(14, get_country_name(player.country));
			m_mem_dc.TextOut(0, y, (text + nwsl(5, player.credits) + " " + n(player.power_in) + " / " + n(player.power_out)).c_str());
			y += 16;
		}
		m_mem_dc.SetTextColor(old_color);
		if (m_view_object_summary)
		{
			for (auto& i : objects_counts)
			{
				int x = -32;
				y += 16;
				for (auto& j : game_state.players)
				{
					if (!j.second.human)
						continue;
					x += 32;
					auto k = find_ptr(i.second, j.first);
					if (!k)
						continue;
					COLORREF old_color = m_mem_dc.SetTextColor(player_color(j.second.id, 0xff));
					char b[12];
					sprintf(b, "%3d", *k);
					m_mem_dc.TextOut(x, y, b);
					m_mem_dc.SetTextColor(old_color);
				}
				m_mem_dc.TextOut(x + 32, y, find_ref(m_object_types.object_types, i.first).name.c_str());
			}
		}
		m_mem_dc_valid = true;
	}
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_mem_dc, 0, 0, SRCCOPY);
	if (live)
	{
		Sleep(100);
		m_mem_dc_valid = false;
		Invalidate();
	}
	else if (m_auto_forward)
		move_front();
}

template<class T>
static void clear_history_map(T& v)
{
	for (auto& i : v)
	{
		for (auto& j : i)
			j = -1;
	}
}

void CXCCGameSpyPlayerView::read_log()
{
	if (live)
		return;
	const Cxif_key_r& key = GetDocument()->key();
	if (key.c_keys())
	{
		m_center_map = false;
		m_map_limits.left = m_map_limits.top = INT_MAX;
		m_map_limits.right = m_map_limits.bottom = INT_MIN;
		Cgame_state game_state;
		clear_history_map(game_state.history_map);
		Cxif_key_r::t_key_map::const_iterator i = key.keys().begin();
		m_object_types.load(i++->second);
		for (; i != key.keys().end(); i++)
		{
			game_state.import_diff(i->second);
			if (!(i->first - 1 & 0xff))
				m_game_state_cache.push_back(game_state);
			for (auto& i : game_state.objects)
			{
				const Cobject& object = i.second;
				if (!object.x || !object.y)
					continue;
				int x, y;
				transform(object.x, object.y, x, y);
				m_map_limits.left = min(m_map_limits.left, x);
				m_map_limits.right = max(m_map_limits.right, x);
				m_map_limits.top = min(m_map_limits.top, y);
				m_map_limits.bottom = max(m_map_limits.bottom, y);
			}
		}
		m_map_limits.left -= 8 << 8;
		m_map_limits.top -= 8 << 8;
		m_map_limits.right += 8 << 8;
		m_map_limits.bottom += 8 << 8;
		m_center_map = true;
		read_map(game_state.scenario);
		m_shot_time = 0;
		m_replay_time = key.c_keys() - 1;
	}
}

void CXCCGameSpyPlayerView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	m_replay_time = 0;
	read_log();	
	m_auto_forward = true;
	m_show_history = false;
	m_show_names = true;
	m_show_terrain = false;
	m_view_non_human_objects = true;
	m_view_object_summary = true;

	if (live)
	{
		m_show_history = false;
		m_show_terrain = false;

		HWND hWnd = ::FindWindow(NULL, "Red Alert 2");
		if (hWnd)
		{
			DWORD pid;
			GetWindowThreadProcessId(hWnd, &pid);
			h = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
			m_object_types = Cobject_types(h);
		}
		m_replay_time = 1;
	}
}

void CXCCGameSpyPlayerView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
	case ' ':
		m_auto_forward = !m_auto_forward;
		m_mem_dc_valid = false;
		Invalidate();
		break;
	case 'r':
		if (live)
			m_object_types = Cobject_types(h);
		else
			rewind();
		break;
	case ',':
		m_auto_forward = false;
		move_back();
		break;
	case '.':
		m_auto_forward = false;
		move_front();
		break;
	case '<':
		m_auto_forward = false;
		move_back(10);
		break;
	case '>':
		m_auto_forward = false;
		move_front(10);
		break;
	case '[':
		m_auto_forward = false;
		move_back(100);
		break;
	case ']':
		m_auto_forward = false;
		move_front(100);
		break;
	}	
	CView::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CXCCGameSpyPlayerView::OnEraseBkgnd(CDC* pDC) 
{
	return m_replay_time ? true : CView::OnEraseBkgnd(pDC);
}

void CXCCGameSpyPlayerView::rewind()
{
	CRect rect;
	GetClientRect(&rect);
	FillRect(m_mem_dc, &rect, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
	shot_time(0);
}

void CXCCGameSpyPlayerView::move_back(int i)
{
	shot_time(i < m_shot_time ? m_shot_time - i : 0);
}

void CXCCGameSpyPlayerView::move_front(int i)
{
	while (i--)
	{
		int t = m_shot_time + 1;
		shot_time(t == m_replay_time ? 0 : t);
	}
}


void CXCCGameSpyPlayerView::shot_time(int v)
{
	if (m_shot_time == v)
		return;
	m_shot_time = v;
	m_mem_dc_valid = false;
	Invalidate();
}

void CXCCGameSpyPlayerView::transform(int x1, int y1, int& x2, int& y2)
{
	x2 = x1 - y1;
	y2 = x1 + y1;
	if (!m_center_map)
		return;
	x2 = (x2 - m_map_limits.left) * (m_mem_dc_size.cx - 1) / (m_map_limits.Width() - 1);
	y2 = (y2 - m_map_limits.top) * (m_mem_dc_size.cy - 1) / (m_map_limits.Height() - 1);						
}

COLORREF CXCCGameSpyPlayerView::player_color(int id, int v) const
{
	id++;
	return RGB(id & 4 ? v : 0, id & 2 ? v : 0, id & 1 ? v : 0);
}

void CXCCGameSpyPlayerView::clear_terrain_map()
{
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			m_terrain_map[x][y].tile = -1;
			m_terrain_map[x][y].sub_tile = -1;
			m_terrain_map[x][y].z = -1;
		}
	}
}

Cvirtual_binary read_file(const string& mix, const string& name)
{
	Cmix_file f;
	if (f.open(xcc_dirs::get_dir(game_ra2) + mix))
		return Cvirtual_binary();
	f.set_game(game_ra2);
	return f.get_vdata(name);
}

void CXCCGameSpyPlayerView::read_map(string name)
{
	clear_terrain_map();
	Cvirtual_binary s = read_file("multi.mix", name);
	if (!s.size() && s.load(xcc_dirs::get_dir(game_ra2) + name))
	{
		name = Cfname(name).get_ftitle();
		s = read_file("xwis.mmx", name + ".map");
		if (!s.size())
			s = read_file(name + ".mmx", name + ".map");
	}
	if (!s.size())
		return;
	Cmap_ts_ini_reader ir;
	ir.fast(true);
	ir.process(s);
	m_terrain_colormap.load(xcc_dirs::get_data_dir() + ir.get_map_data().theater + "_colormap.bin");
	strstream ini;
	Cmap_ts_encoder encoder(ini, true);
	Cmap_ts_encoder::t_header header;
	header.cx = ir.get_map_data().size_right;
	header.cy = ir.get_map_data().size_bottom;
	encoder.header(header);
	encoder.process(s);
	encoder.extract_map(*m_terrain_map);
}

const Cgame_state& CXCCGameSpyPlayerView::get_game_state(int game_state_i)
{
	if (!game_state_i || game_state_i < m_game_state_i)
		m_game_state = m_game_state_cache[m_game_state_i = game_state_i >> 8];
	if (game_state_i != m_game_state_i)
	{
		int t = m_game_state_i + 1;
		const Cxif_key_r& key = GetDocument()->key();
		Cxif_key_r::t_key_map::const_iterator i = key.keys().begin();
		while (i->first != m_game_state_i + 1)
			i++;
		while (t++ <= game_state_i)
			m_game_state.import_diff(i++->second);
		m_game_state_i = game_state_i;
	}
	return m_game_state;
}

void CXCCGameSpyPlayerView::OnViewNonHumanObjects() 
{
	m_view_non_human_objects = !m_view_non_human_objects;
	m_mem_dc_valid = false;
	Invalidate();
}

void CXCCGameSpyPlayerView::OnUpdateViewNonHumanObjects(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_view_non_human_objects);	
}

void CXCCGameSpyPlayerView::OnViewObjectSummary() 
{
	m_view_object_summary = !m_view_object_summary;
	m_mem_dc_valid = false;
	Invalidate();
}

void CXCCGameSpyPlayerView::OnUpdateViewObjectSummary(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_view_object_summary);	
}

void CXCCGameSpyPlayerView::OnViewTerrain() 
{
	m_show_terrain = !m_show_terrain;
	m_mem_dc_valid = false;
	Invalidate();
}

void CXCCGameSpyPlayerView::OnUpdateViewTerrain(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_show_terrain);
}

void CXCCGameSpyPlayerView::OnViewNames() 
{
	m_show_names = !m_show_names;
	m_mem_dc_valid = false;
	Invalidate();
}

void CXCCGameSpyPlayerView::OnUpdateViewNames(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_show_names);	
}

void CXCCGameSpyPlayerView::OnViewHistory() 
{
	m_show_history = !m_show_history;
	m_mem_dc_valid = false;
	Invalidate();
}

void CXCCGameSpyPlayerView::OnUpdateViewHistory(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_show_history);	
}
