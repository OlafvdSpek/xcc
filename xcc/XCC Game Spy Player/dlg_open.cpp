// dlg_open.cpp : implementation file
//

#include "stdafx.h"
#include "XCC Game Spy Player.h"
#include "dlg_open.h"

#include "wol/ra2_names.h"
#include "../xcc game spy/game_state.h"
#include "string_conversion.h"
#include "virtual_binary.h"
#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cdlg_open dialog


Cdlg_open::Cdlg_open(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(Cdlg_open::IDD, pParent, "Open_dlg")
{
	//{{AFX_DATA_INIT(Cdlg_open)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_buffer_w = 0;
}


void Cdlg_open::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdlg_open)
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_REPLAYS, m_replays);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cdlg_open, ETSLayoutDialog)
	//{{AFX_MSG_MAP(Cdlg_open)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_REPLAYS, OnGetdispinfoReplays)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_REPLAYS, OnItemchangedReplays)
	ON_NOTIFY(NM_DBLCLK, IDC_REPLAYS, OnDblclkReplays)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_REPLAYS, OnColumnclickReplays)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cdlg_open message handlers

static int c_colums = 4;

BOOL Cdlg_open::OnInitDialog() 
{
	ETSLayoutDialog::OnInitDialog();
	
	CreateRoot(VERTICAL)
		<< item(IDC_REPLAYS, GREEDY)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< itemGrowing(HORIZONTAL)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			);
	UpdateLayout();
	
	m_replays.SetExtendedStyle(m_replays.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	static char* column_label[] = {"GID", "Size", "Players", "Scenario"};
	static int column_alignment[] = {LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_LEFT, LVCFMT_LEFT};
	for (int i = 0; i < c_colums; i++)
		m_replays.InsertColumn(i, column_label[i], column_alignment[i], -1, i);
	string dir = xcc_dirs::get_dir(game_ra2) + "replays/";
	WIN32_FIND_DATA fd;
	HANDLE fh = FindFirstFile((dir + "game replay *.xif").c_str(), &fd);
	if (fh != INVALID_HANDLE_VALUE)
	{
		CWaitCursor wc;
		do
		{
			if (~fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				// && strlen(fd.cFileName) == 24)
			{
				for (t_map::iterator i = m_map.begin(); i != m_map.end(); i++)
				{
					t_map_entry& e = i->second;
					if (e.name == fd.cFileName)
					{
						e.size = fd.nFileSizeLow;
						m_replays.SetItemData(m_replays.InsertItem(m_replays.GetItemCount(), LPSTR_TEXTCALLBACK), i->first);
						break;
					}
				}
				if (i != m_map.end())
					continue;
				t_map_entry& e = m_map[m_map.empty() ? 0 : m_map.rbegin()->first + 1];
				e.dir = dir;
				e.name = fd.cFileName;
				e.gid = atoi(fd.cFileName + 12);
				e.size = fd.nFileSizeLow;
				{
					Cxif_key_r key;
					if (!key.import(Cvirtual_binary(e.dir + e.name)))
					{
						Cgame_state game_state;
						Cxif_key_r::t_key_map::const_iterator i = key.keys().begin();
						i++;
						game_state.import_diff(i->second);
						e.scenario = game_state.scenario;
						for (Cgame_state::t_players::const_iterator p = game_state.players.begin(); p != game_state.players.end(); p++)
						{
							const Cplayer& player = p->second;
							if (player.color != 5)
								e.players.insert(player.name);
						}
					}
				}
				m_replays.SetItemData(m_replays.InsertItem(m_replays.GetItemCount(), LPSTR_TEXTCALLBACK), m_map.rbegin()->first);
			}
		}
		while (FindNextFile(fh, &fd));
		FindClose(fh);
	}
	{
		for (int i = 0; i < c_colums; i++)
			m_replays.SetColumnWidth(i, LVSCW_AUTOSIZE);
	}
	sort_replays(0, true);
	if (m_replays.GetItemCount())
		m_replays.SetItemState(0, LVNI_FOCUSED | LVNI_SELECTED, LVNI_FOCUSED | LVNI_SELECTED);
	return true;
}

void Cdlg_open::OnGetdispinfoReplays(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	int id = pDispInfo->item.lParam;
	const t_map_entry& e = m_map.find(id)->second;
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		m_buffer[m_buffer_w] = n(e.gid);
		break;
	case 1:
		m_buffer[m_buffer_w] = n(e.size);
		break;
	case 2:
		{
			m_buffer[m_buffer_w].erase();
			for (t_player_set::const_iterator i = e.players.begin(); i != e.players.end(); i++)
			{
				if (!m_buffer[m_buffer_w].empty())
					m_buffer[m_buffer_w] += ", ";
				m_buffer[m_buffer_w] += *i;
			}
		}
		break;
	case 3:
		m_buffer[m_buffer_w] = get_map_name(e.scenario);
		break;
	}
	pDispInfo->item.pszText = const_cast<char*>(m_buffer[m_buffer_w].c_str());
	m_buffer_w--;
	if (m_buffer_w < 0)
		m_buffer_w += 4;
	*pResult = 0;
}

void Cdlg_open::OnItemchangedReplays(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int i = m_replays.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
	if (pNMListView->uNewState & LVIS_FOCUSED)
	{
		const t_map_entry& e = m_map.find(m_replays.GetItemData(i))->second;
		m_fname = e.dir + e.name;
	}
	m_ok.EnableWindow(i != -1);	
	*pResult = 0;
}

void Cdlg_open::OnDblclkReplays(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_replays.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED) != -1)
		EndDialog(IDOK);
	*pResult = 0;
}

string Cdlg_open::fname()
{
	return m_fname;
}

enum
{
	ki_players,
	vi_name,
	vi_gid,
	vi_scenario,
};

void Cdlg_open::import_cache(const Cxif_key& key)
{
	string dir = xcc_dirs::get_dir(game_ra2) + "replays/";
	for (t_xif_key_map::const_iterator i = key.m_keys.begin(); i != key.m_keys.end(); i++)
	{
		t_map_entry& e = m_map[m_map.empty() ? 0 : m_map.rbegin()->first + 1];
		const Cxif_key& k = i->second;
		e.dir = dir;
		e.name = k.get_value_string(vi_name);
		e.gid = k.get_value_int(vi_gid);
		e.scenario = k.get_value_string(vi_scenario);
		{
			const Cxif_key& l = k.open_key_read(ki_players);
			for (t_xif_key_map::const_iterator i = l.m_keys.begin(); i != l.m_keys.end(); i++)
				e.players.insert(i->second.get_value_string(vi_name));
		}
	}
}

Cxif_key Cdlg_open::export_cache()
{
	Cxif_key key;
	for (t_map::const_iterator i = m_map.begin(); i != m_map.end(); i++)
	{
		const t_map_entry& e = i->second;
		Cxif_key& k = key.open_key_write();
		k.set_value_string(vi_name, e.name);
		k.set_value_int(vi_gid, e.gid);
		k.set_value_string(vi_scenario, e.scenario);
		{
			Cxif_key& l = k.open_key_write(ki_players);
			for (t_player_set::const_iterator i = e.players.begin(); i != e.players.end(); i++)
				l.open_key_write().set_value_string(vi_name, *i);
		}
	}
	return key;
}

void Cdlg_open::OnColumnclickReplays(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int column = reinterpret_cast<NM_LISTVIEW*>(pNMHDR)->iSubItem;
	sort_replays(column, column == m_sort_column ? !m_sort_reverse : false);
	*pResult = 0;
}

template<class T>
int compare(T a, T b)
{
	return a < b ? -1 : a != b;
}

int Cdlg_open::compare(int id_a, int id_b)
{
	if (m_sort_reverse)
		swap(id_a, id_b);
	const t_map_entry& a = m_map.find(id_a)->second;
	const t_map_entry& b = m_map.find(id_b)->second;
	switch (m_sort_column)
	{
	case 0:
		return ::compare(a.gid, b.gid);
	case 1:
		return ::compare(a.size, b.size);
	case 2:
		return ::compare(a.players, b.players);
	case 3:
		return ::compare(get_map_name(a.scenario), get_map_name(b.scenario));
	}
	return 0;
}

static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return reinterpret_cast<Cdlg_open*>(lParamSort)->compare(lParam1, lParam2);
}

void Cdlg_open::sort_replays(int i, bool reverse)
{
	m_sort_column = i;
	m_sort_reverse = reverse;
	m_replays.SortItems(Compare, reinterpret_cast<dword>(this));
}