// INIView.cpp : implementation of the CINIView class
//

#include "stdafx.h"
#include "XCC INI Editor.h"

#include "INIDoc.h"
#include "INIView.h"
#include "inichildfrm.h"

#include <fstream>
#include "lazy_ini_reader.h"
#include "multi_line.h"
#include "string_conversion.h"

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
	ON_COMMAND(ID_VIEW_SYNTAX_HIGHLIGHTING, OnViewSyntaxHighlighting)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SYNTAX_HIGHLIGHTING, OnUpdateViewSyntaxHighlighting)
	ON_COMMAND(ID_VIEW_SELECTION_MARGIN, OnViewSelectionMargin)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SELECTION_MARGIN, OnUpdateViewSelectionMargin)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_VIEW_REPORT, OnViewReport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CINIView construction/destruction

CINIView::CINIView()
{
	SetSelectionMargin(false);
	m_syntax_highlighting = true;
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
	if (!m_syntax_highlighting)
	{
		CCrystalEditView::DrawSingleLine(pDC, rect, nLineIndex);
		return;
	}
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

void CINIView::OnViewSyntaxHighlighting() 
{
	m_syntax_highlighting = !m_syntax_highlighting;
	Invalidate();
}

void CINIView::OnUpdateViewSyntaxHighlighting(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_syntax_highlighting);
}

void CINIView::OnViewSelectionMargin() 
{
	SetSelectionMargin(!GetSelectionMargin());
}

void CINIView::OnUpdateViewSelectionMargin(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetSelectionMargin());
}

void CINIView::find_section(int l) 
{
	CPoint pt(0, l);
	SetCursorPos(pt);
	ScrollToLine(pt.y);
	UpdateCaret();
	SetSelection(pt, pt);
}


COLORREF CINIView::GetColor(int nColorIndex)
{
	switch (nColorIndex)
	{
	default:
		return super::GetColor(nColorIndex);
	}
}

#if 0
typedef set<Clazy_key_map::t_vt> t_tset;
typedef map<string, t_tset> t_tmap;
typedef Clazy_ini_reader::t_map t_smap;

void filter(t_smap smap)
{
	typedef map<string, int> t_cmap;

	t_cmap cmap;
	for (t_smap::const_iterator si = smap.begin(); si != smap.end(); si++)
	{
		for (Clazy_key_map::const_iterator ki = si->second.begin(); ki != si->second.end(); ki++)
		{
			cmap[ki->first]++;
		}
	}
	int key_max = INT_MIN;
	string key_name;
	for (t_cmap::const_iterator ci = cmap.begin(); ci != cmap.end(); ci++)
	{
		if (ci->second > key_max)
		{
			key_max = ci->second;
			key_name = ci->first;

		}
	}	
	for (si = smap.begin(); si != smap.end(); si++)
	{
		if (si->second.find(key_name) == si->second.end())
			remove_key(

	}
}

void CINIView::analyse()
{
	ofstream f("d:/temp/report.txt");
	CCrystalTextBuffer& b = *LocateTextBuffer();
	Clazy_ini_reader ir;
	for (int l = 0; l < b.GetLineCount(); l++)
	{
		const CCrystalTextBuffer::SLineInfo& line = LocateTextBuffer()->GetLine(l);
		ir.process_line(line.text());
	}
	t_tmap tmap;
	for (Clazy_ini_reader::const_iterator si = ir.begin(); si != ir.end(); si++)
	{
		bool list = si->second.list();
		f << "[S_" << si->first << "]" << endl
			<< "List=" << btoa(list) << endl;
		for (Clazy_key_map::const_iterator ki = si->second.begin(); ki != si->second.end(); ki++)
		{
			Clazy_key_map::t_vt vt = Clazy_key_map::st(ki->second);
			tmap[ki->first].insert(vt);
			f << "K_" << ki->first << "=" << Clazy_key_map::vt_name[vt] << endl;
		}
		f << endl;
	}
	filter(ir.map());
	/*
	for (ki = tmap.begin(); ki != tmap.end(); ki++)
	{
		typedef set<string> t_sset;
		int max_keys = 0;
		t_sset sset;
		for (Clazy_ini_reader::const_iterator si = ir.begin(); si != ir.end(); si++)
		{
			if (si->second.map().find(ki->first) != si->second.map().end())
			{
				max_keys = max(max_keys, si->second.map().size());
				sset.insert(si->first);
			}
		}
	}
	*/
	f << "[Keys]" << endl;
	for (t_tmap::const_iterator ki = tmap.begin(); ki != tmap.end(); ki++)
	{
		f << "K_" << ki->first << "=";
		for (t_tset::const_iterator ti = ki->second.begin(); ti != ki->second.end(); ti++)
		{
			f << Clazy_key_map::vt_name[*ti] << ", ";
		}
		f << endl;
	}
	f << endl;
}
#endif 

void CINIView::OnViewReport() 
{
	// analyse();
}