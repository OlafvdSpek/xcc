#include "stdafx.h"
#include "XCC WOL IRC Server Client.h"
#include "XCC WOL IRC Server ClientDlg.h"

#include "dlg_login.h"
#include "dlg_serials.h"
#include "multi_line.h"
#include "socket.h"
#include "string_conversion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CXCCWOLIRCServerClientDlg::CXCCWOLIRCServerClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXCCWOLIRCServerClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXCCWOLIRCServerClientDlg)
	m_hosts = _T("");
	m_wolapi_dll = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXCCWOLIRCServerClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCWOLIRCServerClientDlg)
	DDX_Control(pDX, IDC_IPA2, m_ipa2);
	DDX_Control(pDX, IDC_IPA, m_ipa);
	DDX_Text(pDX, IDC_HOSTS, m_hosts);
	DDX_Text(pDX, IDC_WOLAPI_DLL, m_wolapi_dll);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXCCWOLIRCServerClientDlg, CDialog)
	//{{AFX_MSG_MAP(CXCCWOLIRCServerClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SET, OnSet)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_TEST, OnTest)
	ON_BN_CLICKED(IDC_LADDER, OnLadder)
	ON_BN_CLICKED(IDC_VIEW_SERIALS, OnViewSerials)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static bool platform_nt()
{
	OSVERSIONINFO versionInfo;
	versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	return GetVersionEx(&versionInfo) && versionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT;
}

static string hosts_fname()
{
	char win_dir[256];
	if (platform_nt() ? !GetSystemDirectory(win_dir, 256) : !GetWindowsDirectory(win_dir, 256))
		return "c:\\windows\\hosts";
	return static_cast<string>(win_dir) + (platform_nt() ? "\\drivers\\etc\\hosts" : "\\hosts");
}

static string wolapi_dll_fname()
{
	string dir;
	HKEY key;
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Westwood\\WOLAPI", 0, KEY_QUERY_VALUE, &key))
	{
		char s[MAX_PATH];
		DWORD size = MAX_PATH;
		if (ERROR_SUCCESS == RegQueryValueEx(key, "InstallPath", 0, 0, (byte*)s, &size))
			dir = s;
		RegCloseKey(key);
	}
	return dir;
}

BOOL CXCCWOLIRCServerClientDlg::OnInitDialog()
{
	m_hosts = hosts_fname().c_str();
	m_wolapi_dll = wolapi_dll_fname().c_str();

	CDialog::OnInitDialog();

	in_addr ipa;
	ipa.s_addr = Csocket::get_host("servserv.xwis.net");

	m_ipa.SetAddress(ipa.S_un.S_un_b.s_b1, ipa.S_un.S_un_b.s_b2, ipa.S_un.S_un_b.s_b3, ipa.S_un.S_un_b.s_b4);
	update_ipa2();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;
}

void CXCCWOLIRCServerClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

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
		CDialog::OnPaint();
	}
}

HCURSOR CXCCWOLIRCServerClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CXCCWOLIRCServerClientDlg::update_hosts(const string& ipa)
{
	int attributes = GetFileAttributes(m_hosts);
	if (attributes != -1 && attributes & FILE_ATTRIBUTE_READONLY)
		SetFileAttributes(m_hosts, attributes & ~FILE_ATTRIBUTE_READONLY);
	string b;
	ifstream f(m_hosts);
	string s;
	while (getline(f, s))
	{
		Cmulti_line l = Cmulti_line(s).get_next_line('#');
		l.get_next_line(' ');
		string a = l.get_next_line(' ');
		if (a != "irc.westwood.com"
			&& a != "servserv.westwood.com")
			b += s + '\n';
	}
	if (f.bad())
		return 1;
	if (!ipa.empty())
		b += ipa + " irc.westwood.com\n"
			+ ipa + " servserv.westwood.com\n";
	return !(ofstream(m_hosts) << b);
}

void CXCCWOLIRCServerClientDlg::OnSet() 
{
	DWORD a;
	m_ipa.GetAddress(a);
	a = htonl(a);
	if (update_hosts(inet_ntoa(*reinterpret_cast<in_addr*>(&a))))
		::MessageBox(NULL, "Your hosts file could not be updated.", NULL, MB_ICONERROR);
	Sleep(25);
	update_ipa2();
}

void CXCCWOLIRCServerClientDlg::OnReset() 
{
	if (update_hosts(""))
		::MessageBox(NULL, "Your hosts file could not be updated.", NULL, MB_ICONERROR);
	Sleep(25);
	update_ipa2();
}

void CXCCWOLIRCServerClientDlg::OnOpen() 
{
	ShellExecute(NULL, NULL, "notepad", m_hosts, NULL, SW_SHOW);	
}

void CXCCWOLIRCServerClientDlg::update_ipa2()
{
	hostent* e = gethostbyname("servserv.westwood.com");
	if (!e || e->h_addrtype != 2 || e->h_length != sizeof(in_addr))
		return;
	in_addr a = *reinterpret_cast<in_addr*>(*e->h_addr_list);
	m_ipa2.SetAddress(a.S_un.S_un_b.s_b1, a.S_un.S_un_b.s_b2, a.S_un.S_un_b.s_b3, a.S_un.S_un_b.s_b4);
}

void CXCCWOLIRCServerClientDlg::OnTest() 
{
	hostent* e = gethostbyname("servserv.westwood.com");
	if (!e || e->h_addrtype != 2 || e->h_length != sizeof(in_addr))
		return;
	Cdlg_login dlg;
	dlg.ipa(*reinterpret_cast<int*>(*e->h_addr_list));
	dlg.DoModal();
}

void CXCCWOLIRCServerClientDlg::OnLadder() 
{
	ShellExecute(NULL, NULL, "http://xwis.net/ladders/", NULL, NULL, SW_SHOW);		
}

void CXCCWOLIRCServerClientDlg::OnViewSerials()
{
	Cdlg_serials dlg;
	dlg.DoModal();
}
