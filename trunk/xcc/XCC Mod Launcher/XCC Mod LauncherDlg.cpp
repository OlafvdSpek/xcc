// XCC Mod LauncherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XCC Mod Launcher.h"
#include "XCC Mod LauncherDlg.h"

#include <afxinet.h>
#include "cc_file.h"
#include "download_dlg.h"
#include "jpeg_file.h"
#include "multi_line.h"
#include "virtual_tfile.h"
#include "web_tools.h"
#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCModLauncherDlg dialog

CXCCModLauncherDlg::CXCCModLauncherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXCCModLauncherDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXCCModLauncherDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXCCModLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCModLauncherDlg)
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_update);
	DDX_Control(pDX, IDC_BUTTON_XHP, m_xhp);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_BANNER, m_banner);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_BUTTON_SITE, m_site);
	DDX_Control(pDX, IDC_BUTTON_MANUAL, m_manual);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXCCModLauncherDlg, CDialog)
	//{{AFX_MSG_MAP(CXCCModLauncherDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_XHP, OnButtonXHP)
	ON_BN_CLICKED(IDC_BUTTON_SITE, OnButtonSite)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL, OnButtonManual)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(ID_MAIL_AUTHOR, OnMailAuthor)
	ON_BN_CLICKED(ID_UNINSTALL, OnUninstall)
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCModLauncherDlg message handlers

static int load_banner(Cvirtual_image& image)
{
	HINSTANCE hin = AfxGetInstanceHandle();
	HRSRC rc = FindResource(hin, MAKEINTRESOURCE(IDR_BANNER), "Binary");
	HGLOBAL hgl = LoadResource(NULL, rc);
	Cjpeg_file f;
	f.load(Cvirtual_binary(static_cast<const byte*>(LockResource(hgl)), SizeofResource(NULL, rc)));
	FreeResource(hgl);
	return !f.is_valid() || f.decode(image);
}

HBITMAP CXCCModLauncherDlg::create_bitmap(Cvirtual_image& image)
{
	image.swap_rb();
	BITMAPINFOHEADER header;
	ZeroMemory(&header, sizeof(BITMAPINFOHEADER));
	header.biSize = sizeof(BITMAPINFOHEADER);
	header.biWidth = image.cx();
	header.biHeight = -image.cy();
	header.biPlanes = 1;
	header.biBitCount = image.cb_pixel() << 3;
	header.biCompression = BI_RGB;
	return CreateDIBitmap(CClientDC(NULL), &header, CBM_INIT, image.image(), reinterpret_cast<BITMAPINFO*>(&header), DIB_RGB_COLORS);
}

void CXCCModLauncherDlg::load_button_image(string fname, CButton& button)
{
	Cvirtual_image image;
	if (!Cxcc_mod::load_launcher_image(m_key, fname, image))
	{
		HBITMAP bitmap = create_bitmap(image);
		if (bitmap)
		{
			button.ModifyStyle(0, BS_BITMAP, 0);
			button.SetBitmap(bitmap);
		}
	}
}

BOOL CXCCModLauncherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	if (!m_source.data() && m_source.import(m_mod_fname))
	{
		MessageBox("Error opening mod.", NULL, MB_ICONERROR);
		EndDialog(IDCANCEL);
		return true;
	}
	else
	{
		if (m_key.load_key(m_source.data(), m_source.size()))
		{
			MessageBox("Error reading mod.", NULL, MB_ICONERROR);
			EndDialog(IDCANCEL);
		}
		else if (m_mod.load(m_key), m_mod.future_version())
		{
			MessageBox("An update of XCC Mod Launcher is needed to open this mod.", NULL, MB_ICONERROR);
			EndDialog(IDCANCEL);
		}
		else
		{
			Cvirtual_image banner;
			if (!Cxcc_mod::load_launcher_image(m_key, "banner.jpeg", banner) || !load_banner(banner))
			{
				banner.swap_rb();
				BITMAPINFOHEADER header;
				ZeroMemory(&header, sizeof(BITMAPINFOHEADER));
				header.biSize = sizeof(BITMAPINFOHEADER);
				header.biWidth = banner.cx();
				header.biHeight = -banner.cy();
				header.biPlanes = 1;
				header.biBitCount = banner.cb_pixel() << 3;
				header.biCompression = BI_RGB;
				HBITMAP bitmap = CreateDIBitmap(CClientDC(NULL), &header, CBM_INIT, banner.image(), reinterpret_cast<BITMAPINFO*>(&header), DIB_RGB_COLORS);
				if (bitmap)
					m_banner.SetBitmap(bitmap);
			}
			load_button_image("xhp_button.jpeg", m_xhp);
			load_button_image("exit_button.jpeg", m_cancel);
			load_button_image("update_button.jpeg", m_update);
			load_button_image("site_button.jpeg", m_site);
			load_button_image("mod_button.jpeg", m_ok);
			load_button_image("manual_button.jpeg", m_manual);

			Cxcc_mod::t_options options = m_mod.options();
			CString name = options.mod_name.c_str();
			CString caption;
			GetWindowText(caption);
			SetWindowText(caption + " - " + name + " - " + options.mod_version.c_str());
			if (0)
			{
				Cfname uninstall_exe = Cfname(m_mod_fname).get_path() + "uninstal.exe";
				if (uninstall_exe.exists())
					m_uninstall_exe = uninstall_exe;
			}
			if (!options.xhp_button)
				m_xhp.ModifyStyle(WS_VISIBLE, 0, 0);
			if (!options.exit_button)
				m_cancel.ModifyStyle(WS_VISIBLE, 0, 0);
			if (!options.update_button)
				m_update.ModifyStyle(WS_VISIBLE, 0, 0);
			if (!options.manual_button)
				m_manual.ModifyStyle(WS_VISIBLE, 0, 0);
			if (!options.site_button)
				m_site.ModifyStyle(WS_VISIBLE, 0, 0);
			if (web_is_link(options.mod_ucf))
				m_update.EnableWindow(true);
			else if (m_uninstall_exe.size())
			{
				m_update.EnableWindow(true);
				m_update.SetWindowText("Uninstall");
			}
			else
				m_update.EnableWindow(false);
			m_manual.EnableWindow(m_mod.contains(Cxcc_mod::ct_manual));
			m_ok.EnableWindow(true);
			m_site.EnableWindow(web_is_link(options.link));

			if (options.custom_button_text)
			{
				m_manual.SetWindowText(name + " &Manual");
				m_ok.SetWindowText(name + " Mod");
				m_site.SetWindowText(name + " &Site");
			}

			CMenu* pSysMenu = GetSystemMenu(FALSE);
			if (pSysMenu != NULL)
			{
				pSysMenu->AppendMenu(MF_SEPARATOR);
				pSysMenu->AppendMenu((web_is_link(options.mod_ucf) ? MF_ENABLED : MF_GRAYED) | MF_STRING, IDC_BUTTON_UPDATE, "Check for &update");
				pSysMenu->AppendMenu((web_is_mail(options.mail) ? MF_ENABLED : MF_GRAYED) | MF_STRING, ID_MAIL_AUTHOR, ("Send &mail to " + options.name).c_str());
				pSysMenu->AppendMenu((m_mod.contains(Cxcc_mod::ct_manual) ? MF_ENABLED : MF_GRAYED) | MF_STRING, IDC_BUTTON_MANUAL, "View " + name + " &Manual");
				pSysMenu->AppendMenu((web_is_link(options.link) ? MF_ENABLED : MF_GRAYED) | MF_STRING, IDC_BUTTON_SITE, "Visit " + (options.link_title.empty() ? name  + " &Site" : options.link_title.c_str()));
				pSysMenu->AppendMenu(MF_STRING, IDC_BUTTON_XHP, "Visit &XCC Home Page");
				// pSysMenu->AppendMenu((m_uninstall_exe.size() ? MF_ENABLED : MF_GRAYED) | MF_STRING, ID_UNINSTALL, "Uninstall");
			}

		}
	}
	m_source.clear();
	return true;
}

void CXCCModLauncherDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	switch (nID & 0xfff0)
	{
	case IDC_BUTTON_UPDATE:
		OnButtonUpdate();
		break;
	case ID_MAIL_AUTHOR:
		OnMailAuthor();
		break;
	case IDC_BUTTON_MANUAL:
		OnButtonManual();
		break;
	case IDC_BUTTON_SITE:
		OnButtonSite();
		break;
	case IDC_BUTTON_XHP:
		OnButtonXHP();
		break;
	case ID_UNINSTALL:
		OnUninstall();
		break;
	default:
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXCCModLauncherDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

HCURSOR CXCCModLauncherDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXCCModLauncherDlg::OnButtonXHP() 
{
	ShellExecute(m_hWnd, "open", "http://xcc.tiberian.com/", NULL, NULL, SW_SHOW);
}

void CXCCModLauncherDlg::OnButtonSite() 
{
	ShellExecute(m_hWnd, "open", m_mod.options().link.c_str(), NULL, NULL, SW_SHOW);
}

void CXCCModLauncherDlg::OnMailAuthor() 
{
	ShellExecute(m_hWnd, "open", ("mailto:" + m_mod.options().mail).c_str(), NULL, NULL, SW_SHOW);
}

void CXCCModLauncherDlg::OnOK() 
{
	CWaitCursor wait;
	if (Cxcc_mod::activate(m_key, false))
	{
		MessageBox("Error activating mod.", NULL, MB_ICONERROR);
	}
	else if (m_mod.launch_game(true))
	{
		MessageBox("Error launching game.", NULL, MB_ICONERROR);				
	}	
	if ((!m_mod.options().confirm_deactivate || MessageBox("Would you like to deactivate the mod?", NULL, MB_ICONQUESTION | MB_YESNO) == IDYES) && m_mod.deactivate(false))
	{
		MessageBox("Error deactivating mod.", NULL, MB_ICONERROR);				
	}
}

void CXCCModLauncherDlg::OnButtonManual() 
{
	int error = 0;
	char temp_dir[MAX_PATH];
	if (!GetTempPath(MAX_PATH, temp_dir))
		error = 1;
	else
	{
		string dir = temp_dir + m_mod.options().mod_name + " Manual/";
		CreateDirectory(dir.c_str(), NULL);
		error = Cxcc_mod::launch_manual(m_key, dir, m_hWnd);
	}
	if (error)
		MessageBox("Error extracting manual.", NULL, MB_ICONERROR);
}

void CXCCModLauncherDlg::set_mod(Cvirtual_binary v)
{
	m_source = v;
}

void CXCCModLauncherDlg::set_mod_fname(string mod_fname)
{
	m_mod_fname = mod_fname;
}

int CXCCModLauncherDlg::download_update(string link, string fname)
{
	int error = 0;
	CInternetSession is;
	CHttpFile* f = reinterpret_cast<CHttpFile*>(is.OpenURL(link.c_str(), INTERNET_FLAG_TRANSFER_BINARY));
	if (!f)
		error = 1;
	else 
	{
		Cfile32 g;
		DWORD status;
		if (!f->QueryInfoStatusCode(status))
			error = 2;
		else if (status != 200)
			error = 3;
		else if (g.open_write(fname))
			error = 4;
		else
		{
			int total_size = f->Seek(0, CFile::end);
			f->Seek(0, CFile::begin);
			Cdownload_dlg dlg;
			dlg.set(link, fname, total_size);
			dlg.Create(Cdownload_dlg::IDD, NULL);
			dlg.EnableWindow(false);
			int size = 0;
			while (!error)
			{
				int cb_p = min(f->GetLength(), 64 << 10);
				if (!cb_p)
					break;
				char* p = new char[cb_p];
				f->Read(p, cb_p);
				error = g.write(p, cb_p);
				delete[] p;
				size += cb_p;
				dlg.set_size(size);
				dlg.UpdateWindow();
			}
			g.close();
			dlg.DestroyWindow();
		}
		f->Close();
	}
	return error;
}

void CXCCModLauncherDlg::OnButtonUpdate() 
{
	if (!web_is_link(m_mod.options().mod_ucf))
	{
		OnUninstall();
		return;
	}
	int error = 0;
	CWaitCursor wait;
	CInternetSession is;
	CHttpFile* f = reinterpret_cast<CHttpFile*>(is.OpenURL(m_mod.options().mod_ucf.c_str()));
	if (!f)
		error = 1;
	else
	{
		string s;
		while (1)
		{
			int cb_p = f->GetLength();
			if (!cb_p)
				break;
			char* p = new char[cb_p + 1];
			f->Read(p, cb_p);
			p[cb_p] = 0;
			s += p;
			delete[] p;
		}
		f->Close();
		Cvirtual_tfile f;
		f.load_data(Cvirtual_binary(s.c_str(), s.length()));
		error = 2;
		while (!f.eof())
		{
			Cmulti_line l = f.read_line();
			if (l.get_next_line('=') == m_mod.options().mod_name)
			{
				error = 0;
				string version = l.get_next_line(',');
				string link = l.get_next_line(',');
				if (m_mod.options().mod_version < version)
				{
					if (MessageBox(("Version " + version + " is available. Would you like to download this update?").c_str(), NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
					{
						Cfname bak_fname = m_mod_fname;
						bak_fname.set_ext(".bak");
						if (move_file(m_mod_fname, static_cast<string>(bak_fname)))
							MessageBox("Error replacing Mod.", NULL, MB_ICONERROR);
						else
						{
							EnableWindow(false);
							error = download_update(link, m_mod_fname);
							EnableWindow(true);
							if (error)
							{
								move_file(static_cast<string>(bak_fname), m_mod_fname);
								MessageBox("Error retrieving update.", NULL, MB_ICONERROR);
								error = 0;
							}
							else
							{
								delete_file(bak_fname);
								EndDialog(IDCANCEL);
								ShellExecute(m_hWnd, "open", static_cast<string>(GetModuleFileName()).c_str(), m_mod_fname.c_str(), NULL, SW_SHOW);
							}
						}
					}
				}
				else
					MessageBox("No update is available.", NULL, MB_ICONINFORMATION);
				break;
			}
		}
	}
	if (error)
		MessageBox("Error querying for update.", NULL, MB_ICONERROR);
}


void CXCCModLauncherDlg::OnUninstall() 
{
	EndDialog(IDCANCEL);
	ShellExecute(m_hWnd, "open", m_uninstall_exe.c_str(), NULL, NULL, SW_SHOW);
}
