// dlg_login.cpp : implementation file
//

#include "stdafx.h"
#include "dlg_login.h"

#include "socket.h"
#include "virtual_binary.h"
#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cdlg_login dialog


Cdlg_login::Cdlg_login(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(Cdlg_login::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cdlg_login)
	m_edit = _T("");
	//}}AFX_DATA_INIT
}


void Cdlg_login::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdlg_login)
	DDX_Control(pDX, IDC_GAME, m_game);
	DDX_Control(pDX, IDC_USER, m_user);
	DDX_Text(pDX, IDC_EDIT, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cdlg_login, ETSLayoutDialog)
	//{{AFX_MSG_MAP(Cdlg_login)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cdlg_login message handlers

static CString n(int v)
{
	char b[12];
	return itoa(v, b, 10);
}

BOOL Cdlg_login::OnInitDialog() 
{
	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< (pane(VERTICAL, GREEDY)
				<< item(IDC_GAME, GREEDY)
				<< item(IDC_USER, GREEDY)
				)
			<< (pane(VERTICAL, GREEDY)
				<< item(IDOK, NORESIZE)
				<< item(IDCANCEL, NORESIZE)
				)
			)
		<< item(IDC_EDIT, GREEDY)
		;
	ETSLayoutDialog::OnInitDialog();
	xcc_dirs::load_from_registry();
	add_game("Software\\Westwood\\Renegade", game_rg, 0xc);
	add_game("Software\\Westwood\\Tiberian Sun", game_ts, 0x12);
	add_game("Software\\Westwood\\Emperor", game_ebfd, 0x1f);
	add_game("Software\\Westwood\\Red Alert 2", game_ra2, 0x21);
	add_game("Software\\Westwood\\Nox", game_nox, 0x25);
	add_game("Software\\Westwood\\Yuri's Revenge", game_ra2_yr, 0x29);
	for (int i = 1; i < 26; i++)
	{
		t_nick e;
		HKEY key;
		if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CLASSES_ROOT, "Wchat\\Nick" + n(i) + "\\Nick", 0, KEY_READ, &key))
		{
			char b[16];
			DWORD cb_b = 16;
			if (ERROR_SUCCESS == RegQueryValueEx(key, NULL, NULL, NULL, reinterpret_cast<byte*>(b), &cb_b))
				e.name = b;
			RegCloseKey(key);
		}
		if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CLASSES_ROOT, "Wchat\\Nick" + n(i) + "\\Pass", 0, KEY_READ, &key))
		{
			char b[16];
			DWORD cb_b = 16;
			if (ERROR_SUCCESS == RegQueryValueEx(key, NULL, NULL, NULL, reinterpret_cast<byte*>(b), &cb_b))
				e.password = b;
			RegCloseKey(key);
		}
		if (!e.name.empty() && e.password.length() == 8)
		{
			m_user.SetItemData(m_user.AddString(e.name.c_str()), m_nicks.size());
			m_nicks.push_back(e);
		}
	}
	m_game.SetCurSel(0);
	m_user.SetCurSel(0);	
	return true;
}

void Cdlg_login::add_game(const string& reg_key, int game, int gsku)
{
	HKEY key;
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, reg_key.c_str(), 0, KEY_READ, &key))
	{
		char b[32];
		DWORD cb_b = 32;
		if (ERROR_SUCCESS == RegQueryValueEx(key, "Serial", NULL, NULL, reinterpret_cast<byte*>(b), &cb_b))
		{
			Cvirtual_binary s;
			if (!s.import(xcc_dirs::get_dir(static_cast<::t_game>(game)) + "woldata.key") && cb_b == 23 && !b[22])
			{
				string serial = b;
				for (int i = 0, j = 0; i < s.size(); i++)
				{
					serial[j++] = (1000 - s.data()[i] % 10 + (serial[j] - '0')) % 10 + '0';
					if (j == serial.length()) 
						j = 0;
				}
				t_game e;
				e.gsku = gsku;
				e.serial = serial;
				m_game.SetItemData(m_game.AddString(game_name[game]), m_games.size());
				m_games.push_back(e);			
			}
		}
		RegCloseKey(key);		
	}
}

void Cdlg_login::OnOK() 
{
	CWaitCursor wc;
	m_edit.Empty();
	Csocket s;
	s.open(SOCK_STREAM, true);
	if (s == -1)
		m_edit += "unable to create socket: " + static_cast<CString>(Csocket::error2a(WSAGetLastError()).c_str());
	else if (s.connect(m_ipa, htons(4005)))
		m_edit += "unable to connect: " + static_cast<CString>(Csocket::error2a(WSAGetLastError()).c_str());
	else
	{
		strstream msg;
		int selected_game = m_game.GetItemData(m_game.GetCurSel());
		int selected_nick = m_user.GetItemData(m_user.GetCurSel());
		if (selected_game < 0 || selected_nick < 0)
			return;
		const t_game& game = m_games[selected_game];
		const t_nick& nick = m_nicks[selected_nick];
		msg << "cvers 0 " << (game.gsku << 8) << endl
			<< "nick " << nick.name << endl
			<< "apgar " << nick.password << " 0" << endl
			<< "serial " << game.serial << endl
			<< "user UserName e e e" << endl
			<< "quit" << endl;
		m_edit += "server: ";
		m_edit += Csocket::inet_ntoa(m_ipa).c_str();
		m_edit += "\r\n";
		m_edit += "nick: ";
		m_edit += nick.name.c_str();
		m_edit += "\r\n";
		if (msg.pcount() != s.send(msg.str(), msg.pcount()))
			m_edit += "unable to send: " + static_cast<CString>(Csocket::error2a(WSAGetLastError()).c_str());
		else
		{
			const int cb_d = 4 << 10;
			char d[cb_d];				
			int e;
			while ((e = s.recv(d, cb_d)) && e != SOCKET_ERROR)
				m_edit += CString(d, e);
			if (e == SOCKET_ERROR)
				m_edit += "unable to receive: " + static_cast<CString>(Csocket::error2a(WSAGetLastError()).c_str());
		}
	}
	UpdateData(false);
}
