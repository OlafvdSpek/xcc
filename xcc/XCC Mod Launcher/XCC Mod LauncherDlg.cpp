// XCC Mod LauncherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XCC Mod Launcher.h"
#include "XCC Mod LauncherDlg.h"

#include "cc_file.h"
#include "jpeg_file.h"
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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXCCModLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCModLauncherDlg)
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCModLauncherDlg message handlers

static int load_banner(Cvirtual_image& image)
{
	HINSTANCE hin = AfxGetInstanceHandle();
	HRSRC rc = FindResource(hin, MAKEINTRESOURCE(IDR_BANNER), "Binary");
	HGLOBAL hgl = LoadResource(NULL, rc);
	int cb_data = SizeofResource(NULL, rc);	
	const byte* data = static_cast<const byte*>(LockResource(hgl));	

	Cjpeg_file f;
	f.load(data, cb_data);
	int error = !f.is_valid() || f.decode(image);
	FreeResource(hgl);
	return error;
}

BOOL CXCCModLauncherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	Ccc_file f(true);
	if (f.open(m_mod_fname))
	{
		MessageBox("Error opening mod.", NULL, MB_ICONERROR);
		EndDialog(IDCANCEL);
		return true;
	}
	else
	{
		if (m_key.load_key(f.get_data(), f.get_size()))
		{
			f.close();
			MessageBox("Error reading mod.", NULL, MB_ICONERROR);
			EndDialog(IDCANCEL);
			return true;
		}
		else
		{
			m_mod.load(m_key);

			Cvirtual_image banner;
			if (!Cxcc_mod::load_banner(m_key, banner) || !load_banner(banner))
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

			CString name = m_mod.options().mod_name.c_str();
			CString caption;
			GetWindowText(caption);
			SetWindowText(caption + " - " + name);

			m_manual.EnableWindow(m_mod.contains(Cxcc_mod::ct_manual));
			m_ok.EnableWindow(true);
			m_site.EnableWindow(web_is_link(m_mod.options().link));

			/*
			m_manual.SetWindowText(name + " &Manual");
			m_ok.SetWindowText(name + " Mod");
			m_site.SetWindowText(name + " &Site");
			*/
		}
		f.close();
	}
	return true;
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
	if (MessageBox("Would you like to deactivate the mod?", NULL, MB_YESNO) == IDYES && m_mod.deactivate(false))
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

void CXCCModLauncherDlg::set_mod_fname(string mod_fname)
{
	m_mod_fname = mod_fname;
}
