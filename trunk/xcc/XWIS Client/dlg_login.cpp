#include "stdafx.h"
#include "dlg_login.h"

#include <boost/format.hpp>
#include "irc_params.h"
#include "multi_line.h"
#include "reg_key.h"
#include "socket.h"
#include <virtual_binary.h>
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
	add_game("Software\\Westwood\\Emperor", game_ebfd, 0x1f);
	add_game("Software\\Westwood\\Nox", game_nox, 0x25);
	add_game("Software\\Westwood\\Tiberian Sun", game_ts, 0x12);
	add_game("Software\\Westwood\\Tiberian Sun", game_ts_fs, 0x1c);
	add_game("Software\\Westwood\\Red Alert 2", game_ra2, 0x21);
	add_game("Software\\Westwood\\Renegade", game_rg, 0xc);
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
	if (m_nicks.empty())
	{
		m_user.SetItemData(m_user.AddString(""), m_nicks.size());
		m_nicks.push_back(t_nick());
	}
	m_game.SetCurSel(0);
	m_user.SetCurSel(0);	
	return true;
}

void Cdlg_login::add_game(const string& reg_key, ::t_game game, int gsku)
{
	Creg_key key;
	string serial;
	if (ERROR_SUCCESS == key.open(HKEY_LOCAL_MACHINE, reg_key, KEY_READ))
		key.query_value("Serial", serial);
	if (serial.size() == 22)
	{
		Cvirtual_binary s;
		s.load(xcc_dirs::get_dir(game) + "woldata.key");
		for (int i = 0, j = 0; i < s.size(); i++, j++)
		{
			if (j == serial.length())
				j = 0;
			serial[j] = (262 - s.data()[i] + serial[j]) % 10 + '0';
		}
	}
	else
		serial.clear();
	t_game e;
	e.gsku = gsku;
	e.serial = serial;
	m_game.SetItemData(m_game.AddString(game_name[game]), m_games.size());
	m_games.push_back(e);			
}

static int send_recv(const string& host, int port, str_ref s0, string& d)
{
	Csocket s;
	s.open(SOCK_STREAM, true);
	if (s == -1)
	{
		d += "unable to create socket: " + Csocket::error2a(WSAGetLastError());
		return 1;
	}
	d = (boost::format("server: %s:%d (%s)\r\n") % host % port % Csocket::inet_ntoa(Csocket::get_host(host))).str();
	if (s.connect(Csocket::get_host(host), htons(port)))
	{
		d += "unable to connect: " + Csocket::error2a(WSAGetLastError());
		return 1;
	}
	if (s0.size() != s.send(s0))
	{
		d += "unable to send: " + Csocket::error2a(WSAGetLastError());
		return 1;
	}
	array<char, 4 << 10> d0;
	mutable_str_ref d1 = d0;
	while (int e = s.recv(d1))
	{
		if (e == SOCKET_ERROR)
		{
			d += "unable to receive: " + Csocket::error2a(WSAGetLastError());
			return 1;
		}
		d1.advance_begin(e);
	}
	d.append(d0.data(), d0.size() - d1.size());
	return 0;
}

void Cdlg_login::OnOK() 
{
	if (!UpdateData(true))
		return;
	int selected_game = m_game.GetItemData(m_game.GetCurSel());
	int selected_nick = m_user.GetItemData(m_user.GetCurSel());
	if (selected_game < 0 || selected_nick < 0)
		return;
	CWaitCursor wc;
	const t_game& game = m_games[selected_game];
	const t_nick& nick = m_nicks[selected_nick];
	m_edit.Empty();
	m_edit += "nick: ";
	m_edit += nick.name.c_str();
	m_edit += "\r\n";
	if (0)
	{
		m_edit += "serial: ";
		m_edit += game.serial.c_str();
		m_edit += "\r\n";
	}
	string host;
	int port = 0;
	{
		strstream msg;
		msg << "whereto 0 0 " << (game.gsku << 8) << endl
			<< "quit" << endl;
		string d;
		if (send_recv("servserv.westwood.com", 4005, str_ref(msg.str(), msg.pcount()), d))
		{
			m_edit += d.c_str();
			UpdateData(false);
			return;
		}
		Cmulti_line l0 = d;
		while (!l0.empty())
		{
			Circ_params p = l0.get_next_line('\n');
			if (p.p_int(0) != 605)
				continue;
			Cmulti_line l1 = p[2];
			host = l1.get_next_line(' ');
			port = l1.get_next_int(' ');
			break;
		}
	}
	{
		strstream msg;
		msg << "cvers 0 " << (game.gsku << 8) << endl
			<< "nick " << nick.name << endl
			<< "apgar " << nick.password << " 0" << endl;
		msg << "serial " << game.serial << endl
			<< "user" << endl
			<< "privmsg c /names" << endl;
		msg << "quit" << endl;
		string d;
		send_recv(host, port, str_ref(msg.str(), msg.pcount()), d);
		m_edit += d.c_str();
	}
	UpdateData(false);
}
