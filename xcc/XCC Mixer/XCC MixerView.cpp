// XCC MixerView.cpp : implementation of the CXCCMixerView class
//

#include "stdafx.h"
#include "XCC Mixer.h"

#include "MainFrm.h"
#include "XCCFileView.h"
#include "XCC MixerDoc.h"
#include "XCC MixerView.h"
#include "resource.h"

#include <fstream>
#include <id_log.h>
#include <pal_file.h>
#include <string_conversion.h>
#include "aud_decode.h"
#include "aud_file.h"
#include "aud_file_write.h"
#include "cps_file.h"
#include "extract_object.h"
#include "hva_file.h"
#include "ima_adpcm_wav_decode.h"
#include "ima_adpcm_wav_encode.h"
#include "image_tools.h"
#include "pal_file.h"
#include "pcx_decode.h"
#include "pcx_file.h"
#include "resizedlg.h"
#include "shp_decode.h"
#include "shp_dune2_file.h"
#include "shp_file.h"
#include "shp_images.h"
#include "shp_ts_file.h"
#include "shp_ts_file_write.h"
#include "st_file.h"
#include "text_file.h"
#include "tmp_file.h"
#include "tmp_ra_file.h"
#include "tmp_ts_file.h"
#include "voc_file.h"
#include "vqa_file.h"
#include "vxl_file.h"
#include "wav_file.h"
#include "wav_structures.h"
#include "wsa_dune2_file.h"
#include "wsa_file.h"
#include "xif_file.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCMixerView

IMPLEMENT_DYNCREATE(CXCCMixerView, CListView)

BEGIN_MESSAGE_MAP(CXCCMixerView, CListView)
	ON_COMMAND_RANGE(ID_FILE_FOUND_MIX00, ID_FILE_FOUND_MIX99, OnFileFound)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CXCCMixerView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, OnUpdateFileClose)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_COMMAND(ID_POPUP_EXTRACT, OnPopupExtract)
	ON_UPDATE_COMMAND_UI(ID_POPUP_EXTRACT, OnUpdatePopupExtract)
	ON_COMMAND(ID_POPUP_COPY, OnPopupCopy)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY, OnUpdatePopupCopy)
	ON_COMMAND(ID_POPUP_COPY_AS_AUD, OnPopupCopyAsAUD)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_AUD, OnUpdatePopupCopyAsAUD)
	ON_COMMAND(ID_POPUP_COPY_AS_AVI, OnPopupCopyAsAVI)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_AVI, OnUpdatePopupCopyAsAVI)
	ON_COMMAND(ID_POPUP_COPY_AS_CPS, OnPopupCopyAsCPS)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_CPS, OnUpdatePopupCopyAsCPS)
	ON_COMMAND(ID_POPUP_COPY_AS_PCX, OnPopupCopyAsPCX)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_PCX, OnUpdatePopupCopyAsPCX)
	ON_COMMAND(ID_POPUP_COPY_AS_SHP, OnPopupCopyAsSHP)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_SHP, OnUpdatePopupCopyAsSHP)
	ON_COMMAND(ID_POPUP_COPY_AS_WSA, OnPopupCopyAsWSA)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_WSA, OnUpdatePopupCopyAsWSA)
	ON_COMMAND(ID_POPUP_DELETE, OnPopupDelete)
	ON_UPDATE_COMMAND_UI(ID_POPUP_DELETE, OnUpdatePopupDelete)
	ON_COMMAND(ID_POPUP_OPEN, OnPopupOpen)
	ON_UPDATE_COMMAND_UI(ID_POPUP_OPEN, OnUpdatePopupOpen)
	ON_COMMAND(ID_POPUP_OPEN_FOR_EDIT, OnPopupOpenForEdit)
	ON_UPDATE_COMMAND_UI(ID_POPUP_OPEN_FOR_EDIT, OnUpdatePopupOpenForEdit)
	ON_COMMAND(ID_POPUP_OPEN_WITH_FINALSUN, OnPopupOpenWithFinalsun)
	ON_UPDATE_COMMAND_UI(ID_POPUP_OPEN_WITH_FINALSUN, OnUpdatePopupOpenWithFinalsun)
	ON_COMMAND(ID_POPUP_COPY_AS_VXL, OnPopupCopyAsVXL)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_VXL, OnUpdatePopupCopyAsVXL)
	ON_COMMAND(ID_POPUP_COPY_AS_XIF, OnPopupCopyAsXIF)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_XIF, OnUpdatePopupCopyAsXIF)
	ON_COMMAND(ID_POPUP_COPY_AS_CSV, OnPopupCopyAsCSV)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_CSV, OnUpdatePopupCopyAsCSV)
	ON_COMMAND(ID_POPUP_COPY_AS_HVA, OnPopupCopyAsHVA)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_HVA, OnUpdatePopupCopyAsHVA)
	ON_COMMAND(ID_POPUP_COPY_AS_PAL, OnPopupCopyAsPAL)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_PAL, OnUpdatePopupCopyAsPAL)
	ON_COMMAND(ID_POPUP_COPY_AS_SHP_TS, OnPopupCopyAsShHP_TS)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_SHP_TS, OnUpdatePopupCopyAsSHP_TS)
	ON_COMMAND(ID_POPUP_COPY_AS_TMP_TS, OnPopupCopyAsTMP_TS)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_TMP_TS, OnUpdatePopupCopyAsTMP_TS)
	ON_COMMAND(ID_POPUP_COPY_AS_PAL_JASC, OnPopupCopyAsPAL_JASC)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_PAL_JASC, OnUpdatePopupCopyAsPAL_JASC)
	ON_COMMAND(ID_POPUP_COPY_AS_TEXT, OnPopupCopyAsText)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_TEXT, OnUpdatePopupCopyAsText)
	ON_COMMAND(ID_POPUP_PLAY, OnPopupPlay)
	ON_UPDATE_COMMAND_UI(ID_POPUP_PLAY, OnUpdatePopupPlay)
	ON_COMMAND(ID_POPUP_COPY_AS_MAP_TS_PREVIEW, OnPopupCopyAsMapTsPreview)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_MAP_TS_PREVIEW, OnUpdatePopupCopyAsMapTsPreview)
	ON_COMMAND(ID_POPUP_REFRESH, OnPopupRefresh)
	ON_UPDATE_COMMAND_UI(ID_POPUP_REFRESH, OnUpdatePopupRefresh)
	ON_COMMAND(ID_POPUP_RESIZE, OnPopupResize)
	ON_UPDATE_COMMAND_UI(ID_POPUP_RESIZE, OnUpdatePopupResize)
	ON_COMMAND(ID_POPUP_COPY_AS_HTML, OnPopupCopyAsHTML)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_HTML, OnUpdatePopupCopyAsHTML)
	ON_COMMAND(ID_POPUP_IMPORT_INTO_TS, OnPopupImportIntoTS)
	ON_UPDATE_COMMAND_UI(ID_POPUP_IMPORT_INTO_TS, OnUpdatePopupImportIntoTS)
	ON_COMMAND(ID_POPUP_IMPORT_INTO_RA2, OnPopupImportIntoRa2)
	ON_UPDATE_COMMAND_UI(ID_POPUP_IMPORT_INTO_RA2, OnUpdatePopupImportIntoRa2)
	ON_COMMAND(ID_POPUP_COPY_AS_PNG, OnPopupCopyAsPNG)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_PNG, OnUpdatePopupCopyAsPNG)
	ON_COMMAND(ID_POPUP_COPY_AS_WAV_IMA_ADPCM, OnPopupCopyAsWavImaAdpcm)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_WAV_IMA_ADPCM, OnUpdatePopupCopyAsWavImaAdpcm)
	ON_COMMAND(ID_POPUP_COPY_AS_WAV_PCM, OnPopupCopyAsWavPcm)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_WAV_PCM, OnUpdatePopupCopyAsWavPcm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCMixerView construction/destruction

CXCCMixerView::CXCCMixerView()
{
	m_mix_f = NULL;
}

CXCCMixerView::~CXCCMixerView()
{
}

BOOL CXCCMixerView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CXCCMixerView drawing

void CXCCMixerView::OnDraw(CDC* pDC)
{
}

static int c_colums = 4;
static char* column_label[] = {"Name", "Type", "Description", "Size"};
static int column_alignment[] = {LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_RIGHT};

void CXCCMixerView::OnInitialUpdate()
{
	char dir[MAX_PATH];
	if (GetCurrentDirectory(MAX_PATH, dir))
	{
		Cfname fn = dir;
		fn.make_path();
		m_dir = fn.get_all();;
	}
	else
		m_dir = "c:\\";
	m_dir = AfxGetApp()->GetProfileString(m_reg_key, "path", m_dir.c_str());
	CListView::OnInitialUpdate();
	ListView_SetExtendedListViewStyle(m_hWnd, ListView_GetExtendedListViewStyle(m_hWnd) | LVS_EX_FULLROWSELECT);
	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.cx = 100;
	for (int i = 0; i < c_colums; i++)
	{
		lvc.iSubItem = i;
		lvc.pszText = column_label[i];
		lvc.fmt = column_alignment[i];
		GetListCtrl().InsertColumn(i, &lvc);
	}
	update_list();
}

/////////////////////////////////////////////////////////////////////////////
// CXCCMixerView diagnostics

#ifdef _DEBUG
void CXCCMixerView::AssertValid() const
{
	CListView::AssertValid();
}

void CXCCMixerView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXCCMixerView message handlers

void CXCCMixerView::OnFileNew()
{
	close_all_locations();
}

void CXCCMixerView::OnFileOpen()
{
	CFileDialog dlg(true, "mix", NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "MIX files (*.mix)|*.mix|", this);
	if (IDOK == dlg.DoModal())
	{
		close_all_locations();
		open_location_mix(static_cast<string>(dlg.GetPathName()));
	}
}

void CXCCMixerView::OnFileClose()
{
	close_location(true);
}

void CXCCMixerView::OnUpdateFileClose(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(static_cast<bool>(m_mix_f));
}

void CXCCMixerView::open_location_dir(const string& name)
{
	m_dir = name;
	update_list();
}

void CXCCMixerView::open_location_mix(const string& name)
{
	Cmix_file* mix_f = new Cmix_file;
	if (mix_f->open(name))
		delete mix_f;
	else
	{
		m_location.push(m_mix_f);
		m_mix_f = mix_f;
	}
	update_list();
}

void CXCCMixerView::open_location_mix(int id)
{
	Cmix_file* mix_f = new Cmix_file;
	if (mix_f->open(id, *m_mix_f))
		delete mix_f;
	else
	{
		m_location.push(m_mix_f);
		m_mix_f = mix_f;
		update_list();
	}
}

void CXCCMixerView::close_location(int reload)
{
	if (m_mix_f)
	{
		m_mix_f->close();
		delete m_mix_f;
		m_mix_f = m_location.top();
		m_location.pop();
		if (reload)
			update_list();
	}
}

void CXCCMixerView::close_all_locations()
{
	while (!m_location.empty())
		close_location(false);
}

void CXCCMixerView::clear_list()
{
	GetListCtrl().DeleteAllItems();
	m_index.clear();
}

void CXCCMixerView::update_list()
{
	clear_list();
	t_index_entry e;
	m_palet_loaded = false;
	if (m_mix_f)
	{
		m_game = m_mix_f->get_game();
		for (int i = 0; i < m_mix_f->get_c_files(); i++)
		{
			int id = m_mix_f->get_id(i);
			e.description = mix_database::get_description(m_game, id);
			e.ft = m_mix_f->get_type(id);
			e.name = mix_database::get_name(m_game, id);
			e.size = m_mix_f->get_size(id);
			m_index[id] = e;
			if (e.ft == ft_pal)
			{
				Cpal_file f;
				f.open(id, *m_mix_f);
				memcpy(m_palet, f.get_palet(), sizeof(t_palet));
				f.close();
				m_palet_loaded = true;
			}
		}
	}
	else
	{
		m_game = game_ts;
		int drivemap = GetLogicalDrives();
		char drive_name[] = "a:\\";
		for (int i = 0; i < 26; i++)
		{
			if (drivemap >> i & 1)
			{
				e.description = "";
				e.ft = ft_drive;
				e.name = drive_name;
				m_index[Cmix_file::get_id(get_game(), e.name)] = e;
			}
			drive_name[0]++;
		}
		WIN32_FIND_DATA finddata;
		HANDLE findhandle = FindFirstFile((m_dir + "*").c_str(), &finddata);
		if (findhandle != INVALID_HANDLE_VALUE)
		{
			Ccc_file f(false);
			do
			{
				e.name = finddata.cFileName;
				if (finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (e.name == ".")
						continue;
					e.ft = ft_dir;
				}
				else
				{
					if (f.open(m_dir + e.name))
						continue;
					e.ft = f.get_file_type();
					e.size = f.get_size();
					f.close();
				}
				int id = Cmix_file::get_id(get_game(), finddata.cFileName);
				e.description = mix_database::get_description(get_game(), id);
				m_index[id] = e;
			}
			while (FindNextFile(findhandle, &finddata));
			FindClose(findhandle);
		}
	}
	SetRedraw(false);
	int j = 0;
	LV_ITEM lvi;
	lvi.mask = LVIF_PARAM | LVIF_TEXT;
	lvi.iSubItem = 0;
	for (t_index::iterator i = m_index.begin(); i != m_index.end(); i++)
	{
		char name[256];
		char type[32];
		char description[256];
		char size[16];
		strcpy(name, i->second.name.c_str());
		if (!*name)
			strcpy(name, nh(8, i->first).c_str());
		strcpy(type, ft_name[i->second.ft]);
		strcpy(description, i->second.description.c_str());
		strcpy(size, n(i->second.size).c_str());
		lvi.iItem = j;
		lvi.pszText = name;
		lvi.lParam = i->first;
		GetListCtrl().InsertItem(&lvi);
		GetListCtrl().SetItemText(j, 1, type);
		GetListCtrl().SetItemText(j, 2, description);
		if (i->second.ft != ft_dir && i->second.ft != ft_drive)
			GetListCtrl().SetItemText(j, 3, size);
	}
	for (j = 0; j < c_colums; j++)
		GetListCtrl().SetColumnWidth(j, LVSCW_AUTOSIZE);
	sort_list(0, false);
	sort_list(1, false);
	SetRedraw(true);
}

int CXCCMixerView::compare(int id_a, int id_b) const
{
	if (m_sort_reverse)
		swap(id_a, id_b);
	const t_index_entry& a = m_index.find(id_a)->second;
	const t_index_entry& b = m_index.find(id_b)->second;
	if (a.ft == ft_drive)
	{
		if (b.ft != ft_drive)
			return -1;
	}
	else if (b.ft == ft_drive)
		return 1;
	if (a.ft == ft_dir)
	{
		if (b.ft != ft_dir)
			return -1;
	}
	else if (b.ft == ft_dir)
		return 1;
	switch (m_sort_column)
	{
	case 0:
		if (to_lower(a.name) < to_lower(b.name))
			return -1;
		if (to_lower(a.name) == to_lower(b.name))
			return 0;
		return 1;
	case 1:
		if (a.ft < b.ft)
			return -1;
		if (a.ft == b.ft)
			return 0;
		return 1;
	case 2:
		if (a.description < b.description)
			return -1;
		if (a.description == b.description)
			return 0;
		return 1;
	case 3:
		if (a.size < b.size)
			return -1;
		if (a.size == b.size)
			return 0;
		return 1;
	}
	return 0;
}

static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return reinterpret_cast<CXCCMixerView*>(lParamSort)->compare(lParam1, lParam2);
}

void CXCCMixerView::sort_list(int i, bool reverse)
{
	m_sort_column = i;
	m_sort_reverse = reverse;
	GetListCtrl().SortItems(Compare, reinterpret_cast<dword>(this));
}

static CXCCMixerApp* GetApp()
{
	return static_cast<CXCCMixerApp*>(AfxGetApp());
}

static CMainFrame* GetMainFrame()
{
	return static_cast<CMainFrame*>(AfxGetMainWnd());
}

void CXCCMixerView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	int column = reinterpret_cast<NM_LISTVIEW*>(pNMHDR)->iSubItem;
	sort_list(column, column == m_sort_column ? !m_sort_reverse : false);
	*pResult = 0;
}

void CXCCMixerView::OnDestroy()
{
	AfxGetApp()->WriteProfileString(m_reg_key, "path", m_dir.c_str());	
	close_all_locations();
}

void CXCCMixerView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	int id = get_current_id();
	if (id != -1)
	{
		t_index_entry& index = m_index.find(id)->second;
		switch (index.ft)
		{
		case ft_dir:
			{
				string name = index.name;
				close_location(false);
				open_location_dir(m_dir + name + '\\');
				break;
			}
		case ft_drive:
			{
				string name = index.name;
				close_location(false);
				open_location_dir(name);
				break;
			}
		case ft_mix:
		case ft_pak:
			{
				if (m_mix_f)
					open_location_mix(id);
				else
					open_location_mix(m_dir + index.name);
				break;
			}
		}
	}
	*pResult = 0;
}

void CXCCMixerView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = reinterpret_cast<NM_LISTVIEW*>(pNMHDR);
	if (pNMListView->uNewState & LVIS_FOCUSED)
	{
		LV_ITEM lvi;
		lvi.mask = LVIF_PARAM;
		lvi.iItem = pNMListView->iItem;
		GetListCtrl().GetItem(&lvi);
		if (m_mix_f)
			m_file_view_pane->open_f(lvi.lParam, *m_mix_f, m_game, m_palet_loaded ? m_palet : NULL);
		else
		{
			const t_index_entry& index = m_index[lvi.lParam];
			if (index.ft != ft_dir && index.ft != ft_drive)
				m_file_view_pane->open_f(m_dir + index.name);
		}
	}
	*pResult = 0;
}

int CXCCMixerView::get_current_id() const
{
	int i = get_current_index();
	return i == -1 ? -1 : get_id(i);
}

int CXCCMixerView::get_current_index() const
{
	return GetListCtrl().GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
}

int CXCCMixerView::get_id(int i) const
{
	return GetListCtrl().GetItemData(i);
}

void CXCCMixerView::set_other_panes(CXCCFileView* file_view_pane, CXCCMixerView* other_pane)
{
	m_file_view_pane = file_view_pane;
	m_other_pane = other_pane;
}

void CXCCMixerView::OnContextMenu(CWnd*, CPoint point)
{
		if (point.x == -1 && point.y == -1)
		{
			// keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_MIX_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
}

void CXCCMixerView::OnFileFound(dword ID)
{
	close_all_locations();
	open_location_mix(GetMainFrame()->get_mix_name(ID - ID_FILE_FOUND_MIX00));
}

int CXCCMixerView::open_f_id(Ccc_file& f, int id) const
{
	return m_mix_f ? f.open(id, *m_mix_f) : f.open(m_dir + m_index.find(id)->second.name);
}

int CXCCMixerView::open_f_index(Ccc_file& f, int i) const
{
	return open_f_id(f, GetListCtrl().GetItemData(i));
}

void CXCCMixerView::OnPopupExtract()
{
	int id = get_current_id();
	CFileDialog dlg(false, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, "All files (*.*)|*.*|", this);
	char s[MAX_PATH];
	strcpy(s, m_index.find(id)->second.name.c_str());
	dlg.m_ofn.lpstrFile = s;
	if (IDOK == dlg.DoModal())
	{
		Ccc_file f(false);
		if (open_f_index(f, get_current_index()))
		{
		}
		else
		{
			f.extract(static_cast<string>(dlg.GetPathName()));
			f.close();
		}
	}
}

void CXCCMixerView::OnUpdatePopupExtract(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(get_current_id() != -1);
}

const t_paletentry* CXCCMixerView::get_default_palet() const
{
	const t_palet_entry* p = GetMainFrame()->get_pal_data();
	if (p)
		return p;
	return m_palet;
}

bool CXCCMixerView::can_accept() const
{
	return !m_mix_f;
}

string CXCCMixerView::get_dir() const
{
	return m_dir;
}

void CXCCMixerView::set_reg_key(const string& v)
{
	m_reg_key = v.c_str();
}

static bool can_convert(t_file_type s, t_file_type d)
{
	switch (s)
	{
	case ft_aud:
	case ft_voc:
		return d == ft_wav_pcm;
	case ft_cps:
	case ft_shp_dune2:
	case ft_tmp_ra:
	case ft_tmp_ts:
	case ft_wsa_dune2:
	case ft_wsa:
		return d == ft_pcx;
	case ft_hva:
		return d == ft_csv;
	case ft_pal:
		return d == ft_pal_jasc;
	case ft_pcx:
		return d == ft_cps || d == ft_map_ts_preview || d == ft_pal || d == ft_png || d == ft_shp || d == ft_shp_ts || d == ft_tmp_ts || d == ft_vxl;
	case ft_st:
		return d == ft_text;
	case ft_shp:
		return d == ft_pcx || d == ft_shp_ts;
	case ft_shp_ts:
		return d == ft_pcx || d == ft_png;
	case ft_text:
		return d == ft_hva;
	case ft_vqa:
		return d == ft_avi || d == ft_pcx  || d == ft_png || d == ft_wav_pcm;
	case ft_vxl:
		return d == ft_pcx || d == ft_xif;
	case ft_wav:
		return d == ft_aud || d == ft_wav_ima_adpcm || d == ft_wav_pcm;
	case ft_xif:
		return d == ft_html || d == ft_vxl;
	}
	return false;
}

bool CXCCMixerView::can_copy()
{
	return can_delete() && m_other_pane->can_accept();
}

bool CXCCMixerView::can_delete()
{
	m_index_selected.clear();
	int i = GetListCtrl().GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	while (i != -1)
	{
		int id = GetListCtrl().GetItemData(i);
		const t_index_entry& index = m_index.find(id)->second;
		if (index.ft == ft_dir || index.ft == ft_drive || index.name.empty())
			return false;
		m_index_selected.push_back(i);
		i = GetListCtrl().GetNextItem(i, LVNI_ALL | LVNI_SELECTED);
	}
	return true;
}

bool CXCCMixerView::can_copy_as(t_file_type ft)
{
	if (!can_copy() || m_index_selected.empty())
		return false;
	for (t_index_selected::const_iterator i = m_index_selected.begin(); i != m_index_selected.end(); i++)
	{
		if (!can_convert(m_index.find(get_id(*i))->second.ft, ft))
			return false;
	}
	return true;
}

static void set_msg(const string& s)
{
	GetMainFrame()->SetMessageText(s.c_str());
}

static void copy_failed(const Cfname& fname, int error)
{
	set_msg("Copy " + fname.get_ftitle() + " failed, error " + n(error));
}

static void copy_succeeded(const Cfname& fname)
{
	set_msg("Copy " + fname.get_ftitle() + " succeeded");
}

void CXCCMixerView::copy_as(t_file_type ft) const
{
	for (t_index_selected::const_iterator i = m_index_selected.begin(); i != m_index_selected.end(); i++)
	{
		const string fname = m_other_pane->get_dir() + m_index.find(get_id(*i))->second.name;
		int error;
		switch (ft)
		{
		case -1:
			error = copy(*i, fname);
			break;
		case ft_aud:
			error = copy_as_aud(*i, fname);
			break;
		case ft_avi:
			error = copy_as_avi(*i, fname);
			break;
		case ft_cps:
			error = copy_as_cps(*i, fname);
			break;
		case ft_csv:
			error = copy_as_csv(*i, fname);
			break;
		case ft_html:
			error = copy_as_html(*i, fname);
			break;
		case ft_hva:
			error = copy_as_hva(*i, fname);
			break;
		case ft_map_ts_preview:
			error = copy_as_map_ts_preview(*i, fname);
			break;
		case ft_pal:
			error = copy_as_pal(*i, fname);
			break;
		case ft_pal_jasc:
			error = copy_as_pal_jasc(*i, fname);
			break;
		case ft_pcx:
			error = copy_as_pcx(*i, fname, ft_pcx);
			break;
		case ft_png:
			error = copy_as_pcx(*i, fname, ft_png);
			break;
		case ft_shp:
			error = copy_as_shp(*i, fname);
			break;
		case ft_shp_ts:
			error = copy_as_shp_ts(*i, fname);
			break;
		case ft_text:
			error = copy_as_text(*i, fname);
			break;
		case ft_tmp_ts:
			error = copy_as_tmp_ts(*i, fname);
			break;
		case ft_vxl:
			error = copy_as_vxl(*i, fname);
			break;
		case ft_wav_ima_adpcm:
			error = copy_as_wav_ima_adpcm(*i, fname);
			break;
		case ft_wav_pcm:
			error = copy_as_wav_pcm(*i, fname);
			break;
		case ft_xif:
			error = copy_as_xif(*i, fname);
			break;
		default:
			error = 1;
		}
		if (error)
			copy_failed(fname, error);
		else
			copy_succeeded(fname);
	}
	m_other_pane->update_list();
}

int CXCCMixerView::copy(int i, Cfname fname) const
{
	Ccc_file f(false);
	int error = open_f_index(f, i);
	if (!error)
	{
		error = f.extract(fname);
		f.close();
	}
	return error;
}

int CXCCMixerView::copy_as_aud(int i, Cfname fname) const
{
	Cwav_file f;
	int error = open_f_index(f, i);
	if (!error)
	{
		fname.set_ext(".aud");
		error = f.process();
		const t_riff_wave_format_chunk& format_chunk = f.get_format_chunk();
		int cb_data = f.get_data_header().size;
		int samplerate = format_chunk.samplerate;
		if (!error)
		{
			if (format_chunk.tag != 0x0001 ||
				format_chunk.c_channels != 1 && format_chunk.c_channels != 2 ||
				format_chunk.cbits_sample != 16)
			{
				error = 256;
			}
			else
			{
				byte* data = new byte[cb_data];
				f.seek(f.get_data_ofs());
				error = f.read(data, cb_data);
				if (!error)
				{
					int c_samples = cb_data >> 1;
					if (format_chunk.c_channels == 2)
					{
						audio_combine_channels(reinterpret_cast<__int16*>(data), c_samples);
						c_samples >>= 1;
					}
					if (samplerate == 44100)
					{
						audio_combine_channels(reinterpret_cast<__int16*>(data), c_samples);
						c_samples >>= 1;
						samplerate >>= 1;
					}
					Caud_file_write g;
					error = g.open_write(fname);
					if (!error)
					{
						g.set_c_samples(c_samples);
						g.set_samplerate(samplerate);
						error = g.write_header();
						if (!error)
						{
							aud_decode aud_d;
							aud_d.init();
							const short* r = reinterpret_cast<const short*>(data);
							byte chunk[512];
							while (c_samples)
							{
								int cs_chunk = min(c_samples, 1024);
								aud_d.encode_chunk(r, chunk, cs_chunk);
								r += cs_chunk;
								error = g.write_chunk(chunk, cs_chunk);
								if (error)
									break;
								c_samples -= cs_chunk;
							}
						}
						delete[] data;
						g.close();
					}
				}
			}
		}
		f.close();
	}
	return error;
}

int CXCCMixerView::copy_as_avi(int i, Cfname fname) const
{
	int error = 0;
	fname.set_ext(".avi");
	Cvqa_file f;
	error = open_f_index(f, i);
	if (!error)
	{
		error =  f.extract_as_avi(fname, AfxGetMainWnd()->GetSafeHwnd());
		f.close();
	}
	return error;
}

int CXCCMixerView::copy_as_cps(int i, Cfname fname) const
{
	int error = 0;
	fname.set_ext(".cps");
	Cpcx_file f;
	error = open_f_index(f, i);
	if (!error)
	{
		if (f.get_cx() != 320 || f.get_cy() != 200)
			error = 257;
		else if (f.get_c_planes() != 1)
			error = 258;
		else
		{
			byte* s = new byte[320 * 200];
			pcx_decode(f.get_image(), s, *f.get_header());
			byte* d = new byte[256 << 10];
			t_palet palet;
			memcpy(palet, f.get_palet(), sizeof(t_palet));
			convert_palet_24_to_18(palet);
			int cb_d = cps_file_write(s, d, palet);
			delete[] s;
			if (cb_d)
			{
				Cfile32 g;
				error = g.open_write(fname);
				if (!error)
				{
					error = g.write(d, cb_d);
					g.close();
				}
			}
			else
				error = 1;
			delete[] d;
		}
		f.close();
	}
	return error;
}

int CXCCMixerView::copy_as_csv(int i, Cfname fname) const
{
	int error = 0;
	fname.set_ext(".csv");
	Chva_file f;
	error = open_f_index(f, i);
	if (!error)
	{
		error =  f.extract_as_csv(fname);
		f.close();
	}
	return error;
}

int CXCCMixerView::copy_as_html(int i, Cfname fname) const
{
	int error = 0;
	fname.set_ext(".html");
	Cxif_file f;
	error = open_f_index(f, i);
	if (!error)
	{
		Cxif_key k;
		error = k.load_key(f.get_data(), f.get_size());
		if (!error)
		{
			char d[64 << 10];
			Cextract_object::report(k, d, "");
			ofstream g(fname.get_all().c_str());
			g << d;
		}
		f.close();
	}
	return error;
}

int CXCCMixerView::copy_as_hva(int i, Cfname fname) const
{
	int error = 0;
	fname.set_ext(".hva");
	Ctext_file f;
	error = open_f_index(f, i);
	if (!error)
	{
		byte* d = new byte[64 << 10];
		int cb_d = hva_file_write(f.get_data(), f.get_size(), d);
		if (cb_d)
		{
			Cfile32 g;
			error = g.open_write(fname);
			if (!error)
			{
				error = g.write(d, cb_d);
				g.close();
			}
		}
		else
			error = 1;
		delete[] d;
		f.close();
	}
	return error;
}

int CXCCMixerView::copy_as_map_ts_preview(int i, Cfname fname) const
{
	int error = 0;
	fname.set_ext(".txt");
	Cpcx_file f;
	error = open_f_index(f, i);
	if (!error)
	{
		int cx = f.get_cx();
		int cy = f.get_cy();
		int cb_s = cx * cy * 3;
		byte* s = new byte[cx * cy * 3];
		if (f.get_c_planes() == 1)
		{
			byte* t = new byte[cx * cy];
			pcx_decode(f.get_image(), t, *f.get_header());
			convert_image_8_to_24(t, s, cx, cy, *f.get_palet());
			delete[] t;
		}
		else
			pcx_decode(f.get_image(), s, *f.get_header());
		byte* d = new byte[cx * cy * 6];
		int cb_d = encode5(s, d, cb_s);
		byte* e = new byte[cb_d << 1];
		int cb_e = encode64(d, e, cb_d);
		ofstream g(fname.get_all().c_str());
		g << "[Preview]" << endl
			<< "Size=0,0," << n(cx) << ',' << n(cy) << endl
			<< endl
			<< "[PreviewPack]" << endl;
		const byte* r = e;
		const byte* r_end = e + cb_e;
		int line_i = 1;
		while (r < r_end)
		{
			char line[80];
			int cb_line = min(r_end - r, 70);
			memcpy(line, r, cb_line);
			line[cb_line] = 0;
			r += cb_line;
			g << line_i++ << '=' << line << endl;
		}
		error = g.fail();
		delete[] e;
		delete[] d;
		delete[] s;
		f.close();
	}
	return error;
}

int CXCCMixerView::copy_as_pal(int i, Cfname fname) const
{
	int error = 0;
	fname.set_ext(".pal");
	Cpcx_file f;
	error = open_f_index(f, i);
	if (!error)
	{
		t_palet palet;
		memcpy(palet, f.get_palet(), sizeof(t_palet));
		convert_palet_24_to_18(palet);
		Cfile32 g;
		error = g.open_write(fname);
		if (!error)
		{
			error = g.write(palet, sizeof(t_palet));
			g.close();
		}
		f.close();
	}
	return error;
}

int CXCCMixerView::copy_as_pal_jasc(int i, Cfname fname) const
{
	int error = 0;
	fname.set_ext(".pal");
	Cpal_file f;
	error = open_f_index(f, i);
	if (!error)
	{
		error =  f.extract_as_pal_jasc(fname);
		f.close();
	}
	return error;
}

int CXCCMixerView::copy_as_pcx(int i, Cfname fname, t_file_type ft) const
{
	int error = 0;
	fname.set_ext(ft == ft_png ? ".png" : ".pcx");
	switch (m_index.find(get_id(i))->second.ft)
	{
	case ft_cps:
		{
			Ccps_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error = f.extract_as_pcx(fname, get_default_palet());
				f.close();
			}
			break;
		}
	case ft_pcx:
		{
			Cpcx_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error = f.extract_as_png(fname);
				f.close();
			}
			break;
		}
	case ft_shp_dune2:
		{
			Cshp_dune2_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error = f.extract_as_pcx(fname, get_default_palet());
				f.close();
			}
			break;
		}
	case ft_shp:
		{
			Cshp_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error = f.extract_as_pcx(fname, get_default_palet());
				f.close();
			}
			break;
		}
	case ft_shp_ts:
		{
			Cshp_ts_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error = f.extract_as_pcx(fname, ft, get_default_palet(), GetMainFrame()->combine_shadows());
				f.close();
			}
			break;
		}
	case ft_tmp_ra:
		{
			Ctmp_ra_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error = f.extract_as_pcx(fname, get_default_palet());
				f.close();
			}
			break;
		}
	case ft_tmp_ts:
		{
			Ctmp_ts_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error = f.extract_as_pcx(fname, get_default_palet());
				f.close();
			}
			break;
		}
	case ft_vqa:
		{
			Cvqa_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error = f.extract_as_pcx(fname, ft);
				f.close();
			}
			break;
		}
	case ft_wsa_dune2:
		{
			Cwsa_dune2_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error = f.extract_as_pcx(fname, get_default_palet());
				f.close();
			}
			break;
		}
	case ft_wsa:
		{
			Cwsa_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error = f.extract_as_pcx(fname);
				f.close();
			}
			break;
		}
	case ft_vxl:
		{
			Cvxl_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error = f.extract_as_pcx(fname, get_default_palet());
				f.close();
			}
			break;
		}
	}
	return error;
}

static string get_base_name(const string& fname)
{
	string t = Cfname(fname).get_ftitle();
	int p = -1;
	for (int i = 0; i < t.length(); i++)
	{
		if (!isdigit(t[i]))
			p = i;
	}
	return t.substr(0, p);
}

static int get_index_from_name(const string& base_name, const string& fname)
{
	string t = Cfname(fname).get_ftitle();
	if (t.substr(0, base_name.length()) != base_name)
		return -1;
	int p = -1;
	for (int i = 0; i < t.length(); i++)
	{
		if (!isdigit(t[i]))
			p = i;
	}
	return p == base_name.length() && p < t.length() ? atoi(t.substr(p).c_str()) : -1;
}

static void create_rp(const t_palet s1, const t_palet s2, byte* d, t_game game)
{
	d[0] = 0;
	for (int i = 1; i < 256; i++)
	{
		switch (game)
		{
		case game_td:
			if (i >= 0xb0 && i < 0xc0)
				d[i] = i - 0xa0;
			else
				d[i] = find_color_t(s1[i].r, s1[i].g, s1[i].b, s2);
			break;
		case game_ra:
			if (i >= 0x50 && i < 0x60)
				d[i] = i - 0x40;
			else
				d[i] = find_color_t(s1[i].r, s1[i].g, s1[i].b, s2);
			break;
		default:
			d[i] = find_color_t(s1[i].r, s1[i].g, s1[i].b, s2);
		}
	}
}

int CXCCMixerView::copy_as_shp(int i, Cfname fname) const
{
	int cx;
	int cy;
	int c_images;
	int error = 0;
	fname.set_ext(".shp");
	byte* s = NULL;
	t_palet s_palet;
	string base_name = get_base_name(fname);
	if (get_index_from_name(base_name, fname))
		return 0x102;
	Cpcx_file f;
	error = open_f_index(f, i);
	if (!error)
	{
		memcpy(s_palet, *f.get_palet(), sizeof(t_palet));
		cx = f.get_cx();
		cy = f.get_cy();
		c_images = 0;
		f.close();
		int index[1000];
		for (int i = 0; i < 1000; i++)
			index[i] = -1;
		for (t_index::const_iterator j = m_index.begin(); j != m_index.end(); j++)
		{
			int z = get_index_from_name(base_name, j->second.name);
			if (z != -1 && z < 1000)
				index[z] = j->first;
		}
		while (i--)
		{
			int id = index[i];
			if (id == -1)
				continue;
			if (open_f_id(f, id))
			{
				error = 1;
				break;
			}
			else
			{
				if (f.get_cx() != cx || f.get_cy() != cy)
					error = 0x100;
				else if (f.get_c_planes() != 1)
					error = 0x101;
				else if (!error)
				{
					if (!s)
					{
						c_images = i + 1;
						s = new byte[cx * cy * c_images];
					}
					pcx_decode(f.get_image(), s + cx * cy * i, *f.get_header());
				}
				f.close();
			}
		}
	}
	if (!error && s)
	{
		if (GetMainFrame()->use_palet_for_conversion())
		{
			byte rp[256];
			t_palet p;
			memcpy(p, get_default_palet(), sizeof(t_palet));
			convert_palet_18_to_24(p);
			create_rp(s_palet, p, rp);
			apply_rp(s, cx * cy * c_images, rp);
		}
		Cfile32 f;
		fname.set_title(base_name);
		error = f.open_write(fname);
		if (!error)
		{
			byte* d = new byte[sizeof(t_shp_ts_header) + (sizeof(t_shp_ts_image_header) + cx * cy) * c_images];
			const int cb_d = shp_file_write(s, d, cx, cy, c_images);
			error = f.write(d, cb_d);
			delete[] d;
			f.close();
		}
	}
	delete[] s;
	return error;
}

int CXCCMixerView::copy_as_shp_ts(int i, Cfname fname) const
{
	const bool convert_from_td = GetMainFrame()->convert_from_td();
	const bool convert_from_ra = GetMainFrame()->convert_from_ra();
	const bool convert_shadow = GetMainFrame()->split_shadows();
	const bool enable_compression = GetMainFrame()->enable_compression();
	// const bool remap_team_colors = GetMainFrame()->remap_team_colors();
	int cx;
	int cy;
	int c_images;
	int error = 0;
	fname.set_ext(".shp");
	byte* s = NULL;
	t_palet s_palet;
	string base_name = fname.get_ftitle();
	switch (m_index.find(get_id(i))->second.ft)
	{
	case ft_pcx:
		{
			base_name = get_base_name(fname);
			if (get_index_from_name(base_name, fname))
				return 0x102;
			Cpcx_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				memcpy(s_palet, *f.get_palet(), sizeof(t_palet));
				cx = f.get_cx();
				cy = f.get_cy();
				c_images = 0;
				f.close();
				int index[10000];
				for (int i = 0; i < 10000; i++)
					index[i] = -1;
				for (t_index::const_iterator j = m_index.begin(); j != m_index.end(); j++)
				{
					int z = get_index_from_name(base_name, j->second.name);
					if (z != -1 && z < 10000)
						index[z] = j->first;
				}
				while (i--)
				{
					int id = index[i];
					if (id == -1)
						continue;
					if (open_f_id(f, id))
					{
						error = 1;
						break;
					}
					else
					{
						if (f.get_cx() != cx || f.get_cy() != cy)
							error = 0x100;
						else if (f.get_c_planes() != 1)
							error = 0x101;
						else if (!error)
						{
							if (!s)
							{
								c_images = i + 1;
								if (convert_shadow)
									c_images <<= 1;
								s = new byte[cx * cy * c_images];
							}
							pcx_decode(f.get_image(), s + cx * cy * i, *f.get_header());
						}
						f.close();
					}
				}
			}
			break;
		}
	case ft_shp:
		{
			Cshp_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				memcpy(s_palet, GetMainFrame()->get_game_palet(convert_from_td ? game_td : game_ra), sizeof(t_palet));
				convert_palet_18_to_24(s_palet);
				cx = f.get_cx();
				cy = f.get_cy();
				c_images = f.get_c_images() << 1;
				void* p;
				s = new byte[cx * cy * c_images];
				byte* w = s;
				if (cx && cy && !shp_images::load_shp(f, p))
				{
					for (int i = 0; i < c_images >> 1; i++)
					{
						memcpy(w, shp_images::get_shp(p, i), cx * cy);
						w += cx * cy;
					}
					shp_images::destroy_shp(p);
				}
				f.close();
			}
			break;
		}
	}
	if (!error && s)
	{
		if (convert_shadow)
		{
			int count = cx * cy * (c_images >> 1);
			byte* r = s;
			byte* w = s + count;
			while (count--)
			{
				byte& v = *r++;
				if (v == 4)
				{
					v = 0;
					*w++ = 1;
				}
				else
					*w++ = 0;
			}
		}
		if (GetMainFrame()->use_palet_for_conversion())
		{
			byte rp[256];
			t_palet p;
			memcpy(p, get_default_palet(), sizeof(t_palet));
			convert_palet_18_to_24(p);
			if (convert_from_td)
				create_rp(s_palet, p, rp, game_td);
			else if (convert_from_ra)
				create_rp(s_palet, p, rp, game_ra);
			else
				create_rp(s_palet, p, rp);
			apply_rp(s, cx * cy * (c_images >> convert_shadow), rp);
		}
		Cfile32 f;
		fname.set_title(base_name);
		error = f.open_write(fname);
		if (!error)
		{
			byte* d = new byte[sizeof(t_shp_ts_header) + (sizeof(t_shp_ts_image_header) + cx * cy) * c_images];
			const int cb_d = shp_ts_file_write(s, d, cx, cy, c_images, enable_compression);
			error = f.write(d, cb_d);
			delete[] d;
			f.close();
		}
	}
	delete[] s;
	return error;
}

int CXCCMixerView::copy_as_text(int i, Cfname fname) const
{
	int error = 0;
	fname.set_ext(".txt");
	Cst_file f;
	error = open_f_index(f, i);
	if (!error)
	{
		error =  f.extract_as_text(fname);
		f.close();
	}
	return error;
}

int CXCCMixerView::copy_as_tmp_ts(int i, Cfname fname) const
{
	int error = 0;
	fname.set_ext(".tmp");
	Cpcx_file f;
	error = open_f_index(f, i);
	if (!error)
	{
		int cx = f.get_cx();
		int cy = f.get_cy();
		byte* s = new byte[cx * cy];
		pcx_decode(f.get_image(), s, *f.get_header());
		byte* d = new byte[256 << 10];
		int cb_d = tmp_ts_file_write(s, d, f.get_cx(), f.get_cy());
		delete[] s;
		if (cb_d)
		{
			Cfile32 g;
			error = g.open_write(fname);
			if (!error)
			{
				error = g.write(d, cb_d);
				g.close();
			}
		}
		else
			error = 1;
		delete[] d;
		f.close();
	}
	return error;
}

int CXCCMixerView::copy_as_vxl(int i, Cfname fname) const
{
	int error = 0;
	fname.set_ext(".vxl");
	switch (m_index.find(get_id(i))->second.ft)
	{
	case ft_pcx:
		{
			string base_name = get_base_name(fname);
			if (get_index_from_name(base_name, fname))
				return 0x102;
			Cpcx_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				int cx = f.get_cx();
				int cy = f.get_cy();
				int c_images = 0;
				byte* s = NULL;
				f.close();
				int index[256];
				for (int i = 0; i < 256; i++)
					index[i] = -1;
				for (t_index::const_iterator j = m_index.begin(); j != m_index.end(); j++)
				{
					int z = get_index_from_name(base_name, j->second.name);
					if (z != -1 && z < 256)
						index[z] = j->first;
				}
				while (i--)
				{
					int id = index[i];
					if (id == -1)
						continue;
					if (open_f_id(f, id))
					{
						error = 1;
						break;
					}
					else
					{
						if (f.get_cx() != cx || f.get_cy() != cy || f.get_c_planes() != 1)
							error = 0x0100;
						else if (!error)
						{
							if (!s)
							{
								c_images = i + 1;
								s = new byte[cx * cy * c_images];
							}
							pcx_decode(f.get_image(), s + cx * cy * i, *f.get_header());
						}
						f.close();
					}
				}
				if (!error)
				{
					byte* d = new byte[1 << 20];
					int cb_d = vxl_file_write(s, d, cx, cy, c_images);
					if (cb_d)
					{
						Cfile32 g;
						fname.set_title(base_name);
						error = g.open_write(fname);
						if (!error)
						{
							error = g.write(d, cb_d);
							g.close();
						}
					}
					else
						error = 1;
					delete[] d;
				}
			}
			break;
		}
	case ft_xif:
		{
			Cxif_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				Cxif_key k;
				error = k.load_key(f.get_data(), f.get_size());
				if (!error)
				{
					byte* d = new byte[1 << 20];
					int cb_d = vxl_file_write(k, d);
					if (cb_d)
					{
						Cfile32 g;
						error = g.open_write(fname);
						if (!error)
						{
							error = g.write(d, cb_d);
							g.close();
						}
					}
					else
						error = 1;
					delete[] d;
				}
				f.close();
			}
			break;
		}
	}
	return error;
}

int CXCCMixerView::copy_as_wav_ima_adpcm(int i, Cfname fname) const
{
	int error = 0;
	fname.set_ext(".wav");
	switch (m_index.find(get_id(i))->second.ft)
	{
	case ft_wav:
		{
			Cwav_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error = f.process();
				if (!error)
				{
					const t_riff_wave_format_chunk& format_chunk = f.get_format_chunk();
					if (format_chunk.tag != 1 
						|| format_chunk.c_channels != 1 && format_chunk.c_channels != 2
						|| format_chunk.cbits_sample != 16)
						error = 0x100;
					else
					{						
						int cb_s = f.get_data_header().size;
						byte* s = new byte[cb_s];
						f.seek(f.get_data_ofs());
						if (!f.read(s, cb_s))
						{
							int c_channels = format_chunk.c_channels;
							Cima_adpcm_wav_encode encode;
							encode.load(reinterpret_cast<short*>(s), cb_s, c_channels);
							int c_samples = encode.c_samples();
							int cb_audio = encode.cb_data();
							int cb_d = sizeof(t_wav_ima_adpcm_header) + cb_audio;
							byte* d = new byte[cb_d];
							byte* w = d;
							w += wav_ima_adpcm_file_write_header(w, cb_audio, c_samples, format_chunk.samplerate, c_channels);
							memcpy(w, encode.data(), cb_audio);
							error = file32_write(fname, d, cb_d);
							delete[] d;

						}
						delete[] s;
					}
				}
				f.close();
			}
			break;
		}
	}
	return error;
}

int CXCCMixerView::copy_as_wav_pcm(int i, Cfname fname) const
{
	int error = 0;
	fname.set_ext(".wav");
	switch (m_index.find(get_id(i))->second.ft)
	{
	case ft_aud:
		{
			Caud_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error =  f.extract_as_wav(fname);
				f.close();
			}
			break;
		}
	case ft_voc:
		{
			Cvoc_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error =  f.extract_as_wav(fname);
				f.close();
			}
			break;
		}
	case ft_vqa:
		{
			Cvqa_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error =  f.extract_as_wav(fname);
				f.close();
			}
			break;
		}
	case ft_wav:
		{
			Cwav_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error = f.process();
				if (!error)
				{
					const t_riff_wave_format_chunk& format_chunk = f.get_format_chunk();
					if (format_chunk.tag != 0x11 
						|| format_chunk.c_channels != 1 && format_chunk.c_channels != 2
						|| format_chunk.cbits_sample != 4)
						error = 0x100;
					else
					{						
						int cb_s = f.get_data_header().size;
						byte* s = new byte[cb_s];
						f.seek(f.get_data_ofs());
						if (!f.read(s, cb_s))
						{
							int c_channels = format_chunk.c_channels;
							int c_samples = f.get_fact_chunk().c_samples;
							int cb_audio = c_channels * c_samples << 1;
							int cb_d = sizeof(t_wav_header) + cb_audio;
							byte* d = new byte[cb_d];
							byte* w = d;
							w += wav_file_write_header(w, c_samples, format_chunk.samplerate, 2, c_channels);
							Cima_adpcm_wav_decode decode;
							decode.load(s, cb_s, c_channels, 512 * c_channels);
							memcpy(w, decode.data(), cb_audio);
							error = file32_write(fname, d, cb_d);
							delete[] d;

						}
						delete[] s;
					}
				}
				f.close();
			}
			break;
		}
	}
	return error;
}

int CXCCMixerView::copy_as_xif(int i, Cfname fname) const
{
	int error = 0;
	fname.set_ext(".xif");
	Cvxl_file f;
	error = open_f_index(f, i);
	if (!error)
	{
		error =  f.extract_as_xif(fname);
		f.close();
	}
	return error;
}

void CXCCMixerView::OnPopupCopy()
{
	copy_as(static_cast<t_file_type>(-1));
}

void CXCCMixerView::OnUpdatePopupCopy(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy());
}

void CXCCMixerView::OnPopupCopyAsAUD()
{
	copy_as(ft_aud);
}

void CXCCMixerView::OnUpdatePopupCopyAsAUD(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_aud));
}

void CXCCMixerView::OnPopupCopyAsAVI()
{
	copy_as(ft_avi);
}

void CXCCMixerView::OnUpdatePopupCopyAsAVI(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_avi));
}

void CXCCMixerView::OnPopupCopyAsCPS()
{
	copy_as(ft_cps);
}

void CXCCMixerView::OnUpdatePopupCopyAsCPS(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_cps));
}

void CXCCMixerView::OnPopupCopyAsCSV()
{
	copy_as(ft_csv);
}

void CXCCMixerView::OnUpdatePopupCopyAsCSV(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_csv));
}

void CXCCMixerView::OnPopupCopyAsHTML()
{
	copy_as(ft_html);
}

void CXCCMixerView::OnUpdatePopupCopyAsHTML(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_html));
}

void CXCCMixerView::OnPopupCopyAsHVA()
{
	copy_as(ft_hva);
}

void CXCCMixerView::OnUpdatePopupCopyAsHVA(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_hva));
}

void CXCCMixerView::OnPopupCopyAsMapTsPreview()
{
	copy_as(ft_map_ts_preview);
}

void CXCCMixerView::OnUpdatePopupCopyAsMapTsPreview(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_map_ts_preview));
}

void CXCCMixerView::OnPopupCopyAsPAL()
{
	copy_as(ft_pal);
}

void CXCCMixerView::OnUpdatePopupCopyAsPAL(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_pal));
}

void CXCCMixerView::OnPopupCopyAsPAL_JASC()
{
	copy_as(ft_pal_jasc);
}

void CXCCMixerView::OnUpdatePopupCopyAsPAL_JASC(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_pal_jasc));
}

void CXCCMixerView::OnPopupCopyAsPCX()
{
	copy_as(ft_pcx);
}

void CXCCMixerView::OnUpdatePopupCopyAsPCX(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_pcx));
}

void CXCCMixerView::OnPopupCopyAsPNG() 
{
	copy_as(ft_png);
}

void CXCCMixerView::OnUpdatePopupCopyAsPNG(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(can_copy_as(ft_png));
}

void CXCCMixerView::OnPopupCopyAsSHP()
{
	copy_as(ft_shp);
}

void CXCCMixerView::OnUpdatePopupCopyAsSHP(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_shp));
}

void CXCCMixerView::OnPopupCopyAsShHP_TS()
{
	copy_as(ft_shp_ts);
}

void CXCCMixerView::OnUpdatePopupCopyAsSHP_TS(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_shp_ts));
}

void CXCCMixerView::OnPopupCopyAsText()
{
	copy_as(ft_text);
}

void CXCCMixerView::OnUpdatePopupCopyAsText(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_text));
}

void CXCCMixerView::OnPopupCopyAsTMP_TS()
{
	copy_as(ft_tmp_ts);
}

void CXCCMixerView::OnUpdatePopupCopyAsTMP_TS(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_tmp_ts));
}

void CXCCMixerView::OnPopupCopyAsWavImaAdpcm() 
{
	copy_as(ft_wav_ima_adpcm);
}

void CXCCMixerView::OnUpdatePopupCopyAsWavImaAdpcm(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(can_copy_as(ft_wav_ima_adpcm));
}

void CXCCMixerView::OnPopupCopyAsWavPcm() 
{
	copy_as(ft_wav_pcm);
}

void CXCCMixerView::OnUpdatePopupCopyAsWavPcm(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(can_copy_as(ft_wav_pcm));
}

void CXCCMixerView::OnPopupCopyAsWSA()
{
	copy_as(ft_wsa);
}

void CXCCMixerView::OnUpdatePopupCopyAsWSA(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_wsa));
}

void CXCCMixerView::OnPopupCopyAsVXL()
{
	copy_as(ft_vxl);
}

void CXCCMixerView::OnUpdatePopupCopyAsVXL(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_vxl));
}

void CXCCMixerView::OnPopupCopyAsXIF()
{
	copy_as(ft_xif);
}

void CXCCMixerView::OnUpdatePopupCopyAsXIF(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_xif));
}

void CXCCMixerView::OnPopupDelete()
{
	for (t_index_selected::const_iterator i = m_index_selected.begin(); i != m_index_selected.end(); i++)
	{
		string name = m_dir + m_index.find(get_id(*i))->second.name;
		DeleteFile((m_dir + m_index.find(get_id(*i))->second.name).c_str());
	}
	update_list();
}

void CXCCMixerView::OnUpdatePopupDelete(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!m_mix_f && can_delete());
}

t_game CXCCMixerView::get_game()
{
	t_game r = GetMainFrame()->get_game();
	return r == -1 ? m_game : r;
}

void CXCCMixerView::OnPopupOpen()
{
	int id = get_current_id();
	if (m_mix_f)
		open_location_mix(get_current_id());
	else
		open_location_mix(m_dir + m_index.find(id)->second.name);
}

void CXCCMixerView::OnUpdatePopupOpen(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(get_current_id() != -1 &&
		m_index.find(get_current_id())->second.ft == ft_mix);
}

void CXCCMixerView::OnPopupOpenForEdit()
{
}

void CXCCMixerView::OnUpdatePopupOpenForEdit(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(false);
}

void CXCCMixerView::OnPopupOpenWithFinalsun()
{
	Ccc_file f(false);
	if (open_f_index(f, get_current_index()))
	{
	}
	else
	{
		const string fname = xcc_dirs::get_ts_dir() + m_index.find(get_current_id())->second.name;
		f.extract(fname);
		f.close();
		ShellExecute(m_hWnd, "open", GetApp()->get_fs_exe().c_str(), fname.c_str(), NULL, SW_SHOW);
	}
}

void CXCCMixerView::OnUpdatePopupOpenWithFinalsun(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(get_current_id() != -1 &&
		m_index.find(get_current_id())->second.ft == ft_map_ts &&
		GetApp()->is_fs_available());
}

void CXCCMixerView::OnPopupPlay()
{
	CWaitCursor wait;
	Ccc_file f(true);
	if (!open_f_index(f, get_current_index()))
	{
		m_xap.ds(GetMainFrame()->get_ds());
		m_xap.load(f.get_data(), f.get_size());
		f.close();
		m_xap.play();
	}
}

void CXCCMixerView::OnUpdatePopupPlay(CCmdUI* pCmdUI)
{
	if (!m_xap.busy())
	{
		int id = get_current_id();
		if (id != -1)
		{
			switch (m_index.find(get_current_id())->second.ft)
			{
			case ft_aud:
			case ft_voc:
			case ft_wav:
				pCmdUI->Enable(static_cast<bool>(GetMainFrame()->get_ds()));
				return;
			case ft_vqa:
				pCmdUI->Enable(GetMainFrame()->get_dd() && GetMainFrame()->get_ds());
				return;
			}
		}
	}
	pCmdUI->Enable(false);
}

void CXCCMixerView::OnPopupRefresh()
{
	update_list();
}

void CXCCMixerView::OnUpdatePopupRefresh(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_accept());
}

void CXCCMixerView::OnPopupResize()
{
	int id = get_current_id();
	Cshp_ts_file f;
	int error = open_f_index(f, get_current_index());
	if (!error)
	{
		const int global_cx = f.get_cx();
		const int global_cy = f.get_cy();
		CResizeDlg dlg;
		dlg.set_size(global_cx, global_cy);
		if (IDOK == dlg.DoModal())
		{
			const int global_cx_d = dlg.get_cx();
			const int global_cy_d = dlg.get_cy();
			const int c_images = f.get_c_images();
			t_palet palet;
			convert_palet_18_to_24(get_default_palet(), palet);
			palet[0].r = palet[0].b = 0xff;
			palet[0].g = 0;
			byte* rp = global_cx_d * global_cy_d * c_images > 1 << 18 ? new byte[1 << 18] : NULL;
			if (rp)
				create_downsample_table(palet, rp);
			byte* d8 = new byte[global_cx_d * global_cy_d * c_images];
			byte* d24 = new byte[global_cx_d * global_cy_d * 3];
			byte* image8 = new byte[global_cx * global_cy];
			byte* image24 = new byte[global_cx * global_cy * 3];
			for (int i = 0; i < c_images; i++)
			{
				set_msg("Resize: " + n(i * 100 / c_images) + "%");
				const int cx = f.get_cx(i);
				const int cy = f.get_cy(i);
				byte* image = new byte[cx * cy];
				const byte* r;
				if (f.is_compressed(i))
				{
					decode3(f.get_image(i), image, cx, cy);
					r = image;
				}
				else
					r = f.get_image(i);
				memset(image8, 0, global_cx * global_cy);
				byte* w = image8 + f.get_x(i) + global_cx * f.get_y(i);
				for (int y = 0; y < cy; y++)
				{
					memcpy(w, r, cx);
					r += cx;
					w += global_cx;
				}
				delete[] image;
				convert_image_8_to_24(image8, image24, global_cx, global_cy, palet);
				if (global_cx < global_cx_d)
					resize_image_up(image24, d24, global_cx, global_cy, 3, global_cx_d, global_cy_d);
				else
					resize_image_down(image24, d24, global_cx, global_cy, 3, global_cx_d, global_cy_d);
				if (rp)
					convert_image_24_to_8(d24, d8 + global_cx_d * global_cy_d * i, global_cx_d, global_cy_d, rp);
				else
					convert_image_24_to_8(d24, d8 + global_cx_d * global_cy_d * i, global_cx_d, global_cy_d, palet);
			}
			Cfile32 g;
			Cfname fname = get_dir() + m_index.find(id)->second.name;
			error = g.open_write(fname);
			if (!error)
			{
				byte* d = new byte[sizeof(t_shp_ts_header) + (sizeof(t_shp_ts_image_header) + global_cx_d * global_cy_d) * c_images];
				error = g.write(d, shp_ts_file_write(d8, d, global_cx_d, global_cy_d, c_images));
				delete[] d;
				g.close();
			}
			delete[] image24;
			delete[] image8;
			delete[] d24;
			delete[] d8;
			delete[] rp;
			set_msg("Resize " + fname.get_ftitle() + (error ? " failed, error " + n(error) : " succeeded"));
			update_list();
		}
		f.close();
	}
}

void CXCCMixerView::OnUpdatePopupResize(CCmdUI* pCmdUI)
{
	int id = get_current_id();
	if (can_accept() && id != -1)
	{
		switch (m_index.find(get_current_id())->second.ft)
		{
		case ft_shp_ts:
			pCmdUI->Enable(true);
			return;
		}
	}
	pCmdUI->Enable(false);
}

void CXCCMixerView::OnPopupImportIntoTS()
{
	Cxif_key k;
	Ccc_file f(true);
	int error = open_f_index(f, get_current_index());
	if (!error)
	{
		error = k.load_key(f.get_data(), f.get_size());
		f.close();
		if (!error)
		{
			Cextract_object eo;
			eo.open_default(game_ts);
			error = eo.insert(k);
		}
	}
}

void CXCCMixerView::OnUpdatePopupImportIntoTS(CCmdUI* pCmdUI)
{
	int id = get_current_id();
	if (!xcc_dirs::get_ts_dir().empty() && id != -1)
	{
		switch (m_index.find(get_current_id())->second.ft)
		{
		case ft_xif:
			pCmdUI->Enable(true);
			return;
		}
	}
	pCmdUI->Enable(false);
}

void CXCCMixerView::OnPopupImportIntoRa2() 
{
	Cxif_key k;
	Ccc_file f(true);
	int error = open_f_index(f, get_current_index());
	if (!error)
	{
		error = k.load_key(f.get_data(), f.get_size());
		f.close();
		if (!error)
		{
			Cextract_object eo;
			eo.open_default(game_ra2);
			error = eo.insert(k);
		}
	}
}

void CXCCMixerView::OnUpdatePopupImportIntoRa2(CCmdUI* pCmdUI) 
{
	int id = get_current_id();
	if (!xcc_dirs::get_ra2_dir().empty() && id != -1)
	{
		switch (m_index.find(get_current_id())->second.ft)
		{
		case ft_xif:
			pCmdUI->Enable(true);
			return;
		}
	}
	pCmdUI->Enable(false);
}

