// dlg_ccr.cpp : implementation file
//

#include "stdafx.h"
#include "XCC Cheat Reporter.h"
#include "dlg_ccr.h"

#include <fstream>
#include <mapi.h>
#include <windows.h>
#include "cgi.h"
#include "database.h"
#include "file32.h"
#include "fname.h"
#include "html.h"
#include "multi_line.h"
#include "string_conversion.h"
#include "virtual_file.h"
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
	m_send_ws = TRUE;
	m_send_xhp = TRUE;
	//}}AFX_DATA_INIT
	m_buffer_w = 0;
	m_reg_key = "XCR_CCR_dlg";
}


void Cdlg_ccr::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdlg_ccr)
	DDX_Control(pDX, IDC_CHEATER, m_cheater);
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
	DDX_Check(pDX, IDC_SEND_WS, m_send_ws);
	DDX_Check(pDX, IDC_SEND_XHP, m_send_xhp);
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

static int c_colums = 3;

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
				<< itemGrowing(HORIZONTAL)
				<< item(IDC_CHEATER, ABSOLUTE_VERT)
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
			<< item(IDC_SEND_WS, NORESIZE)
			<< item(IDC_SEND_XHP, NORESIZE)
			// << item(, NORESIZE)
			<< itemGrowing(VERTICAL)
			<< (pane(HORIZONTAL, ABSOLUTE_VERT)
				<< item(IDOK, NORESIZE)
				<< item(IDCANCEL, NORESIZE)
				)
			);
	UpdateLayout();

	ETSLayoutDialog::OnInitDialog();

	const char* column_label[] = {"Name", "Size (JPEG)", "Size (PCX)"};
	const int column_alignment[] = {LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_RIGHT};

	ListView_SetExtendedListViewStyle(m_list.m_hWnd, ListView_GetExtendedListViewStyle(m_list.m_hWnd) | LVS_EX_FULLROWSELECT);
	for (int i = 0; i < c_colums; i++)
		m_list.InsertColumn(i, column_label[i], column_alignment[i], -1, i);

	
	{
		m_cheater.DeleteString(0);
		for (t_cheaters::const_iterator i = m_cheaters.begin(); i != m_cheaters.end(); i++)
			m_cheater.AddString(i->c_str());
		m_cheater.SetCurSel(0);
	}

	load_nicknames();
	load_screenshots();
	autosize_colums();

	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);
		m_tooltip.AddTool(GetDlgItem(IDC_NAME), "Name");
		m_tooltip.AddTool(GetDlgItem(IDC_NICKNAME), "Nickname");
		m_tooltip.AddTool(GetDlgItem(IDC_CHEATER), "Cheater");
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
	m_nickname.DeleteString(0);
	HKEY key;
	for (int i = 1; i < 11; i++)
	{
		if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CLASSES_ROOT, ("Wchat\\Nick" + n(i) + "\\Nick").c_str(), 0, KEY_READ, &key))
		{
			char b[16];
			DWORD cb_b = 16;
			if (ERROR_SUCCESS == RegQueryValueEx(key, NULL, NULL, NULL, reinterpret_cast<byte*>(b), &cb_b))
			{
				if (*b)
					m_nickname.AddString(b);
			}
			RegCloseKey(key);
		}
	}
	m_nickname.SetCurSel(0);
}

int Cdlg_ccr::load_stats()
{
	m_cheaters.clear();
	m_stats.Empty();
	ifstream f((xcc_dirs::get_dir(m_game) + "mpstats.txt").c_str());
	string s;
	while (getline(f, s))
	{
		Cmulti_line l = s;
		if (string_equal_i(l.get_next_line(':'), "Name"))
			m_cheaters.insert(l.get_next_line());
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
					Cvirtual_image image;
					Cvirtual_file g;
					e.jpeg_size = -1; // image.load(e.fname) || image.save_as_jpeg(g) ? -1 : g.size();
					e.pcx_size = f.get_size();
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
		if (e.jpeg_size != -1)
			m_buffer[m_buffer_w] = n(e.jpeg_size);
		break;
	case 2:
		if (e.pcx_size != -1)
			m_buffer[m_buffer_w] = n(e.pcx_size);
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
		return compare_int(a.jpeg_size, b.jpeg_size);
	case 2:
		return compare_int(a.pcx_size, b.pcx_size);
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
	vi_nickname,
	vi_game_id,
	vi_cheater
};

const char* html_cheat_report = 
	"<html>"
	"<BODY BGCOLOR=\"#000000\" TEXT=\"#FFFFFF\" LINK=\"#FFFF00\" ALINK=\"#66FF99\" VLINK=\"#999900\" leftmargin=\"0\" topmargin=\"0\" marginwidth=\"0\" marginheight=\"0\">"
	"<br>"
	""
	"<TABLE WIDTH=593 BORDER=0>"
	"  <TR><TD><FONT COLOR=\"000000\">...</FONT></TD>"
	"    <TD> <b><br>"
	"      <FONT SIZE=4> Thank you for submitting your cheater report</FONT></b> "
	"      <p><font face=\"Arial, Helvetica, sans-serif\" size=\"2\" color=\"#FFFFFF\"><b><i>Very "
	"        Important: You must fill out *ALL* the fields below in order for your "
	"        entry to be valid. Forms which are incomplete will be kicked out of our "
	"        system.</i></b></font> </p>"
	"      <FONT FACE=\"ARIAL\" color=\"AAAAFF\"><HR>"
	"      </font><form action=\"http://westwood.ea.com/cgi-bin/cheaterform/forminput.cgi\" method=\"post\">"
	"        <FONT COLOR=\"66FF66\"> "
	"        <input type=\"hidden\" name=\"_send_email1\" value=\"email.txt\">"
	"<!--    <input type=\"hidden\" name=\"_send_email2\" value=\"email2.txt\">           -->"
	"<!--    <input type=\"hidden\" name=\"_out_file\"    value=\"logfile.txt\">          -->"
	"        <input type=\"hidden\" name=\"_error_path\"  value=\"error.txt\">"
	"        <input type=\"hidden\" name=\"_browser_out\" value=\"output.txt\">"
	"	<input type=\"hidden\" name=\"e_email\" value=\"nobody@westwood.com\">"
	"        </font>"
	""
	""
	"  <table border=\"0\" cellpadding=\"5\" cellspacing=\"2\" width=\"551\">"
	"          <tr>"
	"            <td colspan=\"2\"><b><font size=\"4\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">ALL FIELDS ARE REQUIRED</font></b></td>"
	"          </tr>"
	"<tr>"
	"            <td width=\"50%%\"> "
	"              <p><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Game "
	"                Played </font></p>"
	"            </td>"
	"            <td width=\"50%%\"> "
	"              <select name=\"r_game\">"
	"                <option value=\"REDALERT2\">Command &amp; Conquer Red Alert 2</option>"
	"                <option value=\"TIBERIANSUN\">Command &amp; Conquer Tiberian Sun</option>"
	"              </select>"
	"            </td>"
	"          </tr>"
	"<tr>"
	"            <td width=\"50%%\"> "
	"              <p><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Your "
	"                Westwood Online Nickname</font></p>"
	"            </td>"
	"            <td width=\"50%%\"> "
	"              <input type=\"textbox\" length=10 maxlength=10 name=\"r_player1nick\" value=\"%s\">"
	"            </td>"
	"          </tr>"
	"<tr>"
	"            <td width=\"50%%\"> "
	"              <p><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Your "
	"                Opponent's Nickname</font></p>"
	"            </td>"
	"            <td width=\"50%%\"> "
	"              <input type=\"textbox\" length=10 maxlength=10 name=\"r_player2nick\" value=\"%s\">"
	"            </td>"
	"          </tr>"
	"          <tr> "
	"            <td width=\"50%%\"> "
	"              <p><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Your "
	"                Email Address</font></p>"
	"            </td>"
	"            <td width=\"50%%\"> "
	"              <input type=\"textbox\" length=10 maxlength=35 name=\"re_email\" value=\"%s\">"
	"            </td>"
	"          </tr>"
	"          <tr> "
	"            <td width=\"50%%\" height=\"30\"> "
	"              <p><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Type "
	"                of Game Played</font></p>"
	"            </td>"
	"            <td width=\"50%%\" height=\"30\"> "
	"              <select name=\"r_gametype\">"
	"                <option value=\"TOURNAMENT\">Tournament Game</option>"
	"                <option value=\"CLAN\">CLAN Ranked Game</option>"
	"                <option value=\"NON-TOURNAMENT\">Non-Tournament Game</option>"
	"              </select>"
	"            </td>"
	"          </tr>"
	"          <tr> "
	"            <td width=\"50%%\"> "
	"              <p><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Game "
	"                Number and/or date and time of game played.</font></p>"
	"            </td>"
	"            <td width=\"50%%\"> "
	"              <input type=\"textbox\" length=10 maxlength=20 name=\"r_datetimenum\" value=\"%d\">"
	"            </td>"
	"          </tr>"
	"          <tr> "
	"            <td width=\"50%%\"> "
	"              <p><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Please "
	"                describe how you feel this person played unfairly. List any details "
	"                about the game you think would be useful to us (for example, the "
	"                map used, the type of game played, etc.)</font></p>"
	"            </td>"
	"            <td width=\"50%%\"> "
	"              <textarea name=\"r_probdescription\" cols=\"30\" rows=\"6\">%s</textarea>"
	"            </td>"
	"          </tr>"
	"        </table>"
	"        <br>"
	"        <hr width=\"50%%\">"
	"        <input type=hidden name=\"redirect\" value=\"/westwoodonline/fansiteform/thanks.html\">"
	"          <p></p><CENTER>"
	"        <p align=\"center\"><font face=\"ARIAL\" color=\"AAAAFF\">"
	"            <input type=\"submit\" value=\"SUBMIT MY REPORT\" name=\"submit\">"
	"          </font></p></CENTER>"
	"        <FONT FACE=\"ARIAL\" color=\"AAAAFF\"> "
	"        <table width=\"500\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\">"
	"          <tr> "
	"            <td width=\"64\" height=\"40\">&nbsp; </td>"
	"            <td width=\"354\" height=\"40\"> "
	"              <div align=\"center\"><font face=\"ARIAL\" color=\"66FF66\" size=\"2\">Westwood "
	"                Studios respects your privacy. For more information, <a href=\"http://www.ea.com/privacy.html\" target=\"_blank\">please "
	"                read our privacy policy statement.</a></font></div>"
	"            </td>"
	"            <td width=\"72\" height=\"40\"><font face=\"ARIAL\" color=\"66FF66\"><img src=\"../../assets/esrb_rating_icons/PrivacyCertified_sm.gif\" align=\"right\" width=\"64\" height=\"45\"></font></td>"
	"          </tr>"
	"        </table>"
	"        <p align=\"center\"><a href=\"http://www.ea.com/global/legal/legalnotice.jsp\" target=\"_blank\"><img src=\"../../assets/copyright_logos/copyright-white.gif\" width=\"265\" height=\"40\" border=\"0\"></a></p>"
	"        </font> "
	"      </form>"
	"      </td>"
	"			</tr>"
	"		</table>"
	"		"
	"</body>"
	"</html>";

void Cdlg_ccr::OnOK()
{
	if (UpdateData(true))
	{
		if (m_list.GetSelectedCount() < 2 && MessageBox("You've selected less then two screenshots. Multiple screenshots can be selected by using control. Would you like to select more screenshots?", NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
			return;

		const char* save_filter = "XCRF files (*.xcrf)|*.xcrf|";

		CString cheater;
		m_cheater.GetLBText(m_cheater.GetCurSel(), cheater);
		CFileDialog dlg(false, ".xcrf", cheater + "_" + n(m_game_id).c_str(), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, save_filter, NULL);
		if (IDOK == dlg.DoModal())
		{
			CWaitCursor wait;
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
			key.set_value_string(vi_cheater, static_cast<string>(cheater));
			key.set_value_string(vi_mail, static_cast<string>(m_mail));
			key.set_value_int(vi_game_id, m_game_id);
			Cxif_key& screenshots_key = key.open_key_write(ki_screenshots);
			int index = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
			while (index != -1)
			{
				int id = m_list.GetItemData(index);
				const t_map_entry& e = m_map.find(id)->second;
				Cvirtual_image image;
				if (!image.load(e.fname))
				{
					Cvirtual_file f;
					if (!image.save_as_jpeg(f))
						screenshots_key.set_value_binary(index, f.read());
				}
				index = m_list.GetNextItem(index, LVNI_ALL | LVNI_SELECTED);
			}
			const string fname = dlg.GetPathName();
			key.vdata().export(fname);
			if (m_send_xhp)
			{
				HINSTANCE pMailState = LoadLibrary("MAPI32.DLL");
				if (pMailState == NULL)
				{
					AfxMessageBox(AFX_IDP_FAILED_MAPI_LOAD);
					return;
				}

				ULONG (PASCAL *lpfnSendMail)(ULONG, ULONG, MapiMessage*, FLAGS, ULONG);
				(FARPROC&)lpfnSendMail = GetProcAddress(pMailState, "MAPISendMail");
				if (lpfnSendMail == NULL)
				{
					AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
					return;
				}

				// prepare the file description (for the attachment)
				MapiFileDesc fileDesc;
				memset(&fileDesc, 0, sizeof(fileDesc));
				fileDesc.nPosition = (ULONG)-1;
				fileDesc.lpszPathName = const_cast<char*>(fname.c_str());

				MapiRecipDesc recipDesc;
				memset(&recipDesc, 0, sizeof(MapiRecipDesc));
				recipDesc.ulRecipClass = MAPI_TO;
				recipDesc.lpszAddress = "SMTP:XCRF@XCC.TMFWeb.NL";

				string title = static_cast<CString>(game_name[key.get_value_int(vi_game)]) + " XCRF: " + nickname + " (r) vs " + cheater + " (c) in game " + n(m_game_id).c_str();

				// prepare the message (empty with 1 attachment)
				MapiMessage message;
				memset(&message, 0, sizeof(message));
				message.lpszSubject = const_cast<char*>(title.c_str());
				// message.lpszNoteText = const_cast<char*>(static_cast<const char*>(m_description));
				message.nRecipCount = 1;
				message.lpRecips = &recipDesc;
				message.nFileCount = 1;
				message.lpFiles = &fileDesc;

				// prepare for modal dialog box
				AfxGetApp()->EnableModeless(FALSE);
				HWND hWndTop;
				CWnd* pParentWnd = CWnd::GetSafeOwner(NULL, &hWndTop);

				// some extra precautions are required to use MAPISendMail as it
				// tends to enable the parent window in between dialogs (after
				// the login dialog, but before the send note dialog).
				pParentWnd->SetCapture();
				::SetFocus(NULL);
				pParentWnd->m_nFlags |= WF_STAYDISABLED;

				int nError = lpfnSendMail(0, (ULONG)pParentWnd->GetSafeHwnd(), &message, MAPI_LOGON_UI | MAPI_DIALOG, 0);

				// after returning from the MAPISendMail call, the window must
				// be re-enabled and focus returned to the frame to undo the workaround
				// done before the MAPI call.
				::ReleaseCapture();
				pParentWnd->m_nFlags &= ~WF_STAYDISABLED;

				pParentWnd->EnableWindow(TRUE);
				::SetActiveWindow(NULL);
				pParentWnd->SetActiveWindow();
				pParentWnd->SetFocus();
				if (hWndTop != NULL)
					::EnableWindow(hWndTop, TRUE);
				AfxGetApp()->EnableModeless(TRUE);

				if (nError != SUCCESS_SUCCESS &&
					nError != MAPI_USER_ABORT && nError != MAPI_E_LOGIN_FAILURE)
				{
					AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
				}
			}
			if (m_send_ws)
			{
				CString page;
				page.Format(html_cheat_report, nickname, cheater, m_mail, m_game_id, web_encode(static_cast<string>(m_description), false).c_str());
				string fname = get_temp_path() + "cheat_report.html";
				ofstream(fname.c_str()) << static_cast<const char*>(page);
				ShellExecute(m_hWnd, "open", fname.c_str(), NULL, NULL, SW_SHOW);
			}
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

static string get_lid(t_game game)
{
	switch (game)
	{
	case game_ts:
		return "ts";
	}
	return "ra2";
}

static string a_gamelist(t_game game, string nickname)
{
	return a(web_encode(nickname), "href=\"http://xccu.sourceforge.net/xla/gamelist.php?lid=" + get_lid(game) + "&pid=" + uri_encode(nickname) + "\"");
}

static string a_gamelog(t_game game, int game_id)
{
	return game_id ? a(web_encode(n(game_id)), "href=\"http://xccu.sourceforge.net/xla/gamelog.php?lid=" + get_lid(game) + "&gid=" + n(game_id) + "\"") : "Unknown";
}

void create_tables(Cdatabase& database)
{
	Cxcc_error error = database.query("create table if not exists xcr_index (name varchar(255), reporter varchar(16), cheater varchar(16) not null, cheats varchar(255), lid varchar(16) not null, gid int not null, fname varchar(255), last_modified timestamp, primary key (cheater, lid, gid))");
}

void drop_tables(Cdatabase& database)
{
	Cxcc_error error = database.query("drop table if exists xcr_index");
}

int xcrf_decode(Cvirtual_binary s, string fname)
{
	Cxif_key key;
	int error = key.load_key(s.data(), s.size());
	if (!error)
	{
		t_game game = static_cast<t_game>(key.get_value_int(vi_game));
		int game_id = key.exists_value(vi_game_id) ? key.get_value_int(vi_game_id) : 0;
		Chtml page;
		page += tr(td("Reporter") + td(web_name(key.get_value_string(vi_name), key.get_value_string(vi_mail))) + td(a_gamelist(game, key.get_value_string(vi_nickname))));
		page += tr(td("Cheater") + td("&nbsp;") + td(a_gamelist(game, key.get_value_string(vi_cheater, ""))));
		page += tr(td("Game") + td(game_name[key.get_value_int(vi_game)]) + td(a_gamelog(game, game_id)));
		page += tr(td("Stats") + td(web_encode(key.get_value_string(vi_stats)), "colspan=2"));
		if (key.exists_value(vi_sync))
			page += tr(td("Sync") + td(web_encode(key.get_value_string(vi_sync)), "colspan=2"));
		page += tr(td("Description") + td(web_encode(key.get_value_string(vi_description)), "colspan=2"));
		page += tr(td("Cheats") + td(report_cheats(key), "colspan=2"));
		ofstream((fname + "index.html").c_str()) << "<link rel=stylesheet href=\"http://xccu.sourceforge.net\">" + table(page, "border=1") + report_screenshots(key.open_key_read(ki_screenshots), fname);
#ifndef NDEBUG
		static ofstream index_f("c:/temp/index.html"); // xhp/xcrf/index.txt");
		string name = Cfname(fname).get_path();
		name.erase(name.length() - 1);
		name.erase(0, name.rfind('\\') + 1);
		index_f << tr(td(key.get_value_string(vi_name)) + td(key.get_value_string(vi_nickname)) + td(key.get_value_string(vi_cheater, "")) + td(report_cheats(key)) + td(a("HTML", "href=\"" + name + "/\"")) + td(a("XCRF", "href=\"" + name + ".xcrf\""))) << endl;
		Cdatabase database;
		if (database.open())
			MessageBox(NULL, "Unable to open database.", NULL, MB_ICONERROR);
		create_tables(database);
		Csql_query sql_query(database);
		sql_query.write("insert into xcr_index (name, reporter, cheater, cheats, lid, gid, fname) values (%s, %s, %s, %s, %s, %s, %s)");
		sql_query.pe(key.get_value_string(vi_name));
		sql_query.pe(key.get_value_string(vi_nickname));
		sql_query.pe(key.get_value_string(vi_cheater, ""));
		sql_query.pe(report_cheats(key));
		sql_query.pe(get_lid(static_cast<t_game>(key.get_value_int(vi_game))));
		sql_query.p(key.get_value_int(vi_game_id));
		sql_query.pe(name);
		database.query(sql_query.read().c_str());
		// drop_tables(database);
		database.close();
#endif
	}
	return error;
}

BOOL Cdlg_ccr::PreTranslateMessage(MSG* pMsg)
{
	m_tooltip.RelayEvent(pMsg);
	return ETSLayoutDialog::PreTranslateMessage(pMsg);
}
