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
	m_blue = 128;
	m_green = 128;
	m_red = 128;
	m_reset = FALSE;
	m_temperate = TRUE;
	m_urban = TRUE;
	m_relative = TRUE;
	m_ra2 = FALSE;
	m_ts = FALSE;
	m_snow = TRUE;
	m_lock = TRUE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXCCRA2RadarCustomizerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCRA2RadarCustomizerDlg)
	DDX_Control(pDX, IDC_URBAN_PREVIEW, m_urban_preview_control);
	DDX_Control(pDX, IDC_TEMPERATE_PREVIEW, m_temperate_preview_control);
	DDX_Control(pDX, IDC_SNOW_PREVIEW, m_snow_preview_control);
	DDX_Text(pDX, IDC_BLUE, m_blue);
	DDV_MinMaxInt(pDX, m_blue, 0, 255);
	DDX_Text(pDX, IDC_GREEN, m_green);
	DDV_MinMaxInt(pDX, m_green, 0, 255);
	DDX_Text(pDX, IDC_RED, m_red);
	DDV_MinMaxInt(pDX, m_red, 0, 255);
	DDX_Check(pDX, IDC_RESET, m_reset);
	DDX_Check(pDX, IDC_TEMPERATE, m_temperate);
	DDX_Check(pDX, IDC_URBAN, m_urban);
	DDX_Check(pDX, IDC_RELATIVE, m_relative);
	DDX_Check(pDX, IDC_RA2, m_ra2);
	DDX_Check(pDX, IDC_TS, m_ts);
	DDX_Check(pDX, IDC_SNOW, m_snow);
	DDX_Check(pDX, IDC_LOCK, m_lock);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXCCRA2RadarCustomizerDlg, CDialog)
	//{{AFX_MSG_MAP(CXCCRA2RadarCustomizerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_BLUE, OnChangeBlue)
	ON_EN_CHANGE(IDC_GREEN, OnChangeGreen)
	ON_EN_CHANGE(IDC_RED, OnChangeRed)
	ON_BN_CLICKED(IDC_RELATIVE, OnRelative)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCRA2RadarCustomizerDlg message handlers

HBITMAP CXCCRA2RadarCustomizerDlg::create_bitmap(Cvirtual_image image)
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

void CXCCRA2RadarCustomizerDlg::load_image(int id, Cvirtual_image& image)
{
	HINSTANCE hin = AfxGetInstanceHandle();
	HRSRC rc = FindResource(hin, MAKEINTRESOURCE(id), "PNG");
	HGLOBAL hgl = LoadResource(NULL, rc);
	image.load(Cvirtual_binary(static_cast<const byte*>(LockResource(hgl)), SizeofResource(NULL, rc)));
	FreeResource(hgl);
}

BOOL CXCCRA2RadarCustomizerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	/*
	m_snow_preview.load("c:/temp/snow_preview.png");
	m_snow_preview_mask.load("c:/temp/snow_preview_mask.png");
	m_temperate_preview.load("c:/temp/temperate_preview.png");
	m_temperate_preview_mask.load("c:/temp/temperate_preview_mask.png");
	m_urban_preview.load("c:/temp/urban_preview.png");
	m_urban_preview_mask.load("c:/temp/urban_preview_mask.png");
	*/
	load_image(IDR_SNOW_PREVIEW, m_snow_preview);
	load_image(IDR_SNOW_PREVIEW_MASK, m_snow_preview_mask);
	load_image(IDR_TEMPERATE_PREVIEW, m_temperate_preview);
	load_image(IDR_TEMPERATE_PREVIEW_MASK, m_temperate_preview_mask);
	load_image(IDR_URBAN_PREVIEW, m_urban_preview);
	load_image(IDR_URBAN_PREVIEW_MASK, m_urban_preview_mask);
	update_previews();	
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

void CXCCRA2RadarCustomizerDlg::update_previews()
{
	Cvirtual_binary d;
	m_snow_preview_control.SetBitmap(create_bitmap(scale_image(m_snow_preview, m_snow_preview_mask, d)));
	// d.export("c:/temp/snow_preview_mask.png");
	m_temperate_preview_control.SetBitmap(create_bitmap(scale_image(m_temperate_preview, m_temperate_preview_mask, d)));
	// d.export("c:/temp/temperate_preview_mask.png");
	m_urban_preview_control.SetBitmap(create_bitmap(scale_image(m_urban_preview, m_urban_preview_mask, d)));
	// d.export("c:/temp/urban_preview_mask.png");
}

Cvirtual_image CXCCRA2RadarCustomizerDlg::scale_image(Cvirtual_image image, Cvirtual_image mask, Cvirtual_binary& d)
{
	if (!m_reset)
	{
		/*
		Cvirtual_image mask2;
		t_palet palet;
		memset(palet, 0, sizeof(t_palet));
		memset(palet + 1, 255, 3);
		mask2.load(NULL, image.cx(), image.cy(), 1, palet);
		byte* w = mask2.image_edit();
		*/
		t_palet_entry* r = reinterpret_cast<t_palet_entry*>(image.image_edit());
		const byte* r_mask = mask.image();
		for (int i = 0; i < image.cx() * image.cy(); i++)
		{
			// *w++ = r->r != r_mask->r || r->g != r_mask->g || r->b != r_mask->b;
			if (*r_mask++)
			{
				if (m_relative)
				{
					r->r = r->r * m_red / 255;
					r->g = r->g * m_green / 255;
					r->b = r->b * m_blue / 255;
				}
				else
				{
					r->r = m_red;
					r->g = m_green;
					r->b = m_blue;
				}
			}
			r++;
		}
		/*
		Cvirtual_file f;
		mask2.save_as_png(f);
		d = f.read();
		*/
	}
	return image;
}

void CXCCRA2RadarCustomizerDlg::OnChangeRed() 
{
	if (UpdateData(true))
	{
		if (m_lock)
		{
			m_green = m_blue = m_red;
			UpdateData(false);
		}
		update_previews();
	}
}

void CXCCRA2RadarCustomizerDlg::OnChangeGreen() 
{
	if (UpdateData(true))
	{
		if (m_lock)
		{
			m_red = m_blue = m_green;
			UpdateData(false);
		}
		update_previews();
	}
}

void CXCCRA2RadarCustomizerDlg::OnChangeBlue() 
{
	if (UpdateData(true))
	{
		if (m_lock)
		{
			m_red = m_green = m_blue;
			UpdateData(false);
		}
		update_previews();
	}
}

void CXCCRA2RadarCustomizerDlg::OnRelative() 
{
	if (UpdateData(true))
		update_previews();
}

void CXCCRA2RadarCustomizerDlg::OnReset() 
{
	if (UpdateData(true))
		update_previews();
}
