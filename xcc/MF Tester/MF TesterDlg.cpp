// MF TesterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MF Tester.h"
#include "MF TesterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFTesterDlg dialog

CMFTesterDlg::CMFTesterDlg(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(CMFTesterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMFTesterDlg)
	m_edit = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFTesterDlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMFTesterDlg)
	DDX_Text(pDX, IDC_EDIT, m_edit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMFTesterDlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(CMFTesterDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFTesterDlg message handlers

static CString n(int v)
{
	char b[12];
	return itoa(v, b, 10);
}

static bool platform_nt()
{
	OSVERSIONINFO versionInfo;
	versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	return GetVersionEx(&versionInfo) ? versionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT : false;
}

static CString hosts_fname()
{
	char win_dir[256];
	return (platform_nt() ? GetSystemDirectory(win_dir, 256) : GetWindowsDirectory(win_dir, 256))
		? static_cast<CString>(win_dir) + (platform_nt() ? "\\drivers\\etc\\hosts" : "\\hosts")
		: "c:\\windows\\hosts";
}

BOOL CMFTesterDlg::OnInitDialog()
{
	m_edit += "hosts filename: ";
	m_edit += hosts_fname();
	m_edit += "\r\n";
	test_hostname("localhost");
	test_hostname("games2.westwood.com");
	test_hostname("servserv.westwood.com");
	// test_mf();
	test_serverlist_server("127.0.0.1", 0x2100);
	test_serverlist_server("127.0.0.1", 0x2900);
	test_serverlist_server("159.153.208.17", 0x2100);
	test_serverlist_server("159.153.208.17", 0x2900);

	ETSLayoutDialog::OnInitDialog();
	CreateRoot(VERTICAL)
		<< item(IDC_EDIT, GREEDY);
	UpdateLayout();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return true;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFTesterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		ETSLayoutDialog::OnPaint();
	}
}

HCURSOR CMFTesterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMFTesterDlg::test_hostname(const char *name)
{
	hostent* e = gethostbyname(name);
	m_edit += name;
	m_edit += ": ";
	if (e)
	{
		if (e->h_addrtype == 2 && e->h_length == sizeof(in_addr))
			m_edit += inet_ntoa(*reinterpret_cast<in_addr*>(*e->h_addr_list));
		else
			m_edit += n(e->h_addrtype) + " " + n(e->h_length);
	}
	else
		m_edit += "null";
	m_edit += "\r\n";
}

static int send_msg(SOCKET& s, strstream& msg)
{
	return msg.pcount() != send(s, msg.str(), msg.pcount(), 0);
}

void CMFTesterDlg::test_serverlist_server(const char* ipa, int gid)
{
	m_edit += "\r\nserverlist server (";
	m_edit += ipa;
	m_edit += " ";
	m_edit += n(gid);
	m_edit += "): ";
	SOCKET s = socket(PF_INET, SOCK_STREAM, 0);
	if (s == -1)
		m_edit += "unable to create socket: " + n(WSAGetLastError());
	else
	{
		sockaddr_in d_address;
		d_address.sin_family = AF_INET;
		d_address.sin_port = htons(4005);
		d_address.sin_addr.S_un.S_addr = inet_addr(ipa);
		if (connect(s, reinterpret_cast<const sockaddr*>(&d_address), sizeof(sockaddr_in)))
			m_edit += "unable to connect: " + n(WSAGetLastError());
		else
		{
			m_edit += "\r\n";
			strstream msg;
			msg << "lobcount " << gid << endl
				<< "whereto TibSun TibPass99 " << gid << " 65542 0" << endl
				<< "quit" << endl;
			if (send_msg(s, msg))
				m_edit += "unable to send: " + n(WSAGetLastError());
			else
			{
				const int cb_d = 4 << 10;
				char d[cb_d];				
				while (1)
				{
					int e = recv(s, d, cb_d, 0);
					if (e == SOCKET_ERROR)
					{
						m_edit += "unable to receive" + n(WSAGetLastError());
						break;
					}
					else if (e)
						m_edit += string(d, e).c_str();
					else
						break;
				}
			}
		}
		closesocket(s);
	}
	m_edit += "\r\n";
}

void CMFTesterDlg::test_mf()
{
	m_edit += "MF: ";
	HWND hWnd = ::FindWindow("Afx:400000:8:10013:0:c012f", NULL);
	if (hWnd)
	{
		const int cb_b = 256;
		char b[cb_b + 1];
		m_edit += ::GetWindowText(hWnd, b, cb_b) ? b : "0";
	}
	else
		m_edit += "null";
	m_edit += "\r\n";
}
