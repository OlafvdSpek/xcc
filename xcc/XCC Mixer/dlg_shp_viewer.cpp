// dlg_shp_viewer.cpp : implementation file
//

#include "stdafx.h"
#include "dlg_shp_viewer.h"

#include "shp_decode.h"

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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cdlg_shp_viewer message handlers

void Cdlg_shp_viewer::write(Cvirtual_binary v, const t_palet palet)
{
	m_f.load(v);
	convert_palet_18_to_24(palet, m_palet);
	m_combine_shadows = combine_shadows();
}

static HBITMAP create_bitmap(Cvirtual_image image)
{
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
			<< item(IDOK, NORESIZE)
			);
	ETSLayoutDialog::OnInitDialog();
	m_slider.SetRange(0, c_frames() - 1);
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
			m_frame %= c_frames();
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
	const int global_cx = m_f.get_cx() + 3 & ~3;
	const int global_cy = m_f.get_cy();
	d.load(NULL, global_cx, global_cy, 1, m_palet);
	memset(d.image_edit(), 0, global_cx * global_cy);
	bool shadow = false;
	while (true)
	{
		const int cx = m_f.get_cx(i);
		const int cy = m_f.get_cy(i);
		const byte* r;
		Cvirtual_binary t;
		if (m_f.is_compressed(i))
		{
			decode3(m_f.get_image(i), t.write_start(cx * cy), cx, cy);
			r = t.data();
		}
		else
			r = m_f.get_image(i);
		byte* w = d.image_edit();
		w += m_f.get_x(i) + global_cx * m_f.get_y(i);
		for (int y = 0; y < cy; y++)
		{
			if (shadow)
			{
				for (int x = 0; x < cx; x++)
				{
					if (*r++)
						w[x] = 4;
				}
			}
			else
			{
				memcpy(w, r, cx);
				r += cx;
			}
			w += global_cx;
		}
		if (!m_combine_shadows || shadow)
			break;
		i += c_frames();
		shadow = true;
	}
	return d;
}

void Cdlg_shp_viewer::show_frame()
{
	DeleteObject(m_image.SetBitmap(create_bitmap(decode_image(m_frame))));
	m_index = m_frame;
	m_slider.SetPos(m_frame);
	UpdateData(false);
}

bool Cdlg_shp_viewer::combine_shadows() const
{
	const int c_frames = m_f.get_c_images();
	if (c_frames & 1)
		return false;
	for (int i = c_frames >> 1; i < c_frames; i++)
	{
		const int cx = m_f.get_cx(i);
		const int cy = m_f.get_cy(i);
		const byte* r;
		Cvirtual_binary t;
		if (m_f.is_compressed(i))
		{
			decode3(m_f.get_image(i), t.write_start(cx * cy), cx, cy);
			r = t.data();
		}
		else
			r = m_f.get_image(i);
		const byte* r_end = r + cx * cy;
		while (r < r_end)
		{
			if (*r++ > 1)
				return false;
		}
	}
	return true;
}

int Cdlg_shp_viewer::c_frames() const
{
	return m_f.get_c_images() >> (m_combine_shadows ? 1 : 0);
}

