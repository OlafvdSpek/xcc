// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "XCC TMP Editor.h"

#include "XCC TMP EditorDoc.h"
#include "LeftView.h"

#include "string_conversion.h"
#include "properties_dlg.h"
#include "virtual_image.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CListView)

BEGIN_MESSAGE_MAP(CLeftView, CListView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(TVN_GETDISPINFO, OnGetdispinfo)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_POPUP_DELETE, OnPopupDelete)
	ON_UPDATE_COMMAND_UI(ID_POPUP_DELETE, OnUpdatePopupDelete)
	ON_COMMAND(ID_POPUP_INSERT, OnPopupInsert)
	ON_UPDATE_COMMAND_UI(ID_POPUP_INSERT, OnUpdatePopupInsert)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_COMMAND(ID_POPUP_COPY_EXTRA_IMAGE, OnPopupCopyExtraImage)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_EXTRA_IMAGE, OnUpdatePopupCopyExtraImage)
	ON_COMMAND(ID_POPUP_PASTE_EXTRA_IMAGE, OnPopupPasteExtraImage)
	ON_UPDATE_COMMAND_UI(ID_POPUP_PASTE_EXTRA_IMAGE, OnUpdatePopupPasteExtraImage)
	ON_COMMAND(ID_POPUP_LOADASPCX_EXTRAIMAGE, OnPopupLoadaspcxExtraimage)
	ON_UPDATE_COMMAND_UI(ID_POPUP_LOADASPCX_EXTRAIMAGE, OnUpdatePopupLoadaspcxExtraimage)
	ON_COMMAND(ID_POPUP_LOADASPCX_IMAGE, OnPopupLoadaspcxImage)
	ON_UPDATE_COMMAND_UI(ID_POPUP_LOADASPCX_IMAGE, OnUpdatePopupLoadaspcxImage)
	ON_COMMAND(ID_POPUP_SAVEASPCX_EXTRAIMAGE, OnPopupSaveaspcxExtraimage)
	ON_COMMAND(ID_POPUP_SAVEASPCX_IMAGE, OnPopupSaveaspcxImage)
	ON_COMMAND(ID_POPUP_PROPERTIES, OnPopupProperties)
	ON_UPDATE_COMMAND_UI(ID_POPUP_PROPERTIES, OnUpdatePopupProperties)
	ON_COMMAND(ID_POPUP_COPY_COMPLETE, OnPopupCopyComplete)
	ON_COMMAND(ID_POPUP_PASTE_COMPLETE, OnPopupPasteComplete)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	ON_COMMAND(ID_POPUP_COPY_IMAGE, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_IMAGE, OnUpdateEditCopy)
	ON_COMMAND(ID_POPUP_PASTE_IMAGE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_POPUP_PASTE_IMAGE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_POPUP_SAVEASPCX_IMAGE, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_POPUP_SAVEASPCX_EXTRAIMAGE, OnUpdatePopupCopyExtraImage)
	ON_COMMAND(ID_POPUP_LOAD_COMPLETE, OnPopupLoadComplete)
	ON_COMMAND(ID_POPUP_SAVE_COMPLETE, OnPopupSaveComplete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	m_buffer_w = 0;
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CXCCTMPEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

static int c_colums = 6;

void CLeftView::OnInitialUpdate()
{
	char* column_label[] = {"X", "Y", "Extra data", "Height", "Terrain type", "Ramp type"};
	int column_alignment[] = {LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT};

	CListCtrl& lc = GetListCtrl();
	ListView_SetExtendedListViewStyleEx(lc.m_hWnd, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (int i = 0; i < c_colums; i++)
		lc.InsertColumn(i, column_label[i], column_alignment[i], -1, i);

	sync();
	autosize_colums();
	CListView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CListView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CXCCTMPEditorDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXCCTMPEditorDoc)));
	return (CXCCTMPEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	CListCtrl& lc = GetListCtrl();
	int id = lc.GetItemData(pDispInfo->item.iItem);	
	m_buffer[m_buffer_w].erase();
	const CXCCTMPEditorDoc::t_map_entry& e = GetDocument()->map().find(id)->second;
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		m_buffer[m_buffer_w] = n(e.header.x);
		break;
	case 1:
		m_buffer[m_buffer_w] = n(e.header.y);
		break;
	case 2:
		m_buffer[m_buffer_w] = n(e.header.has_extra_data);
		break;
	case 3:
		m_buffer[m_buffer_w] = n(e.header.height);
		break;
	case 4:
		m_buffer[m_buffer_w] = n(e.header.terrain_type);
		break;
	case 5:
		m_buffer[m_buffer_w] = n(e.header.ramp_type);
		break;
	}
	pDispInfo->item.pszText = const_cast<char*>(m_buffer[m_buffer_w].c_str());
	m_buffer_w--;
	if (m_buffer_w < 0)
		m_buffer_w += 4;
	*pResult = 0;
}

void CLeftView::autosize_colums()
{
	SetRedraw(false);
	CListCtrl& lc = GetListCtrl();
	for (int i = 0; i < c_colums; i++)
		lc.SetColumnWidth(i, LVSCW_AUTOSIZE);
	SetRedraw(true);
	Invalidate();
}

void CLeftView::sync()
{
	typedef CXCCTMPEditorDoc::t_map t_map;
		
	SetRedraw(false);
	CListCtrl& lc = GetListCtrl();
	const t_map& map = GetDocument()->map();
	for (t_map::const_iterator i = map.begin(); i != map.end(); i++)
	{
		LVFINDINFO lvf;
		lvf.flags = LVFI_PARAM;
		lvf.lParam = i->first;
		if (lc.FindItem(&lvf, -1) != -1)
			continue;
		int index = lc.InsertItem(lc.GetItemCount(), LPSTR_TEXTCALLBACK);
		lc.SetItemData(index, i->first);
	}
	for (int j = 0; j < lc.GetItemCount(); j++)
	{
		if (map.find(lc.GetItemData(j)) == map.end())
			lc.DeleteItem(j--);
	}
	SetRedraw(true);
	Invalidate();
	m_sort_column = -1;
}

void CLeftView::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_LEFT_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CLeftView::OnEditCopy() 
{
	GetDocument()->get_image(get_current_id()).set_clipboard();
	/*
	CXCCTMPEditorDoc* pDoc = GetDocument();
	const CXCCTMPEditorDoc::t_map_entry& e = pDoc->map().find(get_current_id())->second;
	int cx = pDoc->header().cx;
	int cy = pDoc->header().cy;
	byte* d = new byte[cx * cy];
	decode_tile(e.data.data(), d, cx);
	Cvirtual_image image;
	image.load(d, cx, cy, 1, pDoc->palet());
	delete[] d;
	image.set_clipboard();
	*/
}

void CLeftView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(get_current_id() != -1);
}

void CLeftView::OnPopupCopyExtraImage() 
{
	GetDocument()->get_extra_image(get_current_id()).set_clipboard();
	/*
	CXCCTMPEditorDoc* pDoc = GetDocument();
	const CXCCTMPEditorDoc::t_map_entry& e = pDoc->map().find(get_current_id())->second;
	Cvirtual_image image;
	image.load(e.extra_data.data(), e.header.cx_extra, e.header.cy_extra, 1, pDoc->palet());
	image.set_clipboard();
	*/
}

void CLeftView::OnUpdatePopupCopyExtraImage(CCmdUI* pCmdUI) 
{
	int id = get_current_id();
	pCmdUI->Enable(id != -1 && GetDocument()->map().find(id)->second.extra_data.data());
}

void CLeftView::OnEditPaste() 
{
	Cvirtual_image image;
	if (image.get_clipboard())
		return;
	if (image.cb_pixel() == 3)
		image.decrease_color_depth(GetDocument()->palet());
	GetDocument()->set_image(get_current_id(), image);
	/*
	Cvirtual_image image;
	CXCCTMPEditorDoc* pDoc = GetDocument();
	int cx = pDoc->header().cx;
	int cy = pDoc->header().cy;
	if (image.get_clipboard() || image.cx() != cx || image.cy() != cy)
		return;
	if (image.cb_pixel() == 3)
		image.decrease_color_depth(GetDocument()->palet());
	CXCCTMPEditorDoc::t_map_entry& e = pDoc->map_edit().find(get_current_id())->second;
	encode_tile(image.image(), e.data.data_edit(), cx);
	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);
	*/
}

void CLeftView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(get_current_id() != -1 && IsClipboardFormatAvailable(CF_DIB));
}

void CLeftView::OnPopupPasteExtraImage() 
{
	Cvirtual_image image;
	if (image.get_clipboard())
		return;
	if (image.cb_pixel() == 3)
		image.decrease_color_depth(GetDocument()->palet());
	GetDocument()->set_extra_image(get_current_id(), image);
	/*
	Cvirtual_image image;
	CXCCTMPEditorDoc* pDoc = GetDocument();
	if (image.get_clipboard())
		return;
	if (image.cb_pixel() == 3)
		image.decrease_color_depth(GetDocument()->palet());
	CXCCTMPEditorDoc::t_map_entry& e = pDoc->map_edit().find(get_current_id())->second;
	e.extra_data.write(image.image(), image.cb_image());
	e.header.cx_extra = image.cx();
	e.header.cy_extra = image.cy();
	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);
	*/
}

void CLeftView::OnUpdatePopupPasteExtraImage(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(get_current_id() != -1 && IsClipboardFormatAvailable(CF_DIB));
}

const char* load_filter = "JPEG files (*.jpeg;*.jpg)|*.jpeg;*.jpg|PCX files (*.pcx)|*.pcx|";

void CLeftView::OnPopupLoadaspcxImage() 
{
	Cvirtual_image image;
	if (!load_image(image))
		GetDocument()->set_image(get_current_id(), image);
	/*
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, load_filter, this);
	dlg.m_ofn.nFilterIndex = 2;
	if (IDOK == dlg.DoModal())
	{
		Cvirtual_image image;
		if (image.load(static_cast<string>(dlg.GetPathName())))
			return;
		if (image.cb_pixel() == 3)
			image.decrease_color_depth(GetDocument()->palet());
		GetDocument()->set_image(get_current_id(), image);
	}
	*/
}

void CLeftView::OnUpdatePopupLoadaspcxImage(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(get_current_id() != -1);
}

void CLeftView::OnPopupLoadaspcxExtraimage() 
{
	Cvirtual_image image;
	if (!load_image(image))
		GetDocument()->set_extra_image(get_current_id(), image);
	/*
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, load_filter, this);
	dlg.m_ofn.nFilterIndex = 2;
	if (IDOK == dlg.DoModal())
	{
		Cvirtual_image image;
		if (image.load(static_cast<string>(dlg.GetPathName())))
			return;
		if (image.cb_pixel() == 3)
			image.decrease_color_depth(GetDocument()->palet());
		GetDocument()->set_extra_image(get_current_id(), image);
	}
	*/
}

void CLeftView::OnUpdatePopupLoadaspcxExtraimage(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(get_current_id() != -1);
}

const char* save_filter = "JPEG files (*.jpeg;*.jpg)|*.jpeg;*.jpg|PCX files (*.pcx)|*.pcx|PNG files (*.png)|*.png|";

void CLeftView::OnPopupSaveaspcxImage() 
{
	save_image(GetDocument()->get_image(get_current_id()));
	/*
	CFileDialog dlg(false, "", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, save_filter, this);
	dlg.m_ofn.nFilterIndex = 2;
	if (IDOK == dlg.DoModal())
	{
		t_file_type ft = ft_pcx;
		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1:
			ft = ft_jpeg;
			break;
		case 2:
			ft = ft_pcx;
			break;
		case 3:
			ft = ft_png;
			break;
		}
		GetDocument()->get_image(get_current_id()).save(static_cast<string>(dlg.GetPathName()), ft);
	}
	*/
}

void CLeftView::OnPopupSaveaspcxExtraimage() 
{
	save_image(GetDocument()->get_extra_image(get_current_id()));
	/*
	CFileDialog dlg(false, "", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, save_filter, this);
	dlg.m_ofn.nFilterIndex = 2;
	if (IDOK == dlg.DoModal())
	{
		t_file_type ft = ft_pcx;
		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1:
			ft = ft_jpeg;
			break;
		case 2:
			ft = ft_pcx;
			break;
		case 3:
			ft = ft_png;
			break;
		}
		GetDocument()->get_extra_image(get_current_id()).save(static_cast<string>(dlg.GetPathName()), ft);
	}
	*/
}

void CLeftView::OnPopupCopyComplete() 
{
	GetDocument()->get_complete().set_clipboard();
	/*
	CXCCTMPEditorDoc* pDoc = GetDocument();
	t_rect global = pDoc->get_rect();
	int cx = global.r - global.x;
	int cy = global.b - global.y;
	byte* d = new byte[cx * cy];
	pDoc->draw(d);
	Cvirtual_image image;
	image.load(d, cx, cy, 1, pDoc->palet());
	delete[] d;
	image.set_clipboard();
	*/
}

void CLeftView::OnPopupPasteComplete() 
{
	Cvirtual_image image;
	if (image.get_clipboard())
		return;
	if (image.cb_pixel() == 3)
		image.decrease_color_depth(GetDocument()->palet());
	GetDocument()->set_complete(image);
	/*
	CXCCTMPEditorDoc* pDoc = GetDocument();
	t_rect global = pDoc->get_rect();
	int cx = global.r - global.x;
	int cy = global.b - global.y;
	Cvirtual_image image;
	if (image.get_clipboard() || image.cx() != cx || image.cy() != cy)
		return;
	if (image.cb_pixel() == 3)
		image.decrease_color_depth(GetDocument()->palet());
	pDoc->draw_reverse(image.image());
	*/
}

void CLeftView::OnPopupLoadComplete() 
{
	Cvirtual_image image;
	if (!load_image(image))
		GetDocument()->set_complete(image);
	/*
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, load_filter, this);
	dlg.m_ofn.nFilterIndex = 2;
	if (IDOK == dlg.DoModal())
	{
		Cvirtual_image image;
		if (image.load(static_cast<string>(dlg.GetPathName())))
			return;
		if (image.cb_pixel() == 3)
			image.decrease_color_depth(GetDocument()->palet());
		GetDocument()->set_complete(image);
	}
	*/
}

void CLeftView::OnPopupSaveComplete() 
{
	save_image(GetDocument()->get_complete());
	/*
	CFileDialog dlg(false, "", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, save_filter, this);
	dlg.m_ofn.nFilterIndex = 2;
	if (IDOK == dlg.DoModal())
	{
		t_file_type ft = ft_pcx;
		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1:
			ft = ft_jpeg;
			break;
		case 2:
			ft = ft_pcx;
			break;
		case 3:
			ft = ft_png;
			break;
		}
		GetDocument()->get_complete().save(static_cast<string>(dlg.GetPathName()), ft);
	}
	*/
}

void CLeftView::OnPopupDelete() 
{
	CListCtrl& lc = GetListCtrl();
	while (1)
	{
		int index = lc.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if (index == -1)
			break;
		GetDocument()->remove(lc.GetItemData(index));
	}
}

void CLeftView::OnUpdatePopupDelete(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(get_current_id() != -1);
}

void CLeftView::OnPopupInsert() 
{
}

void CLeftView::OnUpdatePopupInsert(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(false);
}

void CLeftView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	/*
	if (~pNMTreeView->itemOld.state & TVIS_SELECTED && pNMTreeView->itemNew.state & TVIS_SELECTED)
		m_other_pane->set_category(static_cast<Cxcc_mod::t_category_type>(pNMTreeView->itemNew.lParam));	
	*/
	*pResult = 0;
}

int CLeftView::get_current_id()
{
	CListCtrl& lc = GetListCtrl();
	int index = lc.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
	if (index == -1)
		return -1;
	return lc.GetItemData(index);
}

void CLeftView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	sync();
}

void CLeftView::select_all()
{
	SetFocus();
	CListCtrl& lc = GetListCtrl();
	for (int index = 0; index < lc.GetItemCount(); index++)
	{
		lc.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);
	}
}

void CLeftView::invert_selection()
{
	SetFocus();
	CListCtrl& lc = GetListCtrl();
	for (int index = 0; index < lc.GetItemCount(); index++)
	{
		lc.SetItemState(index, ~lc.GetItemState(index, LVIS_SELECTED), LVIS_SELECTED);
	}
}

void CLeftView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int column = pNMListView->iSubItem;
	sort_list(column, column == m_sort_column ? !m_sort_reverse : false);
	*pResult = 0;
}

static int compare_int(int a, int b)
{
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}

int CLeftView::compare(int id_a, int id_b)
{
	typedef CXCCTMPEditorDoc::t_map_entry t_map_entry;
	typedef CXCCTMPEditorDoc::t_map t_map;

	const t_map& map = GetDocument()->map();

	if (m_sort_reverse)
		swap(id_a, id_b);
	const t_map_entry& a = map.find(id_a)->second;
	const t_map_entry& b = map.find(id_b)->second;
	switch (m_sort_column)
	{
	case 0:
		return compare_int(a.header.x, b.header.x);
	case 1:
		return compare_int(a.header.y, b.header.y);
	case 2:
		return compare_int(a.header.has_extra_data, b.header.has_extra_data);
	case 3:
		return compare_int(a.header.height, b.header.height);
	case 4:
		return compare_int(a.header.terrain_type, b.header.terrain_type);
	case 5:
		return compare_int(a.header.ramp_type, b.header.ramp_type);
	default:
		return 0;
	}
}

static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return reinterpret_cast<CLeftView*>(lParamSort)->compare(lParam1, lParam2);
}

void CLeftView::sort_list(int i, bool reverse)
{
	CListCtrl& lc = GetListCtrl();
	m_sort_column = i;
	m_sort_reverse = reverse;
	lc.SortItems(Compare, reinterpret_cast<dword>(this));
}

void CLeftView::OnPopupProperties() 
{
	int id = get_current_id();
	t_tmp_image_header header = GetDocument()->map().find(id)->second.header;
	Cproperties_dlg dlg;
	dlg.set(header);
	if (IDOK == dlg.DoModal())
	{
		dlg.get(header);
		GetDocument()->set_image_header(id, header);
	}
}

void CLeftView::OnUpdatePopupProperties(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(get_current_id() != -1);
}

int CLeftView::load_image(Cvirtual_image& image)
{
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, load_filter, this);
	dlg.m_ofn.nFilterIndex = 2;
	if (IDOK == dlg.DoModal())
	{
		int error = image.load(static_cast<string>(dlg.GetPathName()));
		if (!error && image.cb_pixel() == 3)
			image.decrease_color_depth(GetDocument()->palet());
		return error;
	}
	return 2;
}

int CLeftView::save_image(const Cvirtual_image& image)
{
	CFileDialog dlg(false, "", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, save_filter, this);
	dlg.m_ofn.nFilterIndex = 2;
	if (IDOK == dlg.DoModal())
	{
		t_file_type ft = ft_pcx;
		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1:
			ft = ft_jpeg;
			break;
		case 2:
			ft = ft_pcx;
			break;
		case 3:
			ft = ft_png;
			break;
		}
		return image.save(static_cast<string>(dlg.GetPathName()), ft);
	}
	return 2;
}
