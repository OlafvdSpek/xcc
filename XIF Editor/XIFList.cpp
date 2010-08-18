#include "stdafx.h"
#include "string_conversion.h"
#include "XIF Editor.h"
#include "XIFList.h"
#include "resource.h"
#include "pcx_decode.h"
#include "pcx_file.h"
#include "dlg_edit_bin32.h"
#include "dlg_edit_int32.h"
#include "dlg_edit_string.h"
#include "xif_tools.h"

IMPLEMENT_DYNCREATE(CXIFList, CListView)

CXIFList::CXIFList()
{
}

CXIFList::~CXIFList()
{
}

BEGIN_MESSAGE_MAP(CXIFList, CListView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CXIFList)
	ON_COMMAND(ID_POPUP_EDIT_VALUE, OnPopupEditValue)
	ON_UPDATE_COMMAND_UI(ID_POPUP_EDIT_VALUE, OnUpdatePopupEditValue)
	ON_COMMAND(ID_POPUP_INSERT_BIN32, OnPopupInsertBin32)
	ON_COMMAND(ID_POPUP_INSERT_BINARY, OnPopupInsertBinary)
	ON_COMMAND(ID_POPUP_INSERT_INT32, OnPopupInsertInt32)
	ON_COMMAND(ID_POPUP_INSERT_STRING, OnPopupInsertString)
	ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_COMMAND(ID_POPUP_LOAD_VALUE_PCX, OnPopupLoadValuePcx)
	ON_UPDATE_COMMAND_UI(ID_POPUP_LOAD_VALUE_PCX, OnUpdatePopupLoadValuePcx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CXIFList::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= LVS_EDITLABELS | LVS_NOSORTHEADER | LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

void CXIFList::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	ListView_SetExtendedListViewStyle(m_hWnd, ListView_GetExtendedListViewStyle(m_hWnd) | LVS_EX_FULLROWSELECT);

	int c_colums = 2;
	char* column_label[] = {"Name", "Value"};

	LV_COLUMN lvc;
	lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.cx = 200;
	for (int i = 0; i < c_colums; i++)
	{
		lvc.iSubItem = i;
		lvc.pszText = column_label[i];
		GetListCtrl().InsertColumn(i, &lvc);
	}
}

void CXIFList::insert_key()
{
	for (t_xif_value_map::const_iterator v = m_key->m_values.begin(); v != m_key->m_values.end(); v++)
		insert_value(v->first);
}

int CXIFList::insert_value(int id)
{
	CListCtrl& lc = GetListCtrl();
	int i = lc.InsertItem(id, nh(8, id).c_str());
	lc.SetItemData(i, id);
	update_value(i, id);
	return i;
}

void CXIFList::update_value(int i, int id)
{
	CListCtrl& lc = GetListCtrl();
	const Cxif_value& v = m_key->open_value_read(id);
	string s;
	switch (v.get_type())
	{
	case vt_binary:
		{
			int count = min(v.get_size(), 32);
			const byte* r = v.get_data();
			while (count--)
				s += nh(2, *r++) + ' ';
			if (v.get_size() > 32)
				s += "...";
			break;
		}
	case vt_bin32:
		s = nh(8, v.get_int());
		break;
	case vt_int32:
		s = n(v.get_int());
		break;
	case vt_string:
		s = v.get_string();
		break;
	}
	lc.SetItemText(i, 1, s.c_str());
}

void CXIFList::open_key(Cxif_key* key)
{
	if (m_key)
		close_key();
	m_key = key;
	insert_key();
}


void CXIFList::close_key()
{
	GetListCtrl().DeleteAllItems();
	m_key = NULL;
}

void CXIFList::OnContextMenu(CWnd*, CPoint point)
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
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_XIFLIST));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

int CXIFList::get_current_index()
{
	return GetListCtrl().GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
}

void CXIFList::OnPopupEditValue() 
{
	CListCtrl& lc = GetListCtrl();
	int i = get_current_index();
	int id = lc.GetItemData(i);
	switch (m_key->open_value_read(id).get_type())
	{
	case vt_binary:
		break;
	case vt_bin32:
		{
			Cdlg_edit_bin32 dlg;
			dlg.set(nh(8, id), m_key->get_value_int(id));
			if (dlg.DoModal() == IDOK)
			{
				m_key->set_value_bin(id, dlg.get());
				update_value(i, id);
			}
			break;
		}
	case vt_int32:
		{
			Cdlg_edit_int32 dlg;
			dlg.set(nh(8, id), m_key->get_value_int(id));
			if (dlg.DoModal() == IDOK)
			{
				m_key->set_value_int(id, dlg.get());
				update_value(i, id);
			}
			break;
		}
	case vt_string:
		{
			Cdlg_edit_string dlg;
			dlg.set(nh(8, id), m_key->get_value_string(id));
			if (dlg.DoModal() == IDOK)
			{
				m_key->set_value_string(id, dlg.get());
				update_value(i, id);
			}
			break;
		}
	}
}

void CXIFList::OnUpdatePopupEditValue(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(get_current_index() != -1);
}

int CXIFList::get_free_id()
{
	int id = 0;
	while (m_key->m_values.find(id) != m_key->m_values.end())
		id++;	
	return id;
}

void CXIFList::OnPopupInsertBin32() 
{
	int id = get_free_id();
	m_key->set_value_bin(id, 0);
	GetListCtrl().EditLabel(insert_value(id));
}

void CXIFList::OnPopupInsertBinary() 
{
	int id = get_free_id();
	m_key->set_value_binary(id, Cvirtual_binary());
	GetListCtrl().EditLabel(insert_value(id));
}

void CXIFList::OnPopupInsertInt32() 
{
	int id = get_free_id();
	m_key->set_value_int(id, 0);
	GetListCtrl().EditLabel(insert_value(id));
}

void CXIFList::OnPopupInsertString() 
{
	int id = get_free_id();
	m_key->set_value_string(id, "");
	GetListCtrl().EditLabel(insert_value(id));
}

void CXIFList::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	*pResult = false;
}

void CXIFList::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	*pResult = false;
	const char* t = pDispInfo->item.pszText;
	if (t)
	{
		int id = str2id(t);
		if (id != -1)
		{
			CListCtrl& lc = GetListCtrl();
			if (m_key->exists_value(id))
				return;
			int old_id = pDispInfo->item.lParam;
			Cxif_value v = m_key->open_value_read(old_id);
			m_key->delete_value(old_id);
			m_key->open_value_write(id) = v;
			lc.SetItemData(pDispInfo->item.iItem, id);
			*pResult = true;
		}
	}
}

const char* all_filter = "All files (*.*)|*.*|";
const char* pcx_filter = "PCX files (*.pcx)|*.pcx|";

void CXIFList::OnPopupLoadValuePcx() 
{
	CFileDialog dlg(true, "pcx", 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, pcx_filter, this);
	if (dlg.DoModal() == IDOK)
	{
		Cpcx_file f;
		if (!f.open(static_cast<const char*>(dlg.GetPathName())))
		{
			if (f.is_valid() && f.cb_pixel() == 1)
			{
				CListCtrl& lc = GetListCtrl();
				int i = get_current_index();
				int id = lc.GetItemData(i);
				Cvirtual_binary image;
				pcx_decode(f.get_image(), image.write_start(f.cb_image()), f.header());
				m_key->set_value_binary(id, image);
				update_value(i, id);
			}
			f.close();
		}
	}
}

void CXIFList::OnUpdatePopupLoadValuePcx(CCmdUI* pCmdUI) 
{
	CListCtrl& lc = GetListCtrl();
	int i = get_current_index();
	pCmdUI->Enable(i != -1 && m_key->open_value_read(lc.GetItemData(i)).get_type() == vt_binary);
}
