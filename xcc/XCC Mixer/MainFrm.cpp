// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "XCC Mixer.h"

#include "MainFrm.h"

#include "XCCFileView.h"
#include "XSE_dlg.h"
#include "XSTE_dlg.h"

#include <assert.h>
#include <fstream>
#include "aud_file.h"
#include "directoriesdlg.h"
#include "fname.h"
#include "html.h"
#include "mix_sfl.h"
#include "ogg_file.h"
#include "searchfiledlg.h"
#include "selectpaletdlg.h"
#include "string_conversion.h"
#include "theme_ts_ini_reader.h"
#include "wav_file.h"
#include "xcc_dirs.h"
#include "xcc_log.h"
#include "xccobjectextractordlg.h"
#include "xste.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	// ON_COMMAND(ID_VIEW_DIRECTX_OPTIONS, OnViewDirectxOptions)
	ON_COMMAND_RANGE(ID_VIEW_PALET_PAL000, ID_VIEW_PALET_PAL999, OnViewPalet)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_PALET_PAL000, ID_VIEW_PALET_PAL999, OnUpdateViewPalet)
	ON_COMMAND_RANGE(ID_LAUNCH_XMC, ID_LAUNCH_XML, OnLaunchApp)
	ON_UPDATE_COMMAND_UI_RANGE(ID_LAUNCH_XMC, ID_LAUNCH_XML, OnUpdateLaunchApp)
	// ON_COMMAND(ID_LAUNCH_XSTE, OnLaunchXSTE)
	// ON_UPDATE_COMMAND_UI(ID_LAUNCH_XSTE, OnUpdateLaunchXSTE)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_GAME_TD, OnViewGameTD)
	ON_COMMAND(ID_VIEW_GAME_RA, OnViewGameRA)
	ON_COMMAND(ID_VIEW_GAME_TS, OnViewGameTS)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GAME_TD, OnUpdateViewGameTD)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GAME_RA, OnUpdateViewGameRA)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GAME_TS, OnUpdateViewGameTS)
	ON_UPDATE_COMMAND_UI(ID_FILE_FOUND_UPDATE, OnUpdateFileFoundUpdate)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PALET_UPDATE, OnUpdateViewPaletUpdate)
	ON_COMMAND(ID_VIEW_GAME_AUTO, OnViewGameAuto)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GAME_AUTO, OnUpdateViewGameAuto)
	ON_COMMAND(ID_VIEW_PALET_AUTO, OnViewPaletAuto)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PALET_AUTO, OnUpdateViewPaletAuto)
	ON_COMMAND(ID_VIEW_PALET_PREV, OnViewPaletPrev)
	ON_COMMAND(ID_VIEW_PALET_NEXT, OnViewPaletNext)
	ON_COMMAND(ID_VIEW_PALET_USE_FOR_CONVERSION, OnViewPaletUseForConversion)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PALET_USE_FOR_CONVERSION, OnUpdateViewPaletUseForConversion)
	ON_COMMAND(ID_VIEW_PALET_CONVERT_FROM_TD, OnViewPaletConvertFromTD)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PALET_CONVERT_FROM_TD, OnUpdateViewPaletConvertFromTD)
	ON_COMMAND(ID_VIEW_PALET_CONVERT_FROM_RA, OnViewPaletConvertFromRA)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PALET_CONVERT_FROM_RA, OnUpdateViewPaletConvertFromRA)
	ON_COMMAND(ID_INTERNET_FS_SITE, OnInternetFsSite)
	ON_COMMAND(ID_INTERNET_SE_SITE, OnInternetSeSite)
	ON_COMMAND(ID_INTERNET_XCC_SITE, OnInternetXccSite)
	ON_COMMAND(ID_VIEW_VOXEL_NORMAL, OnViewVoxelNormal)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VOXEL_NORMAL, OnUpdateViewVoxelNormal)
	ON_COMMAND(ID_VIEW_VOXEL_SURFACE_NORMALS, OnViewVoxelSurfaceNormals)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VOXEL_SURFACE_NORMALS, OnUpdateViewVoxelSurfaceNormals)
	ON_COMMAND(ID_VIEW_VOXEL_DEPTH_INFORMATION, OnViewVoxelDepthInformation)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VOXEL_DEPTH_INFORMATION, OnUpdateViewVoxelDepthInformation)
	ON_COMMAND(ID_CONVERSION_SPLIT_SHADOWS, OnConversionSplitShadows)
	ON_UPDATE_COMMAND_UI(ID_CONVERSION_SPLIT_SHADOWS, OnUpdateConversionSplitShadows)
	ON_COMMAND(ID_UTILITIES_XCC_AV_PLAYER, OnUtilitiesXccAvPlayer)
	ON_UPDATE_COMMAND_UI(ID_UTILITIES_XCC_AV_PLAYER, OnUpdateUtilitiesXccAvPlayer)
	ON_COMMAND(ID_UTILITIES_XCC_EDITOR, OnUtilitiesXccEditor)
	ON_UPDATE_COMMAND_UI(ID_UTILITIES_XCC_EDITOR, OnUpdateUtilitiesXccEditor)
	ON_COMMAND(ID_UTILITIES_XCC_MIX_EDITOR, OnUtilitiesXccMixEditor)
	ON_UPDATE_COMMAND_UI(ID_UTILITIES_XCC_MIX_EDITOR, OnUpdateUtilitiesXccMixEditor)
	ON_COMMAND(ID_VIEW_DIRECTORIES, OnViewDirectories)
	ON_COMMAND(ID_UTILITIES_FS, OnUtilitiesFS)
	ON_UPDATE_COMMAND_UI(ID_UTILITIES_FS, OnUpdateUtilitiesFS)
	ON_COMMAND(ID_UTILITIES_SEMM, OnUtilitiesSEMM)
	ON_UPDATE_COMMAND_UI(ID_UTILITIES_SEMM, OnUpdateUtilitiesSEMM)
	ON_COMMAND(ID_UTILITIES_SE, OnUtilitiesSE)
	ON_UPDATE_COMMAND_UI(ID_UTILITIES_SE, OnUpdateUtilitiesSE)
	ON_COMMAND(ID_LAUNCH_DUNE2, OnLaunchDune2)
	ON_COMMAND(ID_LAUNCH_TD, OnLaunchTD)
	ON_COMMAND(ID_LAUNCH_RA, OnLaunchRA)
	ON_COMMAND(ID_LAUNCH_DUNE2000, OnLaunchDune2000)
	ON_COMMAND(ID_LAUNCH_RA2, OnLaunchRA2)
	ON_COMMAND(ID_LAUNCH_TS, OnLaunchTS)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_DUNE2, OnUpdateLaunchDune2)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_DUNE2000, OnUpdateLaunchDune2000)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_RA, OnUpdateLaunchRA)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_RA2, OnUpdateLaunchRA2)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_TD, OnUpdateLaunchTD)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_TS, OnUpdateLaunchTS)
	ON_COMMAND(ID_FILE_SEARCH, OnFileSearch)
	ON_COMMAND(ID_FILE_CREATE_SFL, OnFileCreateSFL)
	ON_COMMAND(ID_LAUNCH_XOE_RA2, OnLaunchXOE_RA2)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_XOE_RA2, OnUpdateLaunchXOE_RA2)
	ON_COMMAND(ID_LAUNCH_XOE_TS, OnLaunchXOE_TS)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_XOE_TS, OnUpdateLaunchXOE_TS)
	ON_COMMAND(ID_LAUNCH_XSE, OnLaunchXSE)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_XSE, OnUpdateLaunchXSE)
	ON_COMMAND(ID_LAUNCH_FA, OnLaunchFA)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_FA, OnUpdateLaunchFA)
	ON_COMMAND(ID_LAUNCH_RAGE, OnLaunchRAGE)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_RAGE, OnUpdateLaunchRAGE)
	ON_COMMAND(ID_CONVERSION_ENABLE_COMPRESSION, OnConversionEnableCompression)
	ON_UPDATE_COMMAND_UI(ID_CONVERSION_ENABLE_COMPRESSION, OnUpdateConversionEnableCompression)
	ON_WM_DESTROY()
	ON_COMMAND(ID_LAUNCH_XTW_TS, OnLaunchXTW_TS)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_XTW_TS, OnUpdateLaunchXTW_TS)
	ON_COMMAND(ID_LAUNCH_XTW_RA2, OnLaunchXTW_RA2)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_XTW_RA2, OnUpdateLaunchXTW_RA2)
	ON_COMMAND(ID_CONVERSION_COMBINE_SHADOWS, OnConversionCombineShadows)
	ON_UPDATE_COMMAND_UI(ID_CONVERSION_COMBINE_SHADOWS, OnUpdateConversionCombineShadows)
	ON_COMMAND(ID_VIEW_REPORT, OnViewReport)
	ON_UPDATE_COMMAND_UI(ID_VIEW_REPORT, OnUpdateViewReport)
	ON_COMMAND(ID_LAUNCH_XSTE_RA2, OnLaunchXSTE_RA2)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_XSTE_RA2, OnUpdateLaunchXSTE_RA2)
	ON_COMMAND(ID_LAUNCH_XSTE_RA2_YR, OnLaunchXSTE_RA2_YR)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_XSTE_RA2_YR, OnUpdateLaunchXSTE_RA2_YR)
	ON_COMMAND(ID_LAUNCH_XTW_RA2_YR, OnLaunchXTW_RA2_YR)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_XTW_RA2_YR, OnUpdateLaunchXTW_RA2_YR)
	ON_COMMAND(ID_VIEW_PALET_SELECT, OnViewPaletSelect)
	ON_COMMAND(ID_VIEW_PALET_AUTO_SELECT, OnViewPaletAutoSelect)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PALET_AUTO_SELECT, OnUpdateViewPaletAutoSelect)
	ON_COMMAND(ID_LAUNCH_XSTE_GR, OnLaunchXSTE_GR)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_XSTE_GR, OnUpdateLaunchXSTE_GR)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_convert_from_td = false;
	m_convert_from_ra = false;
	m_dd = NULL;
	m_ds = NULL;
	m_enable_compression = true;
	m_remap_team_colors = false;
	m_combine_shadows = m_split_shadows = false;
	m_game = static_cast<t_game>(-1);
	m_lists_initialized = false;
	m_palet_i = -1;
	m_reg_key = "MainFrame";
	m_vxl_mode = 0;
	m_use_palet_for_conversion = false;

	m_combine_shadows = AfxGetApp()->GetProfileInt(m_reg_key, "combine_shadows", false);
	m_enable_compression = AfxGetApp()->GetProfileInt(m_reg_key, "enable_compression", true);
	m_palet_i = AfxGetApp()->GetProfileInt(m_reg_key, "palet_i", -1);
	m_split_shadows = AfxGetApp()->GetProfileInt(m_reg_key, "split_shadows", false);
	m_use_palet_for_conversion = AfxGetApp()->GetProfileInt(m_reg_key, "use_palet_for_conversion", false);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~FWS_ADDTOTITLE;
	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (!m_wndSplitter.CreateStatic(this, 1, 3))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	if (!m_wndSplitter.CreateView(0, 0,	pContext->m_pNewViewClass, CSize(300, 0), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	if (!m_wndSplitter.CreateView(0, 1,	pContext->m_pNewViewClass, CSize(0, 0), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}

	if (!m_wndSplitter.CreateView(0, 2,	RUNTIME_CLASS(CXCCFileView), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create third pane\n");
		return FALSE;
	}

	m_left_mix_pane = reinterpret_cast<CXCCMixerView*>(m_wndSplitter.GetPane(0, 0));
	m_right_mix_pane = reinterpret_cast<CXCCMixerView*>(m_wndSplitter.GetPane(0, 1));
	m_file_info_pane = reinterpret_cast<CXCCFileView*>(m_wndSplitter.GetPane(0, 2));

	m_left_mix_pane->set_other_panes(m_file_info_pane, m_right_mix_pane);
	m_right_mix_pane->set_other_panes(m_file_info_pane, m_left_mix_pane);

	m_left_mix_pane->set_reg_key("left_mix_pame");
	m_right_mix_pane->set_reg_key("right_mix_pame");

	SetActiveView(reinterpret_cast<CView*>(m_left_mix_pane));

	return true;
}

void CMainFrame::OnViewGameAuto() 
{
	m_game = static_cast<t_game>(-1);
}

void CMainFrame::OnViewGameTD() 
{
	m_game = game_td;
}

void CMainFrame::OnViewGameRA() 
{
	m_game = game_ra;
}

void CMainFrame::OnViewGameTS() 
{
	m_game = game_ts;
}

void CMainFrame::OnUpdateViewGameAuto(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_game == -1);
}

void CMainFrame::OnUpdateViewGameTD(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_game == game_td);
}

void CMainFrame::OnUpdateViewGameRA(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_game == game_ra);
}

void CMainFrame::OnUpdateViewGameTS(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_game == game_ts);
}

t_game CMainFrame::get_game()
{
	return m_game;
}

void CMainFrame::set_msg(const string& s)
{
	SetMessageText(s.c_str());
}

int CMainFrame::mix_list_create_map(string name, string fname, int file_id, int parent)
{
	int id = m_mix_map_list.size();
	t_mix_map_list_entry& e = m_mix_map_list[id];
	e.name = name;
	e.fname = fname;
	e.id = file_id;
	e.parent = parent;
	return id;
}

int CMainFrame::pal_list_create_map(string name, int parent)
{
	int id = m_pal_map_list.size();
	t_pal_map_list_entry& e = m_pal_map_list[id];
	e.name = name;
	e.parent = parent;
	return id;
}

void CMainFrame::clean_pal_map_list()
{
	typedef set<int> t_used_set;
	t_used_set used_set;
	{
		typedef t_pal_list t_map;
		const t_map& map = m_pal_list;
		for (t_map::const_iterator i = map.begin(); i != map.end(); i++)
			used_set.insert(i->second.parent);
	}
	{
		typedef t_pal_map_list t_map;
		const t_map& map = m_pal_map_list;
		for (t_map::const_iterator i = map.begin(); i != map.end(); i++)
		{
			if (used_set.find(i->first) == used_set.end())
				continue;
			int p = i->second.parent;
			while (p != -1)
			{
				used_set.insert(p);
				p = m_pal_map_list.find(p)->second.parent;
			}
		}
	}
	{
		typedef t_pal_map_list t_map;
		t_map& map = m_pal_map_list;
		for (t_map::iterator i = map.begin(); i != map.end(); )
		{
			if (used_set.find(i->first) == used_set.end())
				i = map.erase(i);
			else
				i++;
		}
	}
}

void CMainFrame::do_mix(Cmix_file& f, const string& mix_name, int mix_parent, int pal_parent)
{
	xcc_log::write_line("do_mix starts: " + mix_name, 1);
	set_msg("Reading " + mix_name);
	if (mix_name.find(" - ") == string::npos)
		m_mix_list[m_mix_list.size()] = mix_name;
	Cmix_file g;
	Cpal_file h;
	for (int i = 0; i < f.get_c_files(); i++)
	{
		const int id = f.get_id(i);
		string name = f.get_name(id);
		if (name.empty())
			name = nh(8, id);
		switch (f.get_type(id))
		{
		case ft_mix:
			if (!g.open(id, f))
			{
				do_mix(g, mix_name + " - " + name, mix_list_create_map(name, "", id, mix_parent), pal_list_create_map(name, pal_parent));
				g.close();
			}
			break;
		case ft_pal:
			{
				t_pal_list_entry e;
				e.name = static_cast<Cfname>(mix_name).get_fname() + " - " + name;
				h.open(id, f);
				memcpy(e.palet, h.get_data(), sizeof(t_palet));
				h.close();
				e.parent = pal_parent;
				m_pal_list[m_pal_list.size()] = e;
				break;
			}
		}
	}
	xcc_log::write_line("do_mixs ends", -1);
}

void CMainFrame::find_mixs(const string& dir, t_game game, string filter)
{
	xcc_log::write_line("find_mixs starts: " + dir, 1);
	if (!dir.empty())
	{
		WIN32_FIND_DATA fd;
		HANDLE findhandle = FindFirstFile((dir + filter).c_str(), &fd);
		if (findhandle != INVALID_HANDLE_VALUE)
		{
			int mix_parent = mix_list_create_map(game_name[game], "", 0, -1);
			int pal_parent = pal_list_create_map(game_name[game], -1);
			do
			{
				if (~fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					const string fname = to_lower(fd.cFileName);
					xcc_log::write_line("finds: " + fname, 1);
					Cmix_file f;
					if (!f.open(dir + fname))
					{
						do_mix(f, dir + fname, mix_list_create_map(fname, dir + fname, 0, mix_parent), pal_list_create_map(fname, pal_parent));
						f.close();
					}
					xcc_log::indent(-1);
				}
			}
			while (FindNextFile(findhandle, &fd));
			FindClose(findhandle);
		}
	}
	m_mix_i[game] = m_mix_list.size();
	m_pal_i[game] = m_pal_list.size();
	xcc_log::write_line("find_mixs ends", -1);
}

typedef map<string, int> t_sort_list;

string escape_menu_name(string v)
{
	for (int i = 0; i < v.length(); i++)
	{
		if (v[i] == '&')
			v.insert(++i, "&");
	}
	return v;
}

void CMainFrame::OnUpdateFileFoundUpdate(CCmdUI* pCmdUI) 
{       
	xcc_log::write_line("OnUpdateFileFoundUpdate starts");
	CMenu* menu = pCmdUI->m_pSubMenu;
	if (menu)
	{
		menu->DeleteMenu(0, MF_BYPOSITION);
		initialize_lists();
		int j = 0;
		int k = 0;
		for (int i = 0; i < game_unknown; i++)
		{
			if (j == m_mix_i[i])
				continue;
			CMenu sub_menu;
			sub_menu.CreatePopupMenu();
			t_sort_list sort_list;
			while (j < m_mix_i[i])
			{
				sort_list[static_cast<Cfname>(m_mix_list[j]).get_fname()] = j;
				j++;
			}
			if (sort_list.empty())
				continue;
			for (t_sort_list::const_iterator l = sort_list.begin(); l != sort_list.end(); l++)
				sub_menu.AppendMenu(MF_STRING, ID_FILE_FOUND_MIX00 + l->second, escape_menu_name(l->first).c_str());
			menu->InsertMenu(k++, MF_BYPOSITION | MF_POPUP, reinterpret_cast<dword>(sub_menu.GetSafeHmenu()), game_name[i]);
			sub_menu.Detach();
		}
	}
	xcc_log::write_line("OnUpdateFileFoundUpdate ends");
}

void CMainFrame::OnUpdateViewPaletUpdate(CCmdUI* pCmdUI) 
{
	xcc_log::write_line("OnUpdateViewPaletUpdate starts");
	CMenu* menu = pCmdUI->m_pSubMenu;
	if (menu)
	{
		menu->DeleteMenu(0, MF_BYPOSITION);
		initialize_lists();
		int j = 0;
		int k = 0;
		for (int i = 0; i < game_unknown; i++)
		{
			if (j == m_pal_i[i])
				continue;
			CMenu sub_menu;
			sub_menu.CreatePopupMenu();
			for (; j < m_pal_i[i]; j++)
				sub_menu.AppendMenu(MF_STRING, ID_VIEW_PALET_PAL000 + j, m_pal_list[j].name.c_str());
			menu->InsertMenu(k++, MF_BYPOSITION | MF_POPUP, reinterpret_cast<dword>(sub_menu.GetSafeHmenu()), game_name[i]);
			sub_menu.Detach();
		}
	}
	xcc_log::write_line("OnUpdateViewPaletUpdate ends");
}

void CMainFrame::initialize_lists()
{
	if (m_lists_initialized)
		return;
	CWaitCursor wait;
	xcc_log::write_line("initialize_lists starts");
	xcc_log::write_line("primary dir: " + xcc_dirs::get_td_primary_dir());
	xcc_log::write_line("secondary dir: " + xcc_dirs::get_td_secondary_dir());
	xcc_log::write_line("ra dir: " + xcc_dirs::get_ra_dir());
	xcc_log::write_line("ts dir: " + xcc_dirs::get_ts_dir());
	xcc_log::write_line("cd dir: " + xcc_dirs::get_cd_dir());
	xcc_log::write_line("data dir: " + xcc_dirs::get_data_dir());
	find_mixs(xcc_dirs::get_td_primary_dir(), game_td, "*.mix");
	find_mixs(xcc_dirs::get_td_secondary_dir(), game_td, "*.mix");
	find_mixs(xcc_dirs::get_ra_dir(), game_ra, "*.mix");
	find_mixs(xcc_dirs::get_ts_dir(), game_ts, "*.mix");
	find_mixs(xcc_dirs::get_dune2_dir(), game_dune2, "*.pak");
	find_mixs(xcc_dirs::get_dune2000_dir(), game_dune2000, "*.mix");
	find_mixs(xcc_dirs::get_ra2_dir(), game_ra2, "*.mix");
	find_mixs("", game_ra2_yr, "");
	find_mixs(xcc_dirs::get_dir(game_rg) + "data\\", game_rg, "*.dat");
	find_mixs(xcc_dirs::get_dir(game_rg) + "data\\", game_rg, "*.dbs");
	find_mixs(xcc_dirs::get_dir(game_rg) + "data\\", game_rg, "*.mix");
	find_mixs(xcc_dirs::get_dir(game_rg) + "data\\", game_rg, "*.pkg");

	t_pal_list pal_list = m_pal_list;
	m_pal_list.clear();
	int j = 0;
	int k = 0;
	for (int i = 0; i < game_unknown; i++)
	{
		t_sort_list sort_list;
		while (j < m_pal_i[i])
		{
			sort_list[pal_list[j].name] = j;
			j++;
		}
		for (t_sort_list::const_iterator l = sort_list.begin(); l != sort_list.end(); l++)
			m_pal_list[k++] = pal_list.find(l->second)->second;
	}

	Cmix_file f1, f2;
	Cpal_file pal_f;
	if (!f1.open("temperat.mix"))
	{
		if (!pal_f.open("temperat.pal", f1))
		{
			memcpy(m_td_palet, pal_f.get_palet(), sizeof(t_palet));
			pal_f.close();
		}
		f1.close();
	}
	if (!f1.open("redalert.mix"))
	{
		if (!f2.open("local.mix", f1))
		{
			if (!pal_f.open("temperat.pal", f2))
			{
				memcpy(m_ra_palet, pal_f.get_palet(), sizeof(t_palet));
				pal_f.close();
			}
			f2.close();
		}
		f1.close();
	}
	if (!f1.open("tibsun.mix"))
	{
		if (!f2.open("cache.mix", f1))
		{
			if (!pal_f.open("unittem.pal", f2))
			{
				memcpy(m_ts_palet, pal_f.get_palet(), sizeof(t_palet));
				pal_f.close();
			}
			f2.close();
		}
		f1.close();
	}
	if (m_palet_i >= m_pal_list.size())
		m_palet_i = -1;
	clean_pal_map_list();
	m_lists_initialized = true;
	xcc_log::write_line("initialize_lists ends");
}

string CMainFrame::get_mix_name(int i) const
{
	return m_mix_list.find(i)->second;
}

const t_paletentry* CMainFrame::get_game_palet(t_game game)
{
	initialize_lists();
	switch (game)
	{
	case game_td:
		return m_td_palet;
	case game_ra:
		return m_ra_palet;
	default:
		return m_ts_palet;
	}
}

const t_paletentry* CMainFrame::get_pal_data()
{
	initialize_lists();
	return m_palet_i == -1 ? NULL : m_pal_list.find(m_palet_i)->second.palet;
}

int CMainFrame::get_vxl_mode() const
{
	return m_vxl_mode;
}

void CMainFrame::OnViewPaletAuto() 
{
	set_palet(-1);
}

void CMainFrame::OnUpdateViewPaletAuto(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_palet_i == -1);
}

void CMainFrame::OnViewPalet(dword ID) 
{
	set_palet(ID - ID_VIEW_PALET_PAL000);
}

void CMainFrame::OnUpdateViewPalet(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_palet_i == pCmdUI->m_nID - ID_VIEW_PALET_PAL000);
}

void CMainFrame::OnViewPaletPrev() 
{
	if (m_pal_i[game_ra2])
	{
		if (m_palet_i > -1)
			m_palet_i--;
		m_file_info_pane->Invalidate();
		set_msg((m_palet_i == -1 ? "default" : m_pal_list.find(m_palet_i)->second.name) + " selected");
	}
}

void CMainFrame::OnViewPaletNext() 
{
	if (m_pal_i[game_ra2])
	{
		m_palet_i++;
		if (m_palet_i == m_pal_i[game_ra2])
			m_palet_i = 0;
		m_file_info_pane->Invalidate();
		set_msg(m_pal_list.find(m_palet_i)->second.name + " selected");
	}
}

bool CMainFrame::auto_select(t_game game, string palet)
{
	for (int i = game < 1 ? 0 : m_pal_i[game - 1]; i < m_pal_i[game]; i++)
	{
		if (m_pal_list.find(i)->second.name.find(palet) == string::npos)
			continue;	
		set_palet(i);
		set_msg(m_pal_list.find(m_palet_i)->second.name + " selected");
		return true;
	}
	return false;
}

void CMainFrame::OnViewPaletUseForConversion() 
{
	m_use_palet_for_conversion = !m_use_palet_for_conversion;
}

void CMainFrame::OnUpdateViewPaletUseForConversion(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_use_palet_for_conversion);
}

void CMainFrame::OnViewPaletConvertFromTD() 
{
	m_convert_from_td = !m_convert_from_td;	
	m_convert_from_ra = false;
}

void CMainFrame::OnUpdateViewPaletConvertFromTD(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_convert_from_td);
}

void CMainFrame::OnViewPaletConvertFromRA() 
{
	m_convert_from_td = false;
	m_convert_from_ra = !m_convert_from_ra;	
}

void CMainFrame::OnUpdateViewPaletConvertFromRA(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_convert_from_ra);
}

void CMainFrame::OnInternetFsSite() 
{
	ShellExecute(m_hWnd, "open", "http://finalsun.wagnerma.de/", NULL, NULL, SW_SHOW);
}

void CMainFrame::OnInternetSeSite() 
{
	ShellExecute(m_hWnd, "open", "http://www.childs-play-software.co.uk/", NULL, NULL, SW_SHOW);
}

void CMainFrame::OnInternetXccSite() 
{
	ShellExecute(m_hWnd, "open", "http://xcc.tiberian.com/", NULL, NULL, SW_SHOW);
}

void CMainFrame::OnViewVoxelNormal() 
{
	m_vxl_mode = 0;
	m_file_info_pane->Invalidate();
}

void CMainFrame::OnUpdateViewVoxelNormal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_vxl_mode == 0);
}

void CMainFrame::OnViewVoxelSurfaceNormals() 
{
	m_vxl_mode = 1;
	m_file_info_pane->Invalidate();
}

void CMainFrame::OnUpdateViewVoxelSurfaceNormals(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_vxl_mode == 1);
}

void CMainFrame::OnViewVoxelDepthInformation() 
{
	m_vxl_mode = 2;
	m_file_info_pane->Invalidate();
}

void CMainFrame::OnUpdateViewVoxelDepthInformation(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_vxl_mode == 2);
}

void CMainFrame::OnConversionCombineShadows() 
{
	m_combine_shadows = !m_combine_shadows;	
}

void CMainFrame::OnUpdateConversionCombineShadows(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_combine_shadows);
}

void CMainFrame::OnConversionSplitShadows() 
{
	m_split_shadows = !m_split_shadows;	
}

void CMainFrame::OnUpdateConversionSplitShadows(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_split_shadows);
}

void CMainFrame::OnConversionEnableCompression() 
{
	m_enable_compression = !m_enable_compression;	
}

void CMainFrame::OnUpdateConversionEnableCompression(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_enable_compression);
}

void CMainFrame::OnConversionRemapTeamColors() 
{
	m_remap_team_colors = !m_remap_team_colors;	
}

void CMainFrame::OnUpdateConversionRemapTeamColors(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(false);
	pCmdUI->SetCheck(m_remap_team_colors);
}

LPDIRECTDRAW CMainFrame::get_dd()
{
	if (!m_dd)
		open_dd();
	return m_dd;
}

void CMainFrame::open_dd()
{
	HRESULT ddr;
	assert(!m_dd);
    ddr = DirectDrawCreate(NULL, &m_dd, NULL);
	xcc_log::write_line("DirectDrawCreate returned " + nh(8, ddr));
}

void CMainFrame::close_dd()
{
	if (m_dd)
	{
		m_dd->Release();
		m_dd = NULL;
	}
}

LPDIRECTSOUND CMainFrame::get_ds()
{
	if (!m_ds)
		open_ds();
	return m_ds;
}

void CMainFrame::open_ds()
{
	HRESULT dsr;
	assert(!m_ds);
    dsr = DirectSoundCreate(NULL, &m_ds, NULL);
	xcc_log::write_line("DirectSoundCreate returned " + nh(8, dsr));
	if (m_ds)
	{
		dsr = m_ds->SetCooperativeLevel(m_hWnd, DSSCL_NORMAL);
		xcc_log::write_line("SetCooperativeLevel returned " + nh(8, dsr));
	}
}

void CMainFrame::close_ds()
{
	if (m_ds)
	{
		m_ds->Release();
		m_ds = NULL;
	}
}

static CXCCMixerApp* GetApp()
{
	return static_cast<CXCCMixerApp*>(AfxGetApp());
}

void CMainFrame::OnUtilitiesXccAvPlayer() 
{
	ShellExecute(m_hWnd, NULL, GetApp()->get_xcc_av_player_exe().c_str(), NULL, NULL, SW_SHOW);
}

void CMainFrame::OnUtilitiesXccEditor() 
{
	ShellExecute(m_hWnd, NULL, GetApp()->get_xcc_editor_exe().c_str(), NULL, NULL, SW_SHOW);
}

void CMainFrame::OnUtilitiesXccMixEditor() 
{
	ShellExecute(m_hWnd, NULL, GetApp()->get_xcc_mix_editor_exe().c_str(), NULL, NULL, SW_SHOW);
}

void CMainFrame::OnLaunchApp(dword ID) 
{
	t_app app = static_cast<t_app>(app_xmc + ID - ID_LAUNCH_XMC);
	ShellExecute(m_hWnd, NULL, m_apps.get_exe(app).c_str(), NULL, NULL, SW_SHOW);
}

void CMainFrame::OnUpdateUtilitiesXccAvPlayer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetApp()->is_xcc_av_player_available());
}

void CMainFrame::OnUpdateUtilitiesXccEditor(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetApp()->is_xcc_editor_available());
}

void CMainFrame::OnUpdateUtilitiesXccMixEditor(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetApp()->is_xcc_mix_editor_available());
}

void CMainFrame::OnUpdateLaunchApp(CCmdUI* pCmdUI) 
{
	t_app app = static_cast<t_app>(app_xmc + pCmdUI->m_nID - ID_LAUNCH_XMC);
	pCmdUI->Enable(m_apps.is_available(app));
}

void CMainFrame::OnViewDirectories() 
{
	CDirectoriesDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnViewDirectxOptions() 
{
}

void CMainFrame::OnUtilitiesFS() 
{
	ShellExecute(m_hWnd, NULL, GetApp()->get_fs_exe().c_str(), NULL, NULL, SW_SHOW);
}

void CMainFrame::OnLaunchFA() 
{
	ShellExecute(m_hWnd, NULL, GetApp()->get_fa_exe().c_str(), NULL, NULL, SW_SHOW);
}

void CMainFrame::OnUtilitiesSE() 
{
	ShellExecute(m_hWnd, NULL, GetApp()->get_se_exe().c_str(), NULL, NULL, SW_SHOW);
}

void CMainFrame::OnUtilitiesSEMM() 
{
	ShellExecute(m_hWnd, NULL, GetApp()->get_semm_exe().c_str(), NULL, NULL, SW_SHOW);
}


void CMainFrame::OnLaunchRAGE() 
{
	ShellExecute(m_hWnd, NULL, GetApp()->get_rage_exe().c_str(), NULL, NULL, SW_SHOW);
}

void CMainFrame::OnUpdateUtilitiesFS(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetApp()->is_fs_available());
}

void CMainFrame::OnUpdateLaunchFA(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetApp()->is_fa_available());
}

void CMainFrame::OnUpdateUtilitiesSE(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetApp()->is_se_available());
}

void CMainFrame::OnUpdateUtilitiesSEMM(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetApp()->is_semm_available());
}

void CMainFrame::OnUpdateLaunchRAGE(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetApp()->is_rage_available());
}

void CMainFrame::OnLaunchDune2() 
{
	ShellExecute(m_hWnd, NULL, GetApp()->get_dune2_exe().c_str(), NULL, NULL, SW_SHOW);
}

void CMainFrame::OnLaunchTD() 
{
	if (GetApp()->is_td_win_available())
		ShellExecute(m_hWnd, NULL, GetApp()->get_td_win_exe().c_str(), NULL, NULL, SW_SHOW);
	else
		ShellExecute(m_hWnd, NULL, GetApp()->get_td_dos_exe().c_str(), NULL, NULL, SW_SHOW);
}

void CMainFrame::OnLaunchRA() 
{
	if (GetApp()->is_ra_win_available())
		ShellExecute(m_hWnd, NULL, GetApp()->get_ra_win_exe().c_str(), NULL, NULL, SW_SHOW);
	else
		ShellExecute(m_hWnd, NULL, GetApp()->get_ra_dos_exe().c_str(), NULL, NULL, SW_SHOW);
}

void CMainFrame::OnLaunchDune2000() 
{
	ShellExecute(m_hWnd, NULL, GetApp()->get_dune2000_exe().c_str(), NULL, NULL, SW_SHOW);
}

void CMainFrame::OnLaunchTS() 
{
	ShellExecute(m_hWnd, NULL, GetApp()->get_ts_exe().c_str(), NULL, NULL, SW_SHOW);
}

void CMainFrame::OnLaunchRA2() 
{
	ShellExecute(m_hWnd, NULL, GetApp()->get_ra2_exe().c_str(), NULL, NULL, SW_SHOW);
}


void CMainFrame::OnUpdateLaunchDune2(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetApp()->is_dune2_available());
}

void CMainFrame::OnUpdateLaunchTD(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetApp()->is_td_dos_available() || GetApp()->is_td_win_available());
}

void CMainFrame::OnUpdateLaunchRA(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetApp()->is_ra_dos_available() || GetApp()->is_ra_win_available());
}

void CMainFrame::OnUpdateLaunchDune2000(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetApp()->is_dune2000_available());
}

void CMainFrame::OnUpdateLaunchTS(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetApp()->is_ts_available());
}

void CMainFrame::OnUpdateLaunchRA2(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetApp()->is_ra2_available());
}

void CMainFrame::OnFileSearch() 
{
	CSearchFileDlg dlg;
	dlg.set(this);
	dlg.DoModal();
}

static void add_mix_to_sfl(t_game game, Cmix_file& g)
{
	for (int i = 0; i < g.get_c_files(); i++)
	{
		int id = g.get_id(i);
		mix_sfl::insert(game, id);
		if (g.get_type(id) == ft_mix)
		{
			Cmix_file f;
			if (!f.open(id, g))
			{
				add_mix_to_sfl(game, f);
				f.close();
			}
		}
	}
}

void CMainFrame::OnFileCreateSFL() 
{
	CWaitCursor wait;
	mix_sfl::clear(game_ts);
	for (int i = m_mix_i[game_ra]; i < m_mix_i[game_ts]; i++)
	{
		Cmix_file f;
		if (!f.open(m_mix_list[i]))
		{
			add_mix_to_sfl(game_ts, f);
			f.close();
		}
	}
	mix_sfl::clear(game_ra2);
	for (; i < m_mix_i[game_ra2]; i++)
	{
		Cmix_file f;
		if (!f.open(m_mix_list[i]))
		{
			add_mix_to_sfl(game_ra2, f);
			f.close();
		}
	}
	mix_sfl::save();
}

void CMainFrame::OnLaunchXOE_TS() 
{
	CXCCObjectExtractorDlg dlg(game_ts);
	dlg.DoModal();
}

void CMainFrame::OnUpdateLaunchXOE_TS(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!xcc_dirs::get_ts_dir().empty());
}

void CMainFrame::OnLaunchXOE_RA2() 
{
	CXCCObjectExtractorDlg dlg(game_ra2);
	dlg.DoModal();
}

void CMainFrame::OnUpdateLaunchXOE_RA2(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!xcc_dirs::get_ra2_dir().empty());	
}

/*
void CMainFrame::OnLaunchXSTE() 
{
	CXSTE_dlg dlg(game_ra2, false);
	dlg.DoModal();
}

void CMainFrame::OnUpdateLaunchXSTE(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!xcc_dirs::get_ra2_dir().empty());	
}
*/

void CMainFrame::OnLaunchXSTE_RA2() 
{
	CXSTE_dlg dlg(game_ra2);
	dlg.DoModal();
}

void CMainFrame::OnUpdateLaunchXSTE_RA2(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!xcc_dirs::get_ra2_dir().empty());		
}

void CMainFrame::OnLaunchXSTE_RA2_YR() 
{
	CXSTE_dlg dlg(game_ra2_yr);
	dlg.DoModal();
}

void CMainFrame::OnUpdateLaunchXSTE_RA2_YR(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(Cfname(xcc_dirs::get_main_mix(game_ra2_yr)).exists());
}

void CMainFrame::OnLaunchXSTE_GR() 
{
	CXSTE_dlg dlg(game_gr);
	dlg.DoModal();
}

void CMainFrame::OnUpdateLaunchXSTE_GR(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(Cfname(xcc_dirs::get_dir(game_gr) + xcc_dirs::get_csf_fname(game_gr)).exists());	
}

void CMainFrame::OnLaunchXSE() 
{
	CXSE_dlg dlg(Cfname(xcc_dirs::get_main_mix(game_ra2_yr)).exists() ? game_ra2_yr : game_ra2);
	dlg.DoModal();
}

void CMainFrame::OnUpdateLaunchXSE(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!xcc_dirs::get_ra2_dir().empty());	
}

void CMainFrame::OnDestroy() 
{
	AfxGetApp()->WriteProfileInt(m_reg_key, "combine_shadows", m_combine_shadows);
	AfxGetApp()->WriteProfileInt(m_reg_key, "enable_compression", m_enable_compression);
	AfxGetApp()->WriteProfileInt(m_reg_key, "palet_i", m_palet_i);
	AfxGetApp()->WriteProfileInt(m_reg_key, "split_shadows", m_split_shadows);
	AfxGetApp()->WriteProfileInt(m_reg_key, "use_palet_for_conversion", m_use_palet_for_conversion);
	CFrameWnd::OnDestroy();
}

typedef map<string, Ctheme_data> t_theme_list;

void CMainFrame::OnLaunchXTW_TS() 
{
	Cmix_file tibsun;
	if (!tibsun.open("tibsun.mix"))
	{
		Cmix_file local;
		if (!local.open("local.mix", tibsun))
		{
			Ccc_file theme(true);
			if (!theme.open("theme.ini", local))
			{
				Ctheme_ts_ini_reader ir;
				if (!ir.process(theme.get_data(), theme.get_size()))
				{
					t_theme_list theme_list = ir.get_theme_list();
					string dir = xcc_dirs::get_ts_dir();
					WIN32_FIND_DATA fd;
					HANDLE findhandle = FindFirstFile((dir + "*.aud").c_str(), &fd);
					if (findhandle != INVALID_HANDLE_VALUE)
					{
						do
						{
							if (~fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
							{
								const string fname = dir + fd.cFileName;
								Caud_file f;
								if (!f.open(fname))
								{
									char b[MAX_PATH];
									int error = GetShortPathName(fname.c_str(), b, MAX_PATH);
									if (error > 0 && error < MAX_PATH)
									{
										Ctheme_data e;
										e.name(Cfname(fd.cFileName).get_ftitle());
										e.length(static_cast<float>(f.get_c_samples()) / f.get_samplerate() / 60);
										theme_list[to_upper(Cfname(b).get_ftitle())] = e;
									}
									f.close();
								}
							}
						}
						while (FindNextFile(findhandle, &fd));
						FindClose(findhandle);
					}
					ofstream g((dir + "theme.ini").c_str());
					g << "[Themes]" << endl;
					// "1=INTRO" << endl;
					int j = 51;
					for (t_theme_list::const_iterator i = theme_list.begin(); i != theme_list.end(); i++)
						g << n(j++) << '=' << to_upper(i->first) << endl;
					g << endl;
					for (i = theme_list.begin(); i != theme_list.end(); i++)
					{
						const Ctheme_data& e = i->second;
						g << '[' << to_upper(i->first) << ']' << endl
							<< "Name=" << e.name() << endl;
						if (e.normal())
							g << "Length=" << e.length() << endl;
						if (!e.normal())
							g << "Normal=no" << endl;
						if (e.scenario())
							g << "Scenario=" <<  n(e.scenario()) << endl;
						if (!e.side().empty())
							g << "Side=" <<  e.side() << endl;
						if (e.repeat())
							g << "Repeat=yes" << endl;
						g << endl;
					}
					if (g.fail())
						MessageBox("Error writing theme.ini.", NULL, MB_ICONERROR);
					else
						MessageBox((n(theme_list.size()) + " themes have been written to theme.ini.").c_str());
				}
				theme.close();
			}
			local.close();
		}
		tibsun.close();
	}
}

void CMainFrame::OnUpdateLaunchXTW_TS(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!xcc_dirs::get_ts_dir().empty());	
}

void CMainFrame::launch_xtw(t_game game)
{
	Cmix_file ra2;
	if (!ra2.open(xcc_dirs::get_main_mix(game)))
	{
		Cmix_file local;
		if (!local.open(xcc_dirs::get_local_mix(game), ra2))
		{
			Ccc_file theme(true);
			string theme_ini_fname = game == game_ra2 ? "theme.ini" : "thememd.ini";
			if (!theme.open(theme_ini_fname, local))
			{
				Ctheme_ts_ini_reader ir;
				if (!ir.process(theme.get_data(), theme.get_size()))
				{
					t_theme_list theme_list = ir.get_theme_list();
					string dir = xcc_dirs::get_ra2_dir();
					WIN32_FIND_DATA fd;
					HANDLE findhandle = FindFirstFile((dir + "*.wav").c_str(), &fd);
					if (findhandle != INVALID_HANDLE_VALUE)
					{
						CXSTE xste;
						bool xste_open = !xste.open(game);
						do
						{
							if (~fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
							{
								const string fname = dir + fd.cFileName;
								Cwav_file f;
								if (!f.open(fname))
								{
									if (!f.process())
									{
										char b[MAX_PATH];
										int error = GetShortPathName(fname.c_str(), b, MAX_PATH);
										if (error > 0 && error < MAX_PATH)
										{
											Ctheme_data e;
											e.name("THEME:" + Cfname(b).get_ftitle());
											e.sound(Cfname(b).get_ftitle());
											theme_list[to_upper(Cfname(b).get_ftitle())] = e;
											if (xste_open)
												xste.csf_f().set_value(e.name(), Ccsf_file::convert2wstring(Cfname(fname).get_ftitle()), "");

										}
									}
									f.close();
								}
							}
						}
						while (FindNextFile(findhandle, &fd));
						if (xste_open)
						{
							xste.write();
							xste.close();
						}
						FindClose(findhandle);
					}
					ofstream g((dir + theme_ini_fname).c_str());
					g << "[Themes]" << endl;
					int j = 51;
					for (t_theme_list::const_iterator i = theme_list.begin(); i != theme_list.end(); i++)
						g << n(j++) << '=' << to_upper(i->first) << endl;
					g << endl;
					for (i = theme_list.begin(); i != theme_list.end(); i++)
					{
						const Ctheme_data& e = i->second;
						g << '[' << to_upper(i->first) << ']' << endl;
						if (!e.name().empty())
							g << "Name=" << e.name() << endl;
						if (!e.normal())
							g << "Normal=no" << endl;
						if (e.repeat())
							g << "Repeat=yes" << endl;
						if (!e.sound().empty())
							g << "Sound=" << e.sound() << endl;
						g << endl;
					}
					if (g.fail())
						MessageBox(("Error writing " + theme_ini_fname + ".").c_str(), NULL, MB_ICONERROR);
					else
						MessageBox((n(theme_list.size()) + " themes have been written to " + theme_ini_fname + ".").c_str());
				}
				theme.close();
			}
			local.close();
		}
		ra2.close();
	}
}

void CMainFrame::OnLaunchXTW_RA2() 
{
	launch_xtw(game_ra2);
}

void CMainFrame::OnUpdateLaunchXTW_RA2(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!xcc_dirs::get_ra2_dir().empty());	
}

void CMainFrame::OnLaunchXTW_RA2_YR() 
{
	launch_xtw(game_ra2_yr);
}

void CMainFrame::OnUpdateLaunchXTW_RA2_YR(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(Cfname(xcc_dirs::get_language_mix(game_ra2_yr)).exists());
}

CXCCMixerView* CMainFrame::left_mix_pane()
{
	return m_left_mix_pane;
}

CXCCMixerView* CMainFrame::right_mix_pane()
{
	return m_right_mix_pane;
}

CXCCFileView* CMainFrame::file_info_pane()
{
	return m_file_info_pane;
}

BOOL CMainFrame::OnIdle(LONG lCount)
{
	initialize_lists();
	if (m_left_mix_pane->OnIdle(lCount) 
		|| m_right_mix_pane->OnIdle(lCount) 
		|| m_file_info_pane->OnIdle(lCount))
		return true;
	return false;
}

void CMainFrame::OnViewReport() 
{
	string page;
	CString version;
	if (version.LoadString(IDR_MAINFRAME))
		page += tr(th(static_cast<string>(version.Left(version.Find('\n'))), "colspan=2"));
	page += tr(td("Left pane") + td(m_left_mix_pane->get_dir()))
		+ tr(td("Right pane") + td(m_right_mix_pane->get_dir()))
		+ tr(td("Combine shadows") + td(btoa(m_combine_shadows)))
		+ tr(td("Split shadows") + td(btoa(m_split_shadows)))
		+ tr(td("RA dir") + td(xcc_dirs::get_ra_dir()))
		+ tr(td("TS dir") + td(xcc_dirs::get_ts_dir()))
		+ tr(td("RA2 dir") + td(xcc_dirs::get_ra2_dir()))
		+ tr(td("Data dir") + td(xcc_dirs::get_data_dir()))
		+ tr(td("EXE dir") + td(GetModuleFileName().get_path()));
		// + tr(td() + td())
	string fname = get_temp_path() + "XCC Mixer Report.html";
	ofstream(fname.c_str()) << head_xcc() + body(table(tr(td(table(page, "border=1 width=100%"), "colspan=2")) + tr(td(m_left_mix_pane->report(), "valign=top") + td(m_right_mix_pane->report(), "valign=top")), "border=0 width=100%"));
	ShellExecute(m_hWnd, "open", fname.c_str(), NULL, NULL, SW_SHOW);
}

void CMainFrame::OnUpdateViewReport(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!OnIdle(0));
}

void CMainFrame::OnViewPaletSelect() 
{
	int old_palet = m_palet_i;
	CSelectPaletDlg dlg;
	if (m_palet_i != -1)
		dlg.current_palet(m_palet_i);
	dlg.set(this, m_pal_map_list, m_pal_list);
	if (IDOK == dlg.DoModal())
		assert(m_palet_i == dlg.current_palet());
	else
		set_palet(old_palet);
}


void CMainFrame::set_palet(int id)
{
	if (m_palet_i == id)
		return;
	m_palet_i = id;
	m_file_info_pane->Invalidate();
}

void CMainFrame::OnViewPaletAutoSelect() 
{
	m_file_info_pane->auto_select();
}

void CMainFrame::OnUpdateViewPaletAutoSelect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_file_info_pane->can_auto_select());
}