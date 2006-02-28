#include "stdafx.h"
#include "XCC Map Encoder.h"
#include "XCC Map EncoderDlg.h"

#include <boost/algorithm/string.hpp>
#include <fstream>
#include <strstream>
#include "cc_file.h"
#include "fname.h"
#include "map_ts_encoder.h"
#include "map_ts_ini_reader.h"
#include "mix_file.h"
#include "mix_file_write.h"
#include "pkt_ts_ini_reader.h"
#include "shp_decode.h"
#include "string_conversion.h"
#include "virtual_image.h"
#include "xcc_map.h"
#include "xste.h"

using namespace boost;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CXCCMapEncoderDlg::CXCCMapEncoderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXCCMapEncoderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXCCMapEncoderDlg)
	m_create_mmx = FALSE;
	m_create_xmmf = TRUE;
	m_gamemode = _T("standard");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXCCMapEncoderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCMapEncoderDlg)
	DDX_Control(pDX, IDC_GAMEMODE, mc_gamemode);
	DDX_Control(pDX, IDC_CREATE_MMX, mc_create_mmx);
	DDX_Control(pDX, IDC_CREATE_XMMF, mc_create_xmmf);
	DDX_Check(pDX, IDC_CREATE_MMX, m_create_mmx);
	DDX_Check(pDX, IDC_CREATE_XMMF, m_create_xmmf);
	DDX_Text(pDX, IDC_GAMEMODE, m_gamemode);
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CXCCMapEncoderDlg::OnInitDialog()
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
	ShellExecute(m_hWnd, "open", "http://xccu.sourceforge.net/", NULL, NULL, SW_SHOW);
}

static string get_pkt(string fname, bool export, string title, string description, int max_players, string gamemode)
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
		CXSTE xste;
		if (!xste.open(game_ra2))
		{
			xste.csf_f().set_value("XMM:" + title, Ccsf_file::convert2wstring(description), "");
			if (!xste.write())
				description = "XMM:" + title;
			xste.close();			
		}
		strstream pkt_f;
		pkt_f << "[MultiMaps]" << endl
			<< "1=" << title << endl
			<< endl
			<< '[' << title << ']' << endl
			<< "Description=" << description << endl
			<< "CD=0,1" << endl
			<< "MinPlayers=2" << endl
			<< "MaxPlayers=" << max_players << endl
			<< "GameMode=" << gamemode << endl;
		if (export)
			file32_write(fname, pkt_f.str(), pkt_f.pcount());
		return string(pkt_f.str(), pkt_f.pcount());
	}
}

void CXCCMapEncoderDlg::convert(string _fname, Ccc_file& f)
{
	Cfname fname = _fname;
	strstream s;
	Cmap_ts_ini_reader ir;
	ir.fast(true);
	ir.process(f.get_data(), f.get_size());
	Cmap_ts_encoder encoder(s, m_create_xmmf);
	string description = ir.get_basic_data().name;
	if (description.empty())
		description = fname.get_ftitle();
	Cmap_ts_encoder::t_header header;
	header.description = description;
	header.gamemode = m_create_mmx ? static_cast<string>(m_gamemode) : "";
	header.cx = ir.get_map_data().size_right;
	header.cy = ir.get_map_data().size_bottom;
	header.cmax_players = ir.max_players();
	encoder.header(header);
	encoder.process(f.get_data(), f.get_size());
	if (m_create_xmmf)
		encoder.encode(m_palet);
	f.close();
	UpdateWindow();
	int error = 0;
	if (m_create_mmx)
	{
		char b[MAX_PATH];
		int length = GetShortPathName(static_cast<string>(fname).c_str(), b, MAX_PATH);
		if (length > 0 && length < MAX_PATH)
			fname = to_lower_copy(string(b));
	}
	string title = fname.get_ftitle();
	if (m_create_xmmf)
	{
		fname.set_ext(".xmmf");
		error = encoder.write_map(fname, string(s.str(), s.pcount()));
	}
	else if (m_create_mmx)
	{
		fname.set_ext(".pkt");
		string pkt = get_pkt(fname, false, title, description, ir.max_players(), static_cast<string>(m_gamemode));
		Cmix_file_write mmx_f(game_ra2);
		mmx_f.add_file(title + ".map", Cvirtual_binary(s.str(), s.pcount()));
		mmx_f.add_file(title + ".pkt", Cvirtual_binary(pkt.c_str(), pkt.length()));
		fname.set_ext(".mmx");
		error = mmx_f.write().save(fname);
	}
	else
		error = file32_write(_fname, s.str(), s.pcount());			
	if (error)
		MessageBox("Error writing map.", NULL, MB_ICONERROR);
}

void CXCCMapEncoderDlg::convert(string _fname)
{
	Ccc_file f(true);
	if (UpdateData(true) && !f.open(_fname))
	{
		CWaitCursor wait;
		if (f.get_file_type() == ft_mix)
		{
			Cmix_file mix_f;
			mix_f.load(f);
			Cfname fname = _fname;
			fname.set_ext(".map");
			Ccc_file pkt_f(true);
			if (!pkt_f.open(fname.get_ftitle() + ".pkt", mix_f))
			{
				Cpkt_ts_ini_reader ir;
				ir.process(pkt_f.get_data(), pkt_f.get_size());
				typedef Cpkt_ts_ini_reader::t_map_list t_map_list;
				const t_map_list& map_list = ir.get_map_list();
				// ir.write_report(ofstream("d:/temp/packs.html", ios::out | ios::app));
				for (t_map_list::const_iterator i = map_list.begin(); i != map_list.end(); i++)
				{
					Ccc_file ini_f(true);
					fname.set_title(i->first);
					if (!ini_f.open(fname.get_fname(), mix_f))
						convert(fname, ini_f);
				}
				pkt_f.close();
			}
			mix_f.close();
			f.close();
		}
		else
			convert(_fname, f);
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
	mc_gamemode.EnableWindow(m_create_mmx);
}
