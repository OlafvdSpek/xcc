// XCC Map DecoderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XCC Map Decoder.h"
#include "XCC Map DecoderDlg.h"

#include <fstream>
#include <strstream>
#include "cc_file.h"
#include "fname.h"
#include "map_ts_encoder.h"
#include "mix_file_write.h"
#include "string_conversion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCMapDecoderDlg dialog

CXCCMapDecoderDlg::CXCCMapDecoderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXCCMapDecoderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXCCMapDecoderDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXCCMapDecoderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCMapDecoderDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXCCMapDecoderDlg, CDialog)
	//{{AFX_MSG_MAP(CXCCMapDecoderDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONVERT, OnConvert)
	ON_BN_CLICKED(IDC_BUTTON_XCC_HOME_PAGE, OnButtonXccHomePage)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCMapDecoderDlg message handlers

BOOL CXCCMapDecoderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	/*
	HINSTANCE hin = AfxGetInstanceHandle();
	HRSRC rc = FindResource(hin, MAKEINTRESOURCE(IDR_PALET), "Binary");
	HGLOBAL hgl = LoadResource(NULL, rc);
	int cb_data = SizeofResource(NULL, rc);	
	const byte* data = static_cast<const byte*>(LockResource(hgl));	
	m_palet.write(data, cb_data);
	FreeResource(hgl);
	*/
	
	return true;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXCCMapDecoderDlg::OnPaint() 
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

HCURSOR CXCCMapDecoderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXCCMapDecoderDlg::OnConvert() 
{
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "Maps (*.xmmf)|*.xmmf|", NULL);
	if (IDOK == dlg.DoModal())
		convert(static_cast<string>(dlg.GetPathName()));
}

void CXCCMapDecoderDlg::OnButtonXccHomePage() 
{
	ShellExecute(m_hWnd, "open", "http://xccu.sourceforge.net/", NULL, NULL, SW_SHOW);
}

void CXCCMapDecoderDlg::convert(string _fname)
{
	Ccc_file f(true);
	if (!f.open(_fname))
	{
		CWaitCursor wait;
		Cfname fname = _fname;
		Cxif_key k;
		int error = k.load_key(f.get_data(), f.get_size());
		if (!error)
		{
			if (Cmap_ts_encoder::wrong_version(k))
				MessageBox("Another version of XCC Map Decoder is needed to open this map.", NULL, MB_ICONERROR);
			else if (Cmap_ts_encoder::write_mmx(k))
			{
				fname.set_ext(".mmx");
				char b[MAX_PATH];
				int length = GetShortPathName(static_cast<string>(fname).c_str(), b, MAX_PATH);
				if (length > 0 && length < MAX_PATH)
					fname = to_lower(b);
				string title = fname.get_ftitle();
				strstream ini, pkt;
				Cmix_file_write mmx_f(game_ra2);
				Cmap_ts_encoder::write_map(ini, k, m_palet);
				Cmap_ts_encoder::write_pkt(pkt, k, fname.get_ftitle());
				mmx_f.add_file(title + ".map", Cvirtual_binary(ini.str(), ini.pcount()));
				mmx_f.add_file(title + ".pkt", Cvirtual_binary(pkt.str(), pkt.pcount()));
				error = mmx_f.write().save(fname);
			}
			else
			{
				fname.set_ext(".mpr");				
				Cmap_ts_encoder::write_map(ofstream(static_cast<string>(fname).c_str()), k, m_palet);
			}
		}
		f.close();
		if (error)
			MessageBox("Error converting map.", NULL, MB_ICONERROR);
	}
}

void CXCCMapDecoderDlg::OnDropFiles(HDROP hDropInfo) 
{
	int c_files = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	char fname[MAX_PATH];
	for (int i = 0; i < c_files; i++)
	{
		DragQueryFile(hDropInfo, i, fname, MAX_PATH);
		convert(fname);
	}
	DragFinish(hDropInfo);
}
