// XCC RA2 Radar CustomizerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XCC RA2 Radar Customizer.h"
#include "XCC RA2 Radar CustomizerDlg.h"

#include <fstream>
#include "file32.h"
#include "mix_file.h"
#include "itc_ini_reader.h"
#include "tmp_ts_file.h"
#include "virtual_binary.h"
#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCRA2RadarCustomizerDlg dialog

CXCCRA2RadarCustomizerDlg::CXCCRA2RadarCustomizerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXCCRA2RadarCustomizerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXCCRA2RadarCustomizerDlg)
	m_blue = 64;
	m_green = 64;
	m_red = 64;
	m_reset = FALSE;
	m_snow = TRUE;
	m_temperate = TRUE;
	m_urban = TRUE;
	m_relative = TRUE;
	m_ra2 = FALSE;
	m_ts = FALSE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXCCRA2RadarCustomizerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCRA2RadarCustomizerDlg)
	DDX_Text(pDX, IDC_BLUE, m_blue);
	DDV_MinMaxInt(pDX, m_blue, 0, 255);
	DDX_Text(pDX, IDC_GREEN, m_green);
	DDV_MinMaxInt(pDX, m_green, 0, 255);
	DDX_Text(pDX, IDC_RED, m_red);
	DDV_MinMaxInt(pDX, m_red, 0, 255);
	DDX_Check(pDX, IDC_RESET, m_reset);
	DDX_Check(pDX, IDC_SNOW, m_snow);
	DDX_Check(pDX, IDC_TEMPERATE, m_temperate);
	DDX_Check(pDX, IDC_URBAN, m_urban);
	DDX_Check(pDX, IDC_RELATIVE, m_relative);
	DDX_Check(pDX, IDC_RA2, m_ra2);
	DDX_Check(pDX, IDC_TS, m_ts);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXCCRA2RadarCustomizerDlg, CDialog)
	//{{AFX_MSG_MAP(CXCCRA2RadarCustomizerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCRA2RadarCustomizerDlg message handlers

BOOL CXCCRA2RadarCustomizerDlg::OnInitDialog()
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

void CXCCRA2RadarCustomizerDlg::OnPaint() 
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

HCURSOR CXCCRA2RadarCustomizerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXCCRA2RadarCustomizerDlg::OnOK() 
{
	if (UpdateData(true))
	{
		if (m_ts)
		{
			if (m_snow)
				customize_radar(game_ts, 0);
			if (m_temperate)
				customize_radar(game_ts, 1);
		}
		if (m_ra2)
		{
			if (m_snow)
				customize_radar(game_ra2, 0);
			if (m_temperate)
				customize_radar(game_ra2, 1);
			if (m_urban)
				customize_radar(game_ra2, 2);
		}
	}
}

int CXCCRA2RadarCustomizerDlg::customize_radar(t_game game, int theater)
{
	CWaitCursor wait;
	const string theater_mname[] = {"snow", "temp", "urb"};

	const Cfname fname = xcc_dirs::get_dir(game) + "iso" + theater_mname[theater] + ".mix";
	if (m_reset)
		return delete_file(fname);
	Cmix_file main_mix;
	main_mix.open(xcc_dirs::get_main_mix(game));
	{
		Ccc_file mix_f(false);
		mix_f.open(fname.get_fname(), main_mix);
		mix_f.extract(fname);
		mix_f.close();
	}
	Cfile32 mix_fe;
	mix_fe.open_edit(fname);
	Cmix_file mix_f;
	mix_f.attach(mix_fe.handle());
	for (int i = 0; i < mix_f.get_c_files(); i++)
	{
		const int id = mix_f.get_id(i);
		Ctmp_ts_file f;
		f.open(id, mix_f);
		if (f.is_valid())
		{
			for (int j = 0; j < f.get_c_tiles(); j++)
			{
				if (!f.get_index()[j])
					continue;
				t_tmp_image_header header = *f.get_image_header(j);
				if (m_relative)
				{
					header.radar_red_left = header.radar_red_left * m_red / 255;
					header.radar_red_right = header.radar_red_right * m_red / 255;
					header.radar_green_left = header.radar_green_left * m_green / 255;
					header.radar_green_right = header.radar_green_right * m_green / 255;
					header.radar_blue_left = header.radar_blue_left * m_blue / 255;
					header.radar_blue_right = header.radar_blue_right * m_blue / 255;
				}
				else
				{
					header.radar_red_left = header.radar_red_right = m_red;
					header.radar_green_left = header.radar_green_right = m_green;
					header.radar_blue_left = header.radar_blue_right = m_blue;
				}
				mix_fe.seek(mix_f.get_offset(id) + f.get_index()[j]);
				mix_fe.write(&header, sizeof(t_tmp_image_header));
			}
		}
		f.close();
	}
	mix_f.detach();
	mix_fe.close();
	main_mix.close();
	return 0;
}
