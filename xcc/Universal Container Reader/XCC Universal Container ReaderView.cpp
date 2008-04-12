#include "stdafx.h"
#include "XCC Universal Container Reader.h"

#include "XCC Universal Container ReaderDoc.h"
#include "XCC Universal Container ReaderView.h"

#include "fname.h"
#include "string_conversion.h"

IMPLEMENT_DYNCREATE(CXCCUniversalContainerReaderView, CListView)

BEGIN_MESSAGE_MAP(CXCCUniversalContainerReaderView, CListView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CXCCUniversalContainerReaderView)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_COMMAND(ID_POPUP_COPY_TO, OnPopupCopyTo)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_TO, OnUpdatePopupCopyTo)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_EDIT_INVERT_SELECTION, OnEditInvertSelection)
	ON_COMMAND(ID_POPUP_OPEN, OnPopupOpen)
	ON_UPDATE_COMMAND_UI(ID_POPUP_OPEN, OnUpdatePopupOpen)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCUniversalContainerReaderView construction/destruction

CXCCUniversalContainerReaderView::CXCCUniversalContainerReaderView()
{
	m_buffer_w = 0;
}

CXCCUniversalContainerReaderView::~CXCCUniversalContainerReaderView()
{
}

BOOL CXCCUniversalContainerReaderView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

static int c_colums = 3;

void CXCCUniversalContainerReaderView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	const char* column_label[] = {"Name", "Offset", "Size"};
	// int column_alignment[] = {LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_RIGHT};

	SetRedraw(false);
	CListCtrl& lc = GetListCtrl();
	lc.SetExtendedStyle(lc.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	for (int i = 0; i < c_colums; i++)
		lc.InsertColumn(i, column_label[i], LVCFMT_RIGHT, -1, i);
	{
		const Cucr_container& container = CXCCUniversalContainerReaderView::container();
		for (int i = 0; i < container.size(); i++)
			lc.SetItemData(lc.InsertItem(lc.GetItemCount(), LPSTR_TEXTCALLBACK), i);
	}
	auto_size();
	SetRedraw(true);
	m_output_dir = Cfname(string(GetDocument()->GetPathName())).get_path();
}

/////////////////////////////////////////////////////////////////////////////
// CXCCUniversalContainerReaderView diagnostics

#ifdef _DEBUG
void CXCCUniversalContainerReaderView::AssertValid() const
{
	CListView::AssertValid();
}

void CXCCUniversalContainerReaderView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CXCCUniversalContainerReaderDoc* CXCCUniversalContainerReaderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXCCUniversalContainerReaderDoc)));
	return (CXCCUniversalContainerReaderDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXCCUniversalContainerReaderView message handlers

void CXCCUniversalContainerReaderView::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	const Cucr_object& e = container()[pDispInfo->item.lParam];
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		m_buffer[m_buffer_w] = e.name();
		break;
	case 1:
		m_buffer[m_buffer_w] = n(e.offset());
		break;
	case 2:
		m_buffer[m_buffer_w] = n(e.size());
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

void CXCCUniversalContainerReaderView::auto_size()
{
	CListCtrl& lc = GetListCtrl();
	for (int i = 0; i < c_colums; i++)
		lc.SetColumnWidth(i, LVSCW_AUTOSIZE);
}

void CXCCUniversalContainerReaderView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	int column = reinterpret_cast<NM_LISTVIEW*>(pNMHDR)->iSubItem;
	sort_items(column, column == m_sort_column ? !m_sort_reverse : false);
	*pResult = 0;
}

template<class T>
static int compare(T a, T b)
{
	return a < b ? -1 : a != b;
}

int CXCCUniversalContainerReaderView::compare(int id_a, int id_b)
{
	if (m_sort_reverse)
		swap(id_a, id_b);
	const Cucr_object& a = container()[id_a];
	const Cucr_object& b = container()[id_b];
	switch (m_sort_column)
	{
	case 0:
		return ::compare(a.name(), b.name());
	case 1:
		return ::compare(a.offset(), b.offset());
	case 2:
		return ::compare(a.size(), b.size());
	}
	return 0;
}

static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return reinterpret_cast<CXCCUniversalContainerReaderView*>(lParamSort)->compare(lParam1, lParam2);
}

void CXCCUniversalContainerReaderView::sort_items(int i, bool reverse)
{
	m_sort_column = i;
	m_sort_reverse = reverse;
	GetListCtrl().SortItems(Compare, reinterpret_cast<dword>(this));
}
#include "resource.h"

void CXCCUniversalContainerReaderView::OnContextMenu(CWnd*, CPoint point)
{
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
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CXCCUniversalContainerReaderView::OnPopupOpen()
{
	string dir = get_temp_path();
	CWaitCursor wc;
	CListCtrl& lc = GetListCtrl();
	int i = -1;
	while ((i = lc.GetNextItem(i, LVNI_SELECTED)) != -1)
	{
		const Cucr_object& e = container()[lc.GetItemData(i)];
		string name = "XCC Universal Container Reader\\" + e.name();
		create_deep_dir(dir, name);
		e.d().export(dir + name);
		ShellExecute(m_hWnd, "open", (dir + name).c_str(), NULL, NULL, SW_SHOW);
	}
}

void CXCCUniversalContainerReaderView::OnUpdatePopupOpen(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount());
}

static int CALLBACK WINAPI BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED)
	{
		char b[MAX_PATH];
		strcpy(b, reinterpret_cast<const char*>(lpData));
		SendMessage(hwnd, BFFM_SETSELECTION, (WPARAM)1, (LPARAM)b);
	}
	return 0;
}

void CXCCUniversalContainerReaderView::OnPopupCopyTo()
{
	BROWSEINFO bi;
	ITEMIDLIST* idlist;
	bi.hwndOwner = GetSafeHwnd();
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = "Select a directory for the files:";
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = reinterpret_cast<DWORD>(m_output_dir.c_str());
	idlist = SHBrowseForFolder(&bi);
	if (!idlist)
		return;
	char b[MAX_PATH];
	if (SHGetPathFromIDList(idlist, b)) // && strlen(b))
	{
		CWaitCursor wc;
		m_output_dir = b;
		CListCtrl& lc = GetListCtrl();
		int i = -1;
		while ((i = lc.GetNextItem(i, LVNI_SELECTED)) != -1)
		{
			const Cucr_object& e = container()[lc.GetItemData(i)];
			string name = e.name();
			create_deep_dir(b, name);
			e.d().export(string(b) + '\\' + name);
		}
	}
	LPMALLOC pMalloc;
	if (SUCCEEDED(SHGetMalloc(&pMalloc)) && pMalloc)
	{
		pMalloc->Free(idlist);
		pMalloc->Release();
	}
}

void CXCCUniversalContainerReaderView::OnUpdatePopupCopyTo(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount());
}

void CXCCUniversalContainerReaderView::OnEditSelectAll()
{
	CListCtrl& lc = GetListCtrl();
	for (int i = 0; i < lc.GetItemCount(); i++)
		lc.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
}

void CXCCUniversalContainerReaderView::OnEditInvertSelection()
{
	CListCtrl& lc = GetListCtrl();
	for (int index = 0; index < lc.GetItemCount(); index++)
		lc.SetItemState(index, ~lc.GetItemState(index, LVIS_SELECTED), LVIS_SELECTED);
}

void CXCCUniversalContainerReaderView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	OnPopupOpen();
	*pResult = 0;
}
