// XRG Mod LauncherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XRG Mod Launcher.h"
#include "XRG Mod LauncherDlg.h"

#include "cc_file.h"
#include "fname.h"
#include "rml_file.h"
#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXRGModLauncherDlg dialog

CXRGModLauncherDlg::CXRGModLauncherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXRGModLauncherDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXRGModLauncherDlg)
	m_binary_diff_compression = FALSE; // TRUE;
	m_tga_compression = TRUE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXRGModLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXRGModLauncherDlg)
	DDX_Check(pDX, IDC_BINARY_DIFF_COMPRESSION, m_binary_diff_compression);
	DDX_Check(pDX, IDC_TGA_COMPRESSION, m_tga_compression);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXRGModLauncherDlg, CDialog)
	//{{AFX_MSG_MAP(CXRGModLauncherDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONVERT, OnConvert)
	ON_BN_CLICKED(IDC_XHP, OnXHP)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXRGModLauncherDlg message handlers

BOOL CXRGModLauncherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXRGModLauncherDlg::OnPaint() 
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

HCURSOR CXRGModLauncherDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXRGModLauncherDlg::OnConvert() 
{
	UpdateData();
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "Mods (*.pkg;*.rmlf)|*.pkg;*.rmlf|", NULL);
	if (IDOK == dlg.DoModal())
		convert(static_cast<string>(dlg.GetPathName()));
}

void CXRGModLauncherDlg::OnXHP() 
{
	ShellExecute(m_hWnd, "open", "http://xcc.tiberian.com/", NULL, NULL, SW_SHOW);
}

void CXRGModLauncherDlg::convert(string fname)
{
	CWaitCursor wait;
	Cfname s_fname = fname;
	Cfname d_fname = s_fname;
	Ccc_file f(true);
	if (!f.open(fname))
	{
		switch (f.get_file_type())			
		{
		case ft_mix_rg:
			d_fname.set_ext(".rmlf");
			encode_rmlf(s_fname, m_binary_diff_compression, m_tga_compression).vdata().export(d_fname);
			break;
		case ft_xif:
			d_fname.set_path(xcc_dirs::get_dir(game_rg) + "data/");
			d_fname.set_ext(".pkg");
			decode_rmlf(s_fname).export(d_fname);
			break;
		}
		f.close();
	}
}

void CXRGModLauncherDlg::OnDropFiles(HDROP hDropInfo) 
{
	UpdateData();
	int c_files = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	char fname[MAX_PATH];
	for (int i = 0; i < c_files; i++)
	{
		DragQueryFile(hDropInfo, i, fname, MAX_PATH);
		convert(fname);
	}
	DragFinish(hDropInfo);
}
