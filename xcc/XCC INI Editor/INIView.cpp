// INIView.cpp : implementation of the CINIView class
//

#include "stdafx.h"
#include "XCC INI Editor.h"

#include "INIDoc.h"
#include "INIView.h"
#include "inichildfrm.h"

#include "multi_line.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CINIView

IMPLEMENT_DYNCREATE(CINIView, CCrystalEditView)

BEGIN_MESSAGE_MAP(CINIView, CCrystalEditView)
	//{{AFX_MSG_MAP(CINIView)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CINIView construction/destruction

CINIView::CINIView()
{
	SetSelectionMargin(false);
}

CINIView::~CINIView()
{
}

BOOL CINIView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CCrystalEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CINIView diagnostics

#ifdef _DEBUG
void CINIView::AssertValid() const
{
	CCrystalEditView::AssertValid();
}

void CINIView::Dump(CDumpContext& dc) const
{
	CCrystalEditView::Dump(dc);
}

CINIDoc* CINIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CINIDoc)));
	return (CINIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CINIView message handlers

void CINIView::OnInitialUpdate() 
{
	CCrystalEditView::OnInitialUpdate();
	
	LOGFONT lf;
	GetDocument()->m_font.GetLogFont(&lf);
	SetFont(lf);
}

void CINIView::DrawSingleLine(CDC *pDC, const CRect &rect, int nLineIndex)
{
	/*
	CCrystalEditView::DrawSingleLine(pDC, rect, nLineIndex);
	return;
	*/
	COLORREF bk_color = RGB(255, 255, 255);
	if (nLineIndex == -1)
	{
		pDC->FillRect(rect, &CBrush(bk_color));
		return;
	}
	const CCrystalTextBuffer::SLineInfo& line = LocateTextBuffer()->GetLine(nLineIndex);
	const string& text = line.text();			
	void* old_font = pDC->SelectObject(GetFont());
	int old_bk_mode = pDC->SetBkMode(TRANSPARENT);
	const COLORREF te_color[] = {RGB(0, 0, 0), RGB(0, 0, 255), RGB(0, 0, 0), RGB(0, 0, 255), RGB(0, 0, 0), RGB(0, 0, 255), RGB(0, 0, 0), RGB(0, 64, 64), RGB(0, 128, 0), RGB(0, 0, 0)};
	// const COLORREF active_bk_color = RGB(255, 255, 0);
	const COLORREF error_bk_color = RGB(255, 192, 192);
	const COLORREF header_bk_color = RGB(192, 192, 255);
	if (line.cc_index(CCrystalTextBuffer::SLineInfo::te_error))
		bk_color = error_bk_color;
	else if (line.cc_index(CCrystalTextBuffer::SLineInfo::te_header_name))
		bk_color = header_bk_color;
	if (nLineIndex == GetCursorPos().y)
		bk_color &= RGB(255, 255, 0);
	pDC->FillRect(rect, &CBrush(bk_color));
	int c = 0;
	for (int te = 0; te < CCrystalTextBuffer::SLineInfo::te_eol; te++)
	{
		int cc = line.cc_index(te);
		if (cc)
		{
			pDC->SetTextColor(te_color[te]);
			string b = text.substr(line.c_index(te), cc);
			for (int a = 0; a < b.length(); )
			{
				int t = b.find('\t', a);
				if (t == string::npos)
				{
					pDC->TextOut(rect.left + (c - m_nOffsetChar) * GetCharWidth(), rect.top, b.substr(a).c_str());
					c += b.length() - a;
					break;
				}
				pDC->TextOut((c - m_nOffsetChar) * GetCharWidth(), rect.top, b.substr(a, t - a).c_str());
				c += t - a + GetTabSize();
				c &= ~(GetTabSize() - 1);
				a = t + 1;
			}
		}
	}
	pDC->SetBkMode(old_bk_mode);
	pDC->SelectObject(old_font);
}
