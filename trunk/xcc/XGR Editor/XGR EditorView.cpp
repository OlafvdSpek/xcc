// XGR EditorView.cpp : implementation of the CXGREditorView class
//

#include "stdafx.h"
#include "XGR Editor.h"

#include "XGR EditorDoc.h"
#include "XGR EditorView.h"

#include <strstream>
#include "dlg_edit_key.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXGREditorView

IMPLEMENT_DYNCREATE(CXGREditorView, CListView)

BEGIN_MESSAGE_MAP(CXGREditorView, CListView)
	//{{AFX_MSG_MAP(CXGREditorView)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	ON_COMMAND(ID_POPUP_OPEN, OnPopupOpen)
	ON_UPDATE_COMMAND_UI(ID_POPUP_OPEN, OnUpdatePopupOpen)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXGREditorView construction/destruction

CXGREditorView::CXGREditorView()
{
	m_buffer_w = 0;
}

CXGREditorView::~CXGREditorView()
{
}

BOOL CXGREditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_NOCOLUMNHEADER | LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

static int c_colums = 2;

void CXGREditorView::OnInitialUpdate()
{
	const char* column_label[] = {"Name", "Value"};
	CListCtrl& lc = GetListCtrl();
	lc.SetExtendedStyle(lc.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	for (int i = 0; i < c_colums; i++)
		lc.InsertColumn(i, column_label[i], LVCFMT_LEFT, -1, i);
	CListView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CXGREditorView message handlers

static int section_size(const Cgr_ini_reader::Csection& section)
{
	int size = 0;
	for (Cgr_ini_reader::Csection::t_sections::const_iterator i = section.sections.begin(); i != section.sections.end(); i++)
		size += 1 + section_size(*i);
	return size;
}

static int sections_size(const Cgr_ini_reader::t_sections& sections)
{
	int size = 0;
	for (Cgr_ini_reader::t_sections::const_iterator i = sections.begin(); i != sections.end(); i++)
		size += 1 + section_size(i->second.second);
	return size;
}

void CXGREditorView::insert_section(int l, Cgr_ini_reader::Csection& section)
{
	CListCtrl& lc = GetListCtrl();
	for (Cgr_ini_reader::Csection::t_sections::iterator i = section.sections.begin(); i != section.sections.end(); i++)
	{
		int id = m_map.empty() ? 0 : m_map.rbegin()->first + 1;
		m_map[id] = t_map_entry(l, &*i);
		lc.SetItemData(lc.InsertItem(lc.GetItemCount(), LPSTR_TEXTCALLBACK), id);
		insert_section(l + 1, *i);
	}
}

void CXGREditorView::open(const string& name, const Cvirtual_binary& d)
{
	CWaitCursor wait;
	close();
	m_ini.import(d);
	m_ini_name = name;
	CListCtrl& lc = GetListCtrl();
	Cgr_ini_reader::t_sections& sections = m_ini.sections();
	lc.SetItemCount(sections_size(sections));
	for (Cgr_ini_reader::t_sections::iterator i = sections.begin(); i != sections.end(); i++)
	{
		int index = lc.InsertItem(lc.GetItemCount(), i->first.c_str());
		lc.SetItemText(index, 1, i->second.first.c_str());
		lc.SetItemData(index, -1);
		insert_section(1, i->second.second);
	}
	{
		for (int i = 0; i < c_colums; i++)
			lc.SetColumnWidth(i, LVSCW_AUTOSIZE);
	}
}

void CXGREditorView::save()
{
	assert(!m_ini_name.empty());
	strstream os;
	m_ini.export(os);
	os.gcount();
	GetDocument()->insert(m_ini_name, Cvirtual_binary(os.str(), os.pcount()));
}

void CXGREditorView::close()
{
	CListCtrl& lc = GetListCtrl();
	lc.DeleteAllItems();
	m_map.clear();
}

void CXGREditorView::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	const t_map_entry& e = m_map.find(pDispInfo->item.lParam)->second;
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		m_buffer[m_buffer_w] = string(e.l << 2, ' ') + e.section->name;
		break;
	case 1:
		m_buffer[m_buffer_w] = e.section->value;
		break;
	default:
		m_buffer[m_buffer_w].erase();
	}
	pDispInfo->item.pszText = const_cast<char*>(m_buffer[m_buffer_w].c_str());
	m_buffer_w--;
	if (m_buffer_w < 0)
		m_buffer_w += 4;
	*pResult = 0;
}

void CXGREditorView::OnPopupOpen() 
{
	CListCtrl& lc = GetListCtrl();
	int index = lc.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
	t_map::iterator i = m_map.find(lc.GetItemData(index));
	if (i == m_map.end())
		return;
	t_map_entry& e = i->second;
	Cdlg_edit_key dlg;
	dlg.set_name(e.section->name);
	dlg.set_value(e.section->value);
	if (IDOK == dlg.DoModal())
	{
		e.section->value = dlg.get_value();
		lc.Update(index);
		save();
	}
}

void CXGREditorView::OnUpdatePopupOpen(CCmdUI* pCmdUI) 
{
	CListCtrl& lc = GetListCtrl();
	int index = lc.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
	pCmdUI->Enable(index != -1 && m_map.find(lc.GetItemData(index)) != m_map.end());
}

void CXGREditorView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnPopupOpen();	
	*pResult = 0;
}