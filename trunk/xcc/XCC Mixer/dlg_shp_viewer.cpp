// dlg_shp_viewer.cpp : implementation file
//

#include "stdafx.h"
#include "dlg_shp_viewer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cdlg_shp_viewer dialog


Cdlg_shp_viewer::Cdlg_shp_viewer(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(Cdlg_shp_viewer::IDD, pParent, "shp_viewer_dlg")
{
	//{{AFX_DATA_INIT(Cdlg_shp_viewer)
	//}}AFX_DATA_INIT
}


void Cdlg_shp_viewer::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdlg_shp_viewer)
	DDX_Control(pDX, IDC_SLIDER, m_slider);
	DDX_Control(pDX, IDC_IMAGE, m_image);
	DDX_Text(pDX, IDC_FRAME, m_index);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cdlg_shp_viewer, ETSLayoutDialog)
	//{{AFX_MSG_MAP(Cdlg_shp_viewer)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cdlg_shp_viewer message handlers

void Cdlg_shp_viewer::write(Cvideo_decoder* decoder)
{
	m_decoder = decoder;
	if (decoder->palet())
		convert_palet_18_to_24(decoder->palet(), m_palet);
}

static HBITMAP create_bitmap(Cvirtual_image image)
{
	if (image.cx() & 3)
	{
		Cvirtual_image d(NULL, image.cx() + 3 & ~3, image.cy(), image.cb_pixel(), image.palet());
		const byte* r = image.image();
		byte* w = d.image_edit();
		for (int y = 0; y < image.cy(); y++)
		{
			memcpy(w, r, image.cx() * image.cb_pixel());
			memset(w + image.cx(), 0, image.cb_pixel() * (- image.cx() & 3));
			r += image.cx();
			w += d.cx();
		}
		image = d;
	}
	image.increase_color_depth(3);
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

BOOL Cdlg_shp_viewer::OnInitDialog() 
{
	CreateRoot(VERTICAL)
		<< item(IDC_IMAGE, GREEDY)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< item(IDC_FRAME, NORESIZE)
			<< item(IDC_SLIDER, GREEDY)
			<< item(IDC_PLAY, NORESIZE)
			<< item(IDOK, NORESIZE)
			);
	ETSLayoutDialog::OnInitDialog();
	m_slider.SetRange(0, m_decoder->cf() - 1);
	m_frame = 0;
	show_frame();
	m_last_access = 0;
	m_timer_id = SetTimer(1, 100, NULL);
	return true;	
}

void Cdlg_shp_viewer::OnTimer(UINT nIDEvent) 
{
	if (m_timer_id == nIDEvent)
	{
		int frame = m_slider.GetPos();
		int t = time(NULL);
		if (m_frame != frame)
		{
			m_last_access = t;
			m_frame = frame;
		}
		else if (t - m_last_access > 15)
		{
			m_frame++;
			m_frame %= m_decoder->cf();
		}
		else
			return;
		show_frame();
	}
	else
		ETSLayoutDialog::OnTimer(nIDEvent);
}

Cvirtual_image Cdlg_shp_viewer::decode_image(int i) const
{
	Cvirtual_image d;
	d.load(NULL, m_decoder->cx(), m_decoder->cy(), 1, m_palet);
	m_decoder->seek(i);
	m_decoder->decode(d.image_edit());
	return d;
}

void Cdlg_shp_viewer::show_frame()
{
	DeleteObject(m_image.SetBitmap(create_bitmap(decode_image(m_frame))));
	m_index = m_frame;
	m_slider.SetPos(m_frame);
	UpdateData(false);
}

void Cdlg_shp_viewer::OnPlay() 
{
	m_last_access = 0;	
}
