// XCC Cheat ReporterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XCC Cheat Reporter.h"
#include "XCC Cheat ReporterDlg.h"

#include "dlg_ccr.h"
#include "virtual_image.h"
#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCCheatReporterDlg dialog

CXCCCheatReporterDlg::CXCCCheatReporterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXCCCheatReporterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXCCCheatReporterDlg)
	m_game = 1;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXCCCheatReporterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCCheatReporterDlg)
	DDX_CBIndex(pDX, IDC_GAME, m_game);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXCCCheatReporterDlg, CDialog)
	//{{AFX_MSG_MAP(CXCCCheatReporterDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PASTE, OnPaste)
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	ON_BN_CLICKED(IDC_DECODE, OnDecode)
	ON_BN_CLICKED(IDC_XHP, OnXhp)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCCheatReporterDlg message handlers

BOOL CXCCCheatReporterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// decode("c:\\data\\cr.xcrf");
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXCCCheatReporterDlg::OnPaint() 
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

HCURSOR CXCCCheatReporterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXCCCheatReporterDlg::OnPaste() 
{
	Cvirtual_image image;
	int error = image.get_clipboard();
	if (error)
		MessageBox("Unable to open clipboard.", NULL, MB_ICONERROR);		
	else
	{
		CWaitCursor wait;
		image.save();
		if (error)
			MessageBox("Unable to write image.", NULL, MB_ICONERROR);		
	}
}

void CXCCCheatReporterDlg::OnCreate() 
{
	Cdlg_ccr dlg;
	dlg.game(game());
	if (dlg.load_stats())
		MessageBox("Unable to load mpstats.txt.", NULL, MB_ICONERROR);		
	else 
		dlg.DoModal();
}

void CXCCCheatReporterDlg::OnDecode() 
{
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "XCRF files (*.xcrf)|*.xcrf|", NULL);
	if (IDOK == dlg.DoModal())
		decode(static_cast<string>(dlg.GetPathName()));
}

void CXCCCheatReporterDlg::OnXhp() 
{
	ShellExecute(m_hWnd, "open", "http://xccu.sourceforge.net/", NULL, NULL, SW_SHOW);
}

t_game CXCCCheatReporterDlg::game()
{
	UpdateData(true);
	switch (m_game)
	{
	case 0:
		return game_ts;
	default:
		return game_ra2;
	}
}

t_file_type CXCCCheatReporterDlg::image_format()
{
	return ft_jpeg;
}

string CXCCCheatReporterDlg::image_ext()
{
	switch (image_format())
	{
	case ft_jpeg:
		return ".jpeg";
	case ft_pcx:
		return ".pcx";
	case ft_png:
		return ".png";
	}
	return "";
}

void CXCCCheatReporterDlg::decode(string _fname)
{
	CWaitCursor wait;	
	Cvirtual_binary s;
	if (!s.import(_fname))
	{
		Cfname fname = _fname;
		fname.set_ext("");
		fname.make_path();
		create_directory(fname);
		xcrf_decode(s, fname);
	}
}

void CXCCCheatReporterDlg::OnDropFiles(HDROP hDropInfo) 
{
	int c_files = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	char fname[MAX_PATH];
	for (int i = 0; i < c_files; i++)
	{
		DragQueryFile(hDropInfo, i, fname, MAX_PATH);
		decode(fname);
	}
	DragFinish(hDropInfo);
}
