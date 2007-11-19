#include "stdafx.h"
#include "dlg_login.h"

#include "reg_key.h"
#include "socket.h"
#include "virtual_binary.h"
#include "xcc_dirs.h"

Cdlg_login::Cdlg_login(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(Cdlg_login::IDD, pParent)
{
	m_edit = _T("");
}

void Cdlg_login::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME, m_game);
	DDX_Control(pDX, IDC_USER, m_user);
	DDX_Text(pDX, IDC_EDIT, m_edit);
}

BEGIN_MESSAGE_MAP(Cdlg_login, ETSLayoutDialog)
END_MESSAGE_MAP()

static CString n(int v)
{
	char b[12];
	return itoa(v, b, 10);
}

BOOL Cdlg_login::OnInitDialog() 
{
	ETSLayoutDialog::OnInitDialog();
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
	UpdateLayout();
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
		Creg_key key;
		if (ERROR_SUCCESS == key.open(HKEY_CLASSES_ROOT, string("Wchat\\Nick" + n(i) + "\\Nick"), KEY_READ)
			&& ERROR_SUCCESS == key.query_value("", e.name)
			&& ERROR_SUCCESS == key.open(HKEY_CLASSES_ROOT, string("Wchat\\Nick" + n(i) + "\\Pass"), KEY_READ)
			&& ERROR_SUCCESS == key.query_value("", e.password)
			&& !e.name.empty() 
			&& e.password.length() == 8)
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
	Creg_key key;
	string serial;
	if (ERROR_SUCCESS != key.open(HKEY_LOCAL_MACHINE, reg_key, KEY_READ)
		|| ERROR_SUCCESS != key.query_value("Serial", serial)
		|| serial.size() != 22)
		return;
	Cvirtual_binary s;
	s.load(xcc_dirs::get_dir(static_cast<::t_game>(game)) + "woldata.key");
	for (int i = 0, j = 0; i < s.size(); i++, j++)
	{
		if (j == serial.length())
			j = 0;
		serial[j] = (262 - s.data()[i] + serial[j]) % 10 + '0';
	}
	t_game e;
	e.gsku = gsku;
	e.serial = serial;
	m_game.SetItemData(m_game.AddString(game_name[game]), m_games.size());
	m_games.push_back(e);			
}

void Cdlg_login::OnOK() 
{
	CWaitCursor wc;
	m_edit = "server: ";
	m_edit += Csocket::inet_ntoa(m_ipa).c_str();
	m_edit += "\r\n";
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
			<< "user" << endl
			<< "privmsg c /names" << endl
			<< "quit" << endl;
		m_edit += "nick: ";
		m_edit += nick.name.c_str();
		m_edit += "\r\n";
		if (0)
		{
			m_edit += "serial: ";
			m_edit += game.serial.c_str();
			m_edit += "\r\n";
		}
		if (msg.pcount() != s.send(const_memory_range(msg.str(), msg.pcount())))
			m_edit += "unable to send: " + static_cast<CString>(Csocket::error2a(WSAGetLastError()).c_str());
		else
		{
			const int cb_d = 4 << 10;
			char d[cb_d];				
			int e;
			while ((e = s.recv(memory_range(d, cb_d))) && e != SOCKET_ERROR)
				m_edit += CString(d, e);
			if (e == SOCKET_ERROR)
				m_edit += "unable to receive: " + static_cast<CString>(Csocket::error2a(WSAGetLastError()).c_str());
		}
	}
	UpdateData(false);
}
