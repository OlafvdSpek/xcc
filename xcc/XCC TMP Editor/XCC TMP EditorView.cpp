// XCC TMP EditorView.cpp : implementation of the CXCCTMPEditorView class
//

#include "stdafx.h"
#include "XCC TMP Editor.h"

#include "XCC TMP EditorDoc.h"
#include "XCC TMP EditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCTMPEditorView

IMPLEMENT_DYNCREATE(CXCCTMPEditorView, CScrollView)

BEGIN_MESSAGE_MAP(CXCCTMPEditorView, CScrollView)
	//{{AFX_MSG_MAP(CXCCTMPEditorView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCTMPEditorView construction/destruction

CXCCTMPEditorView::CXCCTMPEditorView()
{
	m_selected = -1;
	m_view_true_height = false;
}

CXCCTMPEditorView::~CXCCTMPEditorView()
{
}

BOOL CXCCTMPEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CXCCTMPEditorView drawing

void CXCCTMPEditorView::load_color_table(const t_palet p)
{
	t_palet32bgr_entry* color_table = reinterpret_cast<t_palet32bgr_entry*>(m_color_table);
	for (int i = 0; i < 256; i++)
	{
		color_table[i].r = p[i].r;
		color_table[i].g = p[i].g;
		color_table[i].b = p[i].b;
	}
}

void CXCCTMPEditorView::load_grey_table(int c_colors)
{
	t_palet32bgr_entry* color_table = reinterpret_cast<t_palet32bgr_entry*>(m_color_table);
	for (int i = 0; i < c_colors; i++)
	{
		color_table[i].r = color_table[i].g = color_table[i].b = i * 255 / (c_colors - 1);
	}
	for (; i < 256; i++)
	{
		color_table[i].r = 255;
		color_table[i].g = color_table[i].b = 0;
	}
}

void CXCCTMPEditorView::draw_image8(const byte* s, int cx_s, int cy_s, CDC* pDC, int x_d, int y_d)
{
	if (!CRect().IntersectRect(m_clip_rect, CRect(CPoint(x_d, y_d), CSize(cx_s, cy_s))))
		return;
	CDC mem_dc;
	mem_dc.CreateCompatibleDC(pDC);
	HBITMAP h_dib;
	dword* p_dib;
	{	
		BITMAPINFO bmi;
		ZeroMemory(&bmi, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = cx_s;
		bmi.bmiHeader.biHeight = -cy_s;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = bmi.bmiHeader.biWidth * -bmi.bmiHeader.biHeight * (bmi.bmiHeader.biBitCount >> 3);
		h_dib = CreateDIBSection(*pDC, &bmi, DIB_RGB_COLORS, reinterpret_cast<void**>(&p_dib), 0, 0);
	}
	void* old_bitmap = mem_dc.SelectObject(h_dib);
	for (int y = 0; y < cy_s; y++)
	{
		for (int x = 0; x < cx_s; x++)
			p_dib[x + cx_s * y] = m_color_table[s[x + cx_s * y]];
	}
	pDC->BitBlt(x_d, y_d, cx_s, cy_s, &mem_dc, 0, 0, SRCCOPY);
	mem_dc.SelectObject(old_bitmap);
	DeleteObject(h_dib);
}

void CXCCTMPEditorView::OnDraw(CDC* pDC)
{
	CXCCTMPEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDC->GetClipBox(&m_clip_rect);
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	int x = 0;
	int y = 0;
	int y_inc = tm.tmHeight;

	t_rect global = pDoc->get_rect(view_true_height());
	{
		int cx = global.r - global.x;
		int cy = global.b - global.y;
		byte* d = new byte[cx * cy];
		pDoc->draw(d, m_selected, view_true_height());
		load_color_table(pDoc->palet());
		draw_image8(d, cx, cy, pDC, 0, y);
		y += cy + y_inc;
		delete[] d;
	}
	
	typedef CXCCTMPEditorDoc::t_map t_map;
		
	int cx = pDoc->header().cx;
	int cy = pDoc->header().cy;
	byte* d = new byte[cx * cy];
	t_map map = pDoc->map();
	int selection_color = 0xffffff;
	CBrush brush(selection_color);
	for (t_map::const_iterator i = map.begin(); i != map.end(); i++)
	{		
		const t_tmp_image_header& header = i->second.header;
		if (i->second.extra_data.data())
		{
			load_color_table(pDoc->palet());
			draw_image8(i->second.extra_data.data(), header.cx_extra, header.cy_extra, pDC, 0, y);
			if (m_selected == i->first)
				pDC->FrameRect(CRect(CPoint(header.x_extra - global.x, header.y_extra - global.y - header.height * (cy / 2)), CSize(header.cx_extra, header.cy_extra)), &brush);
				// pDC->FrameRect(CRect(CPoint(header.x_extra - global.x, header.y_extra - global.y), CSize(header.cx_extra, header.cy_extra)), &brush);
			if (i->second.extra_z_data.data())
			{
				load_grey_table(32);
				draw_image8(i->second.extra_z_data.data(), header.cx_extra, header.cy_extra, pDC, cx + y_inc, y);
			}
			y += header.cy_extra + y_inc;
		}
		decode_tile(i->second.data.data(), d, cx);
		load_color_table(pDoc->palet());
		draw_image8(d, cx, cy, pDC, 0, y);
		if (m_selected == i->first)
		{
			// pDC->FrameRect(CRect(CPoint(header.x - global.x, header.y - global.y), CSize(cx, cy)), &brush);
			/*
			int half_cx = cx >> 1;
			int half_cy = cy >> 1;
			CPoint tl = CPoint(header.x - global.x, header.y - global.y);
			CPen pen(PS_SOLID, 1, selection_color);
			CPen* old_pen = pDC->SelectObject(&pen);
			pDC->MoveTo(tl + CPoint(half_cx, 0));
			pDC->LineTo(tl + CPoint(cx, half_cy));
			pDC->LineTo(tl + CPoint(half_cx, cy));
			pDC->LineTo(tl + CPoint(0, half_cy));
			pDC->LineTo(tl + CPoint(half_cx, 0));
			pDC->SelectObject(old_pen);
			*/
		}
		if (i->second.z_data.data())
		{
			decode_tile(i->second.z_data.data(), d, cx);
			load_grey_table(32);
			draw_image8(d, cx, cy, pDC, cx + y_inc, y);
			x = max(x, 2 * cx + y_inc);
		}
		y += cy + y_inc;
	}
	delete[] d;
	SetScrollSizes(MM_TEXT, CSize(x, y));
}

void CXCCTMPEditorView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize(0, 0));
}

/////////////////////////////////////////////////////////////////////////////
// CXCCTMPEditorView diagnostics

#ifdef _DEBUG
void CXCCTMPEditorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CXCCTMPEditorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CXCCTMPEditorDoc* CXCCTMPEditorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXCCTMPEditorDoc)));
	return (CXCCTMPEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXCCTMPEditorView message handlers


void CXCCTMPEditorView::select(int id)
{
	if (m_selected != id)
	{
		m_selected = id;
		Invalidate();
	}
}

bool CXCCTMPEditorView::view_true_height() const
{
	return m_view_true_height;
}

void CXCCTMPEditorView::view_true_height(bool v)
{
	if (m_view_true_height == v)
		return;
	m_view_true_height = v;
	Invalidate();
}