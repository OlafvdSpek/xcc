// dlg_ccr.cpp : implementation file
//

#include "stdafx.h"
#include "XCC Cheat Reporter.h"
#include "dlg_ccr.h"

#include <fstream>
#include <windows.h>
#include "cgi.h"
#include "file32.h"
#include "html.h"
#include "string_conversion.h"
#include "virtual_image.h"
#include "web_tools.h"
#include "xcc_dirs.h"
#include "xif_key.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cdlg_ccr dialog


Cdlg_ccr::Cdlg_ccr(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(Cdlg_ccr::IDD, pParent, "XCR_CCR_dlg")
{
	//{{AFX_DATA_INIT(Cdlg_ccr)
	m_stats = _T("");
	m_description = _T("");
	m_connection_speed = FALSE;
	m_disconnect = FALSE;
	m_game_speed = FALSE;
	m_map_revealer = FALSE;
	m_mod_map = FALSE;
	m_reconnection_error = FALSE;
	m_build_anywhere = FALSE;
	m_money = FALSE;
	m_tech = FALSE;
	m_mail = _T("Mail");
	m_name = _T("Name");
	m_game_id = 0;
	//}}AFX_DATA_INIT
	m_buffer_w = 0;
	m_reg_key = "XCR_CCR_dlg";
}


void Cdlg_ccr::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdlg_ccr)
	DDX_Control(pDX, IDC_NICKNAME, m_nickname);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Text(pDX, IDC_STATS, m_stats);
	DDX_Text(pDX, IDC_DESCRIPTION, m_description);
	DDX_Check(pDX, IDC_CONNECTION_SPEED, m_connection_speed);
	DDX_Check(pDX, IDC_DISCONNECT, m_disconnect);
	DDX_Check(pDX, IDC_GAME_SPEED, m_game_speed);
	DDX_Check(pDX, IDC_MAP_REVEALER, m_map_revealer);
	DDX_Check(pDX, IDC_MOD_MAP, m_mod_map);
	DDX_Check(pDX, IDC_RECONNECTION_ERROR, m_reconnection_error);
	DDX_Check(pDX, IDC_BUILD_ANYWHERE, m_build_anywhere);
	DDX_Check(pDX, IDC_MONEY, m_money);
	DDX_Check(pDX, IDC_TECH, m_tech);
	DDX_Text(pDX, IDC_MAIL, m_mail);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_GAME_ID, m_game_id);
	DDV_MinMaxInt(pDX, m_game_id, 1, 100000000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cdlg_ccr, ETSLayoutDialog)
	//{{AFX_MSG_MAP(Cdlg_ccr)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST, OnGetdispinfoList)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST, OnColumnclickList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cdlg_ccr message handlers

void Cdlg_ccr::game(t_game game)
{
	m_game = game;
}

static int c_colums = 2;

BOOL Cdlg_ccr::OnInitDialog() 
{
	m_name = AfxGetApp()->GetProfileString(m_reg_key, "name", "Name");
	m_mail = AfxGetApp()->GetProfileString(m_reg_key, "mail", "Mail");

	CreateRoot(HORIZONTAL)
		<< (pane(VERTICAL, GREEDY)
			<< (pane(HORIZONTAL, GREEDY)
				<< item(IDC_NAME, ABSOLUTE_VERT)
				<< item(IDC_NICKNAME, ABSOLUTE_VERT)
				)
			<< (pane(HORIZONTAL, GREEDY)
				<< item(IDC_MAIL, ABSOLUTE_VERT)
				<< item(IDC_GAME_ID, ABSOLUTE_VERT)
				)
			<< item(IDC_STATS, GREEDY)
			<< item(IDC_DESCRIPTION, GREEDY)
			<< item(IDC_LIST, GREEDY)
			)
		<< (pane(VERTICAL, ABSOLUTE_HORZ)		
			<< item(IDC_DISCONNECT, NORESIZE)
			<< item(IDC_RECONNECTION_ERROR, NORESIZE)
			<< item(IDC_GAME_SPEED, NORESIZE)
			<< item(IDC_CONNECTION_SPEED, NORESIZE)
			<< item(IDC_MAP_REVEALER, NORESIZE)
			<< item(IDC_MOD_MAP, NORESIZE)
			<< item(IDC_BUILD_ANYWHERE, NORESIZE)
			<< item(IDC_MONEY, NORESIZE)
			<< item(IDC_TECH, NORESIZE)
			// << item(, NORESIZE)
			<< itemGrowing(VERTICAL)
			<< (pane(HORIZONTAL, ABSOLUTE_VERT)		
				<< item(IDOK, NORESIZE)
				<< item(IDCANCEL, NORESIZE)
				)
			);
	UpdateLayout();

	ETSLayoutDialog::OnInitDialog();

	const char* column_label[] = {"Name", "Size", "Date"};
	const int column_alignment[] = {LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_LEFT};

	ListView_SetExtendedListViewStyle(m_list.m_hWnd, ListView_GetExtendedListViewStyle(m_list.m_hWnd) | LVS_EX_FULLROWSELECT);
	for (int i = 0; i < c_colums; i++)
		m_list.InsertColumn(i, column_label[i], column_alignment[i], -1, i);

	load_nicknames();
	load_screenshots();
	autosize_colums();
		
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);
		m_tooltip.AddTool(GetDlgItem(IDC_NAME), "Name");
		m_tooltip.AddTool(GetDlgItem(IDC_NICKNAME), "Nickname");
		m_tooltip.AddTool(GetDlgItem(IDC_MAIL), "Mail");
		m_tooltip.AddTool(GetDlgItem(IDC_GAME_ID), "Game ID");
		m_tooltip.AddTool(GetDlgItem(IDC_STATS), "Statistics");
		m_tooltip.AddTool(GetDlgItem(IDC_DESCRIPTION), "Description");
		m_tooltip.AddTool(GetDlgItem(IDC_LIST), "Screenshots");
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Cdlg_ccr::load_nicknames()
{
	HKEY key;
	for (int i = 1; i < 11; i++)
	{
		if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CLASSES_ROOT, ("Wchat\\Nick" + n(i) + "\\Nick").c_str(), 0, KEY_READ, &key))
		{
			char b[16];
			DWORD cb_b = 16;
			if (ERROR_SUCCESS == RegQueryValueEx(key, NULL, NULL, NULL, reinterpret_cast<byte*>(b), &cb_b))
			{
				m_nickname.AddString(b);
				m_nickname.SelectString(-1, b);
			}
			RegCloseKey(key);
		}
	}
	m_nickname.DeleteString(0);
}

int Cdlg_ccr::load_stats()
{
	m_stats.Empty();
	ifstream f((xcc_dirs::get_dir(m_game) + "mpstats.txt").c_str());
	string s;
	while (getline(f, s))
	{
		m_stats += (s + "\r\n").c_str();
	}
	return !f.eof() && f.fail();
}

int Cdlg_ccr::get_free_id() const
{
	return m_map.empty() ? 0 : m_map.rbegin()->first + 1;
}

int Cdlg_ccr::load_screenshots()
{
	string dir = xcc_dirs::get_dir(m_game);
	WIN32_FIND_DATA fd;
	HANDLE findhandle = FindFirstFile((dir + "*.pcx").c_str(), &fd);
	if (findhandle != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (~fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				const string fname = dir + fd.cFileName;
				Cfile32 f;
				if (!f.open_read(fname))
				{
					int id = get_free_id();
					t_map_entry& e = m_map[id];
					e.fname = to_lower(dir + fd.cFileName);
					e.size = f.get_size();;
					m_list.SetItemData(m_list.InsertItem(m_list.GetItemCount(), LPSTR_TEXTCALLBACK), id);
					f.close();
				}
			}
		}
		while (FindNextFile(findhandle, &fd));
		FindClose(findhandle);
	}
	sort_list(0, false);
	return 0;
}

void Cdlg_ccr::autosize_colums()
{
	SetRedraw(false);
	for (int i = 0; i < c_colums; i++)
		m_list.SetColumnWidth(i, LVSCW_AUTOSIZE);
	if (0)
	{
		m_list.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
		int cx = m_list.GetColumnWidth(i);
		m_list.SetColumnWidth(i, LVSCW_AUTOSIZE);
		if (m_list.GetColumnWidth(i) < cx)
			m_list.SetColumnWidth(i, cx);
	}
	SetRedraw(true);
	Invalidate();
}

void Cdlg_ccr::OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	int id = pDispInfo->item.lParam;
	const t_map_entry& e = m_map.find(id)->second;
	m_buffer[m_buffer_w].erase();
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		m_buffer[m_buffer_w] = e.fname;
		break;
	case 1:
		if (e.size != -1)
			m_buffer[m_buffer_w] = n(e.size);
		break;
	}
	pDispInfo->item.pszText = const_cast<char*>(m_buffer[m_buffer_w].c_str());
	m_buffer_w--;
	if (m_buffer_w < 0)
		m_buffer_w += 4;
	*pResult = 0;
}

void Cdlg_ccr::OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int column = pNMListView->iSubItem;
	sort_list(column, column == m_sort_column ? !m_sort_reverse : false);
	*pResult = 0;
}

static int compare_int(unsigned int a, unsigned int b)
{
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}

static int compare_string(string a, string b)
{
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}

int Cdlg_ccr::compare(int id_a, int id_b) const
{
	if (m_sort_reverse)
		swap(id_a, id_b);
	const t_map_entry& a = m_map.find(id_a)->second;
	const t_map_entry& b = m_map.find(id_b)->second;
	switch (m_sort_column)
	{
	case 0:
		return compare_string(a.fname, b.fname);
	case 1:
		return compare_int(a.size, b.size);
	default:
		return 0;
	}
}

static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return reinterpret_cast<Cdlg_ccr*>(lParamSort)->compare(lParam1, lParam2);
}

void Cdlg_ccr::sort_list(int i, bool reverse)
{
	m_sort_column = i;
	m_sort_reverse = reverse;
	m_list.SortItems(Compare, reinterpret_cast<dword>(this));
}

enum
{
	vi_game,
	vi_stats,
	vi_sync,
	vi_description,
	ki_screenshots,
	vi_disconnect,
	vi_reconnection_error,
	vi_game_speed,
	vi_connection_speed,
	vi_map_revealer,
	vi_mod_map,
	vi_build_anywhere,
	vi_money,
	vi_tech,
	vi_name,
	vi_mail,
	vi_nickname
};

void Cdlg_ccr::OnOK() 
{
	if (UpdateData(true))
	{
		const char* save_filter = "XCRF files (*.xcrf)|*.xcrf|";
		
		CWaitCursor wait;
		CFileDialog dlg(false, ".xcrf", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, save_filter, NULL);
		if (IDOK == dlg.DoModal())
		{
			AfxGetApp()->WriteProfileString(m_reg_key, "name", m_name);
			AfxGetApp()->WriteProfileString(m_reg_key, "mail", m_mail);
			Cxif_key key;
			key.set_value_int(vi_game, m_game);
			key.set_value_string(vi_stats, static_cast<string>(m_stats));
			// key.set_value_string(vi_sync, static_cast<string>(""));
			key.set_value_string(vi_description, static_cast<string>(m_description));
			if (m_disconnect)
				key.set_value_int(vi_disconnect, true);
			key.set_value_int(vi_reconnection_error, m_reconnection_error);
			key.set_value_int(vi_game_speed, m_game_speed);
			key.set_value_int(vi_connection_speed, m_connection_speed);
			key.set_value_int(vi_map_revealer, m_map_revealer);
			key.set_value_int(vi_mod_map, m_mod_map);
			key.set_value_int(vi_build_anywhere, m_build_anywhere);
			key.set_value_int(vi_money, m_money);
			key.set_value_int(vi_tech, m_tech);
			key.set_value_string(vi_name, static_cast<string>(m_name));
			CString nickname;
			m_nickname.GetLBText(m_nickname.GetCurSel(), nickname);
			key.set_value_string(vi_nickname, static_cast<string>(nickname));
			key.set_value_string(vi_mail, static_cast<string>(m_mail));
			Cxif_key& screenshots_key = key.open_key_write(ki_screenshots);
			int index = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
			while (index != -1)
			{
				int id = m_list.GetItemData(index);
				const t_map_entry& e = m_map.find(id)->second;
				Cvirtual_image image;
				if (!image.load(e.fname))
				{
					string temp_fname = get_temp_fname();
					if (!image.save_as_jpeg(temp_fname))
					{
						Cvirtual_binary s;
						if (!s.import(temp_fname))
							screenshots_key.set_value_binary(index, s.data(), s.size());
						delete_file(temp_fname);
					}
				}
				index = m_list.GetNextItem(index, LVNI_ALL | LVNI_SELECTED);
			}
			key.vdata().export(static_cast<string>(dlg.GetPathName()));
			ETSLayoutDialog::OnOK();
		}
	}
}

static Chtml report_cheats(const Cxif_key& key)
{
	Chtml page;
	int index = 0;
	for (t_xif_value_map::const_iterator i = key.m_values.begin(); i != key.m_values.end(); i++)
	{
		switch (i->first)
		{
		case vi_disconnect:
			if (i->second.get_int())
				page += "Disconnect<br>";
			break;
		case vi_reconnection_error: 
			if (i->second.get_int())
				page += "Reconnection error<br>";
			break;
		case vi_game_speed: 
			if (i->second.get_int())
				page += "Game speed<br>";
			break;
		case vi_connection_speed: 
			if (i->second.get_int())
				page += "Connection speed<br>";
			break;
		case vi_map_revealer: 
			if (i->second.get_int())
				page += "Map revealer<br>";
			break;
		case vi_mod_map: 
			if (i->second.get_int())
				page += "Mod map<br>";
			break;
		case vi_build_anywhere: 
			if (i->second.get_int())
				page += "Build anywhere<br>";
			break;
		case vi_money: 
			if (i->second.get_int())
				page += "Money<br>";
			break;
		case vi_tech: 
			if (i->second.get_int())
				page += "Tech<br>";
			break;
			/*
		case vi_@: 
			if (i->second.get_int())
				page += "@<br>";
			break;
			*/
		}
	}
	return page;
}

static Chtml report_screenshots(const Cxif_key& key, string path)
{
	Chtml page;
	int index = 0;
	for (t_xif_value_map::const_iterator i = key.m_values.begin(); i != key.m_values.end(); i++)
	{
		Cfname fname = path + "scrn" + nwzl(4, index++) + ".jpeg";		
		if (!i->second.get_vdata().export(fname))
			page += "<p><img src=" + fname.get_fname() + ">";
	}
	return page;
}

int xcrf_decode(Cvirtual_binary s, string fname)
{
	Cxif_key key;
	int error = key.load_key(s.data(), s.size());
	if (!error)
	{
		Chtml page;
		page += tr(td("Name") + td(web_name(key.get_value_string(vi_name), key.get_value_string(vi_mail))));
		page += tr(td("Nickname") + td(web_encode(key.get_value_string(vi_nickname))));
		page += tr(td("Game") + td(game_name[key.get_value_int(vi_game)]));
		page += tr(td("Stats") + td(web_encode(key.get_value_string(vi_stats))));
		if (key.exists_value(vi_sync))
			page += tr(td("Sync") + td(web_encode(key.get_value_string(vi_sync))));
		page += tr(td("Description") + td(web_encode(key.get_value_string(vi_description))));
		page += tr(td("Cheats") + td(report_cheats(key)));
		// page += tr(td("Screenshots") + td());
		ofstream((fname + "index.html").c_str()) << html(head("<link rel=stylesheet href=http://xcc.tiberian.com/xcc.css>") + body(table(page, "border=1") + report_screenshots(key.open_key_read(ki_screenshots), fname)));
	}
	return error;
}

BOOL Cdlg_ccr::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);
	return ETSLayoutDialog::PreTranslateMessage(pMsg);
}
