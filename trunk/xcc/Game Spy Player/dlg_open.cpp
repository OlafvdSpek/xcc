#include "stdafx.h"
#include "dlg_open.h"

#include "wol/ra2_names.h"
#include "../game spy/game_state.h"
#include "string_conversion.h"
#include <virtual_binary.h>
#include "xcc_dirs.h"

int get_replays_dir(string& v)
{
	char d[MAX_PATH];
	if (!SHGetSpecialFolderPath(NULL, d, CSIDL_PERSONAL, true))
		return 1;
	v = d;
	v += "/XGS/";
	return 0;
}

Cdlg_open::Cdlg_open(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(Cdlg_open::IDD, pParent, "Open_dlg")
{
	//{{AFX_DATA_INIT(Cdlg_open)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Cdlg_open::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdlg_open)
	DDX_Control(pDX, IDC_PLAYERS, m_players);
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
	ON_NOTIFY(LVN_GETDISPINFO, IDC_PLAYERS, OnGetdispinfoPlayers)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PLAYERS, OnItemchangedPlayers)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_PLAYERS, OnColumnclickPlayers)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL Cdlg_open::OnInitDialog()
{
	ETSLayoutDialog::OnInitDialog();

	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL, GREEDY)
			<< item(IDC_PLAYERS, GREEDY)
			<< item(IDC_REPLAYS, GREEDY)
			)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< itemGrowing(HORIZONTAL)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			);
	UpdateLayout();

	insert_players_columns();
	insert_replays_columns();
	string dir;
	get_replays_dir(dir);
	WIN32_FIND_DATA fd;
	HANDLE fh = FindFirstFile((dir + "*.x*").c_str(), &fd);
	if (fh != INVALID_HANDLE_VALUE)
	{
		CWaitCursor wc;
		set<string> old_players;
		do
		{
			if (~fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				t_map::iterator i;
				for (i = m_map.begin(); i != m_map.end(); i++)
				{
					t_map_entry& e = i->second;
					if (e.name != fd.cFileName)
						continue;
					e.size = fd.nFileSizeLow;
					m_replays.SetItemData(m_replays.InsertItem(m_replays.GetItemCount(), LPSTR_TEXTCALLBACK), i->first);
					insert_players(e.players, i->first);
					break;
				}
				if (i == m_map.end())
				{
					t_map_entry& e = m_map[m_map.empty() ? 0 : m_map.rbegin()->first + 1];
					e.dir = dir;
					e.name = fd.cFileName;
					e.gid = atoi(fd.cFileName + 12);
					e.size = fd.nFileSizeLow;
					Cxif_key_r key;
					if (!key.import(Cvirtual_binary(e.dir + e.name)) && key.keys().size() >= 2)
					{
						Cgame_state game_state;
						game_state.import_diff(boost::next(key.keys().begin())->second);
						e.scenario = game_state.scenario;
						for (auto& p : game_state.players)
						{
							const Cplayer& player = p.second;
							if (player.color != 5)
								e.players.insert(player.name);
						}
					}
					m_replays.SetItemData(m_replays.InsertItem(m_replays.GetItemCount(), LPSTR_TEXTCALLBACK), m_map.rbegin()->first);
					insert_players(e.players, m_map.rbegin()->first);
				}
			}
		}
		while (FindNextFile(fh, &fd));
		FindClose(fh);
	}
	for (auto& i : m_reverse_player_map)
		m_players.SetItemData(m_players.InsertItem(m_players.GetItemCount(), LPSTR_TEXTCALLBACK), i.second);
	m_players.auto_size();
	m_replays.auto_size();
	sort_replays(0, false);
	if (m_replays.GetItemCount())
		m_replays.SetItemState(0, LVNI_FOCUSED | LVNI_SELECTED, LVNI_FOCUSED | LVNI_SELECTED);
	return true;
}

void Cdlg_open::OnGetdispinfoReplays(NMHDR* pNMHDR, LRESULT* pResult)
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	string& buffer = m_replays.get_buffer();
	int id = pDispInfo->item.lParam;
	const t_map_entry& e = find_ref(m_map, id);
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		buffer = n(e.gid);
		break;
	case 1:
		buffer = n(e.size);
		break;
	case 2:
		{
			buffer.erase();
			for (auto& i : e.players)
			{
				if (!buffer.empty())
					buffer += ", ";
				buffer += i;
			}
		}
		break;
	case 3:
		buffer = get_map_name(e.scenario);
		break;
	}
	pDispInfo->item.pszText = const_cast<char*>(buffer.c_str());
	*pResult = 0;
}

void Cdlg_open::OnGetdispinfoPlayers(NMHDR* pNMHDR, LRESULT* pResult)
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	string& buffer = m_players.get_buffer();
	const t_player_map_entry& e = find_ref(m_player_map, pDispInfo->item.lParam);
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		buffer = e.player;
		break;
	case 1:
		buffer = n(e.replays.size());
		break;
	}
	pDispInfo->item.pszText = const_cast<char*>(buffer.c_str());
	*pResult = 0;
}

void Cdlg_open::OnItemchangedReplays(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->uNewState & LVIS_FOCUSED)
	{
		const t_map_entry& e = find_ref(m_map, pNMListView->lParam);
		m_fname = e.dir + e.name;
		m_ok.EnableWindow(true);
	}
	else
		m_ok.EnableWindow(false);
	*pResult = 0;
}

void Cdlg_open::OnItemchangedPlayers(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->uNewState & LVIS_FOCUSED)
	{
		m_replays.DeleteAllItems();
		const t_player_map_entry& e = find_ref(m_player_map, pNMListView->lParam);
		for (auto& i : e.replays)
			m_replays.SetItemData(m_replays.InsertItem(m_replays.GetItemCount(), LPSTR_TEXTCALLBACK), i);
	}
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
	string dir;
	get_replays_dir(dir);
	for (auto& i : key.m_keys)
	{
		t_map_entry& e = m_map[m_map.empty() ? 0 : m_map.rbegin()->first + 1];
		const Cxif_key& k = i.second;
		e.dir = dir;
		e.name = k.get_value_string(vi_name);
		e.gid = k.get_value_int(vi_gid);
		e.scenario = k.get_value_string(vi_scenario);
		{
			const Cxif_key& l = k.open_key_read(ki_players);
			for (auto& i : l.m_keys)
				e.players.insert(i.second.get_value_string(vi_name));
		}
	}
}

Cxif_key Cdlg_open::export_cache()
{
	Cxif_key key;
	for (auto& i : m_map)
	{
		const t_map_entry& e = i.second;
		Cxif_key& k = key.open_key_write();
		k.set_value_string(vi_name, e.name);
		k.set_value_int(vi_gid, e.gid);
		k.set_value_string(vi_scenario, e.scenario);
		{
			Cxif_key& l = k.open_key_write(ki_players);
			for (auto& i : e.players)
				l.open_key_write().set_value_string(vi_name, i);
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

void Cdlg_open::OnColumnclickPlayers(NMHDR* pNMHDR, LRESULT* pResult)
{
	sort_players(reinterpret_cast<NM_LISTVIEW*>(pNMHDR)->iSubItem);
	*pResult = 0;
}

template<class T>
int compare(T a, T b)
{
	return a < b ? -1 : a != b;
}

int Cdlg_open::replay_compare(int id_a, int id_b)
{
	if (m_sort_reverse)
		swap(id_a, id_b);
	const t_map_entry& a = find_ref(m_map, id_a);
	const t_map_entry& b = find_ref(m_map, id_b);
	switch (m_sort_column)
	{
	case 0:
		return ::compare(b.gid, a.gid);
	case 1:
		return ::compare(b.size, a.size);
	case 2:
		return ::compare(a.players, b.players);
	case 3:
		return ::compare(get_map_name(a.scenario), get_map_name(b.scenario));
	}
	return 0;
}

int Cdlg_open::player_compare(int id_a, int id_b)
{
	const t_player_map_entry& a = find_ref(m_player_map, id_a);
	const t_player_map_entry& b = find_ref(m_player_map, id_b);
	switch (m_players_sort_column)
	{
	case 0:
		return ::compare(a.player, b.player);
	case 1:
		return ::compare(b.replays.size(), a.replays.size());
	}
	return 0;
}

static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return reinterpret_cast<Cdlg_open*>(lParamSort)->replay_compare(lParam1, lParam2);
}

static int CALLBACK PlayerCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return reinterpret_cast<Cdlg_open*>(lParamSort)->player_compare(lParam1, lParam2);
}

void Cdlg_open::sort_replays(int i, bool reverse)
{
	m_sort_column = i;
	m_sort_reverse = reverse;
	m_replays.SortItems(Compare, reinterpret_cast<dword>(this));
}

void Cdlg_open::sort_players(int i)
{
	m_players_sort_column = i;
	m_players.SortItems(PlayerCompare, reinterpret_cast<dword>(this));
}

void Cdlg_open::insert_players(const t_player_set& players, int replay)
{
	for (auto& i : players)
		insert_player(i, replay);
}

void Cdlg_open::insert_player(const string& player, int replay)
{
	if (auto p = find_ptr(m_reverse_player_map, player))
		m_player_map[*p].replays.insert(replay);
	else
	{
		int i = m_reverse_player_map[player] = m_player_map.size();
		m_player_map[i].player = player;
		m_player_map[i].replays.insert(replay);
	}
}

void Cdlg_open::insert_players_columns()
{
	const char* column_label[] = {"Player", "Replays", "", NULL};
	for (int i = 0; column_label[i]; i++)
		m_players.InsertColumn(i, column_label[i], LVCFMT_RIGHT, -1, i);
}

void Cdlg_open::insert_replays_columns()
{
	const char* column_label[] = {"GID", "Size", "Players", "Scenario", NULL};
	const int column_alignment[] = {LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_LEFT, LVCFMT_LEFT};
	for (int i = 0; column_label[i]; i++)
		m_replays.InsertColumn(i, column_label[i], column_alignment[i], -1, i);
}