// XCC Map EncoderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XCC Map Encoder.h"
#include "XCC Map EncoderDlg.h"

#include <fstream>
#include <strstream>
#include "cc_file.h"
#include "fname.h"
#include "map_ts_encoder.h"
#include "map_ts_ini_reader.h"
#include "mix_file_write.h"
#include "shp_decode.h"
#include "virtual_image.h"
#include "xcc_map.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCMapEncoderDlg dialog

CXCCMapEncoderDlg::CXCCMapEncoderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXCCMapEncoderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXCCMapEncoderDlg)
	m_create_mmx = FALSE;
	m_export_pkt = TRUE;
	m_create_xmmf = TRUE;
	m_import_pkt = TRUE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXCCMapEncoderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCMapEncoderDlg)
	DDX_Control(pDX, IDC_EXPORT_PKT, mc_export_pkt);
	DDX_Control(pDX, IDC_CREATE_MMX, mc_create_mmx);
	DDX_Control(pDX, IDC_CREATE_XMMF, mc_create_xmmf);
	DDX_Check(pDX, IDC_CREATE_MMX, m_create_mmx);
	DDX_Check(pDX, IDC_EXPORT_PKT, m_export_pkt);
	DDX_Check(pDX, IDC_CREATE_XMMF, m_create_xmmf);
	DDX_Check(pDX, IDC_IMPORT_PKT, m_import_pkt);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXCCMapEncoderDlg, CDialog)
	//{{AFX_MSG_MAP(CXCCMapEncoderDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONVERT, OnConvert)
	ON_BN_CLICKED(IDC_BUTTON_XCC_HOME_PAGE, OnButtonXccHomePage)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_CREATE_MMX, OnCreateMmx)
	ON_BN_CLICKED(IDC_CREATE_XMMF, OnCreateXmmf)
	ON_BN_CLICKED(IDC_IMPORT_PKT, OnImportPkt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCMapEncoderDlg message handlers

BOOL CXCCMapEncoderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXCCMapEncoderDlg::OnPaint() 
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

HCURSOR CXCCMapEncoderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXCCMapEncoderDlg::OnConvert() 
{
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "Maps (*.map;*.mpr)|*.map;*.mpr|", NULL);
	if (IDOK == dlg.DoModal())
		convert(static_cast<string>(dlg.GetPathName()));
}

void CXCCMapEncoderDlg::OnButtonXccHomePage() 
{
	ShellExecute(m_hWnd, "open", "http://xcc.tiberian.com/", NULL, NULL, SW_SHOW);
}

static string get_pkt(string fname, bool export, string description)
{
	Ccc_file pkt_f(true);
	if (!pkt_f.open(fname))
	{
		string s = string(reinterpret_cast<const char*>(pkt_f.get_data()), pkt_f.get_size());
		pkt_f.close();
		return s;
	}
	else
	{
		strstream pkt_f;
		pkt_f << "[MultiMaps]" << endl
			<< "1=" << description << endl
			<< endl
			<< '[' << description << ']' << endl
			<< "Description=" << description << endl
			<< "CD=0,1" << endl
			<< "MinPlayers=2" << endl
			<< "MaxPlayers=2" << endl
			<< "GameMode=standard" << endl;
		if (export)
			file32_write(fname, pkt_f.str(), pkt_f.pcount());
		return string(pkt_f.str(), pkt_f.pcount());
	}
}

void CXCCMapEncoderDlg::convert(string _fname)
{
	Ccc_file f(true);
	if (UpdateData(true) && !f.open(_fname))
	{
		CWaitCursor wait;
		Cfname fname = _fname;
		strstream s;
		Cmap_ts_encoder encoder(s, m_create_xmmf);
		Cmap_ts_ini_reader ir;
		encoder.process(f.get_data(), f.get_size());
		ir.fast(true);
		ir.process(f.get_data(), f.get_size());
		f.close();
		UpdateWindow();
		int error = 0;
		fname.set_ext(".pkt");
		string title = fname.get_ftitle();
		string pkt;
		if (m_import_pkt)
			pkt = get_pkt(fname, m_export_pkt, title);
		if (m_create_xmmf)
		{
			fname.set_ext(".xmmf");
			error = encoder.write_map(fname, string(s.str(), s.pcount()), pkt);
		}
		else if (m_create_mmx)
		{
			Cmix_file_write mmx_f;
			mmx_f.add_file(title + ".map", s.str(), s.pcount());
			mmx_f.add_file(title + ".pkt", pkt.c_str(), pkt.length());
			fname.set_ext(".mmx");
			error = mmx_f.write(fname);
		}
		else
			error = file32_write(_fname, s.str(), s.pcount());			
		if (error)
			MessageBox("Error converting map.", NULL, MB_ICONERROR);
	}
}

void CXCCMapEncoderDlg::OnDropFiles(HDROP hDropInfo) 
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

void CXCCMapEncoderDlg::OnCreateMmx() 
{
	UpdateData(true);
	mc_create_xmmf.EnableWindow(!m_create_mmx);
}

void CXCCMapEncoderDlg::OnCreateXmmf() 
{
	UpdateData(true);
	mc_create_mmx.EnableWindow(!m_create_xmmf);
}

void CXCCMapEncoderDlg::OnImportPkt() 
{
	UpdateData(true);
	mc_export_pkt.EnableWindow(m_import_pkt);
}
