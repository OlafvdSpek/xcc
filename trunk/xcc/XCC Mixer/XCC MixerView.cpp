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
#include <strstream>
#include <id_log.h>
#include <pal_file.h>
#include <string_conversion.h>
#include "aud_decode.h"
#include "aud_file.h"
#include "aud_file_write.h"
#include "big_edit.h"
#include "big_file_write.h"
#include "cps_file.h"
#include "dds_file.h"
#include "dlg_shp_viewer.h"
#include "extract_object.h"
#include "hva_file.h"
#include "ima_adpcm_wav_decode.h"
#include "ima_adpcm_wav_encode.h"
#include "image_tools.h"
#include "jpeg_file.h"
#include "map_ts_encoder.h"
#include "map_ts_ini_reader.h"
#include "mix_edit.h"
#include "mix_file_write.h"
#include "mix_rg_edit.h"
#include "mix_rg_file_write.h"
#include "pal_file.h"
#include "pcx_decode.h"
#include "pcx_file.h"
#include "pkt_ts_ini_reader.h"
#include "resizedlg.h"
#include "shp_decode.h"
#include "shp_dune2_file.h"
#include "shp_file.h"
#include "shp_images.h"
#include "shp_properties_dlg.h"
#include "shp_ts_file.h"
#include "shp_ts_file_write.h"
#include "st_file.h"
#include "text_file.h"
#include "tmp_file.h"
#include "tmp_ra_file.h"
#include "tmp_ts_file.h"
#include "virtual_tfile.h"
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
	ON_COMMAND(ID_POPUP_COPY_AS_SHP_TS, OnPopupCopyAsSHP_TS)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_SHP_TS, OnUpdatePopupCopyAsSHP_TS)
	ON_COMMAND(ID_POPUP_COPY_AS_TMP_TS, OnPopupCopyAsTMP_TS)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_TMP_TS, OnUpdatePopupCopyAsTMP_TS)
	ON_COMMAND(ID_POPUP_COPY_AS_PAL_JASC, OnPopupCopyAsPAL_JASC)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_PAL_JASC, OnUpdatePopupCopyAsPAL_JASC)
	ON_COMMAND(ID_POPUP_COPY_AS_TEXT, OnPopupCopyAsText)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_TEXT, OnUpdatePopupCopyAsText)
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
	ON_COMMAND(ID_POPUP_COPY_AS_PCX_SINGLE, OnPopupCopyAsPcxSingle)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_PCX_SINGLE, OnUpdatePopupCopyAsPcxSingle)
	ON_COMMAND(ID_POPUP_CLIPBOARD_COPY, OnPopupClipboardCopy)
	ON_UPDATE_COMMAND_UI(ID_POPUP_CLIPBOARD_COPY, OnUpdatePopupClipboardCopy)
	ON_COMMAND(ID_POPUP_COPY_AS_PNG_SINGLE, OnPopupCopyAsPngSingle)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_PNG_SINGLE, OnUpdatePopupCopyAsPngSingle)
	ON_COMMAND(ID_POPUP_CLIPBOARD_PASTE_AS_PCX, OnPopupClipboardPasteAsPcx)
	ON_UPDATE_COMMAND_UI(ID_POPUP_CLIPBOARD_PASTE_AS_PCX, OnUpdatePopupClipboardPasteAsImage)
	ON_COMMAND(ID_POPUP_CLIPBOARD_PASTE_AS_SHP_TS, OnPopupClipboardPasteAsShpTs)
	ON_UPDATE_COMMAND_UI(ID_POPUP_CLIPBOARD_PASTE_AS_SHP_TS, OnUpdatePopupClipboardPasteAsVideo)
	ON_COMMAND(ID_POPUP_CLIPBOARD_PASTE_AS_PNG, OnPopupClipboardPasteAsPng)
	ON_COMMAND(ID_POPUP_OPEN_WITH_FINALALERT, OnPopupOpenWithFinalalert)
	ON_UPDATE_COMMAND_UI(ID_POPUP_OPEN_WITH_FINALALERT, OnUpdatePopupOpenWithFinalalert)
	ON_COMMAND(ID_POPUP_COPY_AS_JPEG, OnPopupCopyAsJpeg)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_JPEG, OnUpdatePopupCopyAsJpeg)
	ON_COMMAND(ID_POPUP_CLIPBOARD_PASTE_AS_JPEG, OnPopupClipboardPasteAsJpeg)
	ON_COMMAND(ID_POPUP_EXPLORE, OnPopupExplore)
	ON_UPDATE_COMMAND_UI(ID_POPUP_EXPLORE, OnUpdatePopupExplore)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_POPUP_COMPACT, OnPopupCompact)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COMPACT, OnUpdatePopupCompact)
	ON_COMMAND(ID_POPUP_COPY_AS_TGA, OnPopupCopyAsTga)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPY_AS_TGA, OnUpdatePopupCopyAsTga)
	ON_UPDATE_COMMAND_UI(ID_POPUP_CLIPBOARD_PASTE_AS_PNG, OnUpdatePopupClipboardPasteAsImage)
	ON_UPDATE_COMMAND_UI(ID_POPUP_CLIPBOARD_PASTE_AS_JPEG, OnUpdatePopupClipboardPasteAsImage)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

enum t_error_message
{
	em_bad_fname = 0x400,
	em_bad_depth,
	em_bad_size
};

const char* error_messages[] =
{
	"Bad filename. All files should have a name like \"image ####.pcx\" where #### is the zero based index.",
	"Bad color depth. Only 8-bit images are supported.",
	"Bad size. All images should have the same size."
};

/////////////////////////////////////////////////////////////////////////////
// CXCCMixerView construction/destruction

static CXCCMixerApp* GetApp()
{
	return static_cast<CXCCMixerApp*>(AfxGetApp());
}

static CMainFrame* GetMainFrame()
{
	return static_cast<CMainFrame*>(AfxGetMainWnd());
}

CXCCMixerView::CXCCMixerView()
{
	m_mix_f = NULL;
	m_reading = false;
}

CXCCMixerView::~CXCCMixerView()
{
}

BOOL CXCCMixerView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

static int c_colums = 4;
static char* column_label[] = {"Name", "Type", "Size", "Description"};
static int column_alignment[] = {LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_LEFT};

void CXCCMixerView::OnInitialUpdate()
{
	char dir[MAX_PATH];
	if (GetCurrentDirectory(MAX_PATH, dir))
	{
		Cfname fn = dir;
		fn.make_path();
		m_dir = fn.get_all();
	}
	else
		m_dir = "c:\\";
	{
		string dir = AfxGetApp()->GetProfileString(m_reg_key, "path", m_dir.c_str());
		string fname = dir + "write_check.temp";
		if (!file32_write(fname, NULL, 0))
		{
			delete_file(fname);
			m_dir = dir;
		}
	}
	CListView::OnInitialUpdate();
	GetListCtrl().SetExtendedStyle(GetListCtrl().GetExtendedStyle() | LVS_EX_FULLROWSELECT);
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
// CXCCMixerView message handlers

void CXCCMixerView::OnFileNew()
{
	const char* save_filter = "Red Alert MIXs (*.mix)|*.mix|Tiberian Sun MIXs (*.mix)|*.mix|Red Alert 2 MIXs (*.mix)|*.mix|Renegade MIXs (*.mix)|*.mix|Generals BIGs (*.big)|*.big|";

	close_all_locations();
	CFileDialog dlg(false, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, save_filter, this);
	dlg.m_ofn.nFilterIndex = 3;
	if (IDOK == dlg.DoModal())
	{
		string name = dlg.GetPathName();
		int error = 0;
		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1:
			error = Cmix_file_write(game_ra).write().export(name);
			break;
		case 2:
			error = Cmix_file_write(game_ts).write().export(name);
			break;
		case 3:
			error = Cmix_file_write(game_ra2).write().export(name);
			break;
		case 4:
			error = Cmix_rg_file_write().write().export(name);
			break;
		case 5:
			error = Cbig_file_write().write().export(name);
			break;
		default:
			assert(false);
		}
		update_list();
	}
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
	if (m_mix_f)
		close_location(true);
	else
	{
		int i = m_dir.rfind('\\');
		if (i != string::npos)
		{
			i = m_dir.rfind('\\', i - 1);
			if (i != string::npos)
				open_location_dir(m_dir.substr(0, i + 1));
		}
	}
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
		m_mix_fname = name;
	}
	update_list();
}

void CXCCMixerView::open_location_mix(t_mix_map_list::const_iterator i, int file_id)
{
	typedef stack<int> t_stack;
	t_stack stack;
	close_all_locations();
	const t_mix_map_list& mix_list = GetMainFrame()->mix_map_list();
	while (i->second.fname.empty())
	{
		stack.push(i->second.id);
		i = mix_list.find(i->second.parent);
	}
	open_location_mix(i->second.fname);
	while (!stack.empty())
	{
		open_location_mix(stack.top());
		stack.pop();
	}
	if (file_id)
	{
		CListCtrl& lc = GetListCtrl();
		LVFINDINFO lvf;
		lvf.flags = LVFI_PARAM;
		lvf.lParam = file_id;
		int i = lc.FindItem(&lvf, -1);
		if (i != -1)
		{
			lc.SetItemState(i, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
			lc.EnsureVisible(i, false);
		}
	}
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
	DragAcceptFiles(can_edit());
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
			if (e.name.empty())
				e.name = nh(8, id);
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
				e.name = drive_name;
				e.ft = ft_drive;
				e.size = -1;
				e.description = "";
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
				e.size = -1;
				if (finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (e.name == ".")
						continue;
					e.ft = ft_dir;
				}
				else
					e.ft = static_cast<t_file_type>(-1);
				int id = Cmix_file::get_id(get_game(), finddata.cFileName);
				e.description = mix_database::get_description(get_game(), id);
				m_index[id] = e;
			}
			while (FindNextFile(findhandle, &finddata));
			FindClose(findhandle);
		}
	}
	SetRedraw(false);
	CListCtrl& lc = GetListCtrl();
	for (t_index::iterator i = m_index.begin(); i != m_index.end(); i++)
	{
		int index = lc.InsertItem(lc.GetItemCount(), LPSTR_TEXTCALLBACK);
		lc.SetItemData(index, i->first);
	}
	sort_list(0, false);
	sort_list(1, false);
	SetRedraw(true);
	autosize_colums();
	m_reading = true;
}

void CXCCMixerView::autosize_colums()
{
	SetRedraw(false);
	CListCtrl& lc = GetListCtrl();
	for (int i = 0; i < c_colums; i++)
		lc.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	SetRedraw(true);
}

void CXCCMixerView::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	CListCtrl& lc = GetListCtrl();
	m_buffer[++m_buffer_w &= 3].erase();
	const t_index_entry&  e = m_index.find(pDispInfo->item.lParam)->second;
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		m_buffer[m_buffer_w] = e.name;
		break;
	case 1:
		if (e.ft != -1)
			m_buffer[m_buffer_w] = ft_name[e.ft];
		break;
	case 2:
		if (e.size != -1)
			m_buffer[m_buffer_w] = n(e.size);
		break;
	case 3:
		m_buffer[m_buffer_w] = e.description;
		break;
	}
	pDispInfo->item.pszText = const_cast<char*>(m_buffer[m_buffer_w].c_str());
	*pResult = 0;
}

template <class T>
static int compare(const T& a, const T& b)
{
	return a < b ? -1 : a != b;
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
		return ::compare(to_lower(a.name), to_lower(b.name));
	case 1:
		return ::compare(a.ft, b.ft);
	case 2:
		return ::compare(a.size, b.size);
	case 3:
		return ::compare(a.description, b.description);
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
		open_item(id);
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

bool CXCCMixerView::can_edit() const
{
	return m_location.size() < 2;
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
	case ft_dds:
		return d == ft_clipboard || d == ft_jpeg || d == ft_pcx || d == ft_png || ft_tga;
	case ft_hva:
		return d == ft_csv;
	case ft_jpeg:
		return d == ft_clipboard;
	case ft_pal:
		return d == ft_pal_jasc;
	case ft_pcx:
		return d == ft_clipboard || d == ft_cps || d == ft_map_ts_preview || d == ft_pal || d == ft_png || d == ft_shp || d == ft_shp_ts || d == ft_tmp_ts || d == ft_vxl;
	case ft_st:
		return d == ft_text;
	case ft_shp:
		return d == ft_pcx || d == ft_shp_ts;
	case ft_shp_ts:
		return d == ft_clipboard || d == ft_jpeg || d == ft_pcx_single || d == ft_pcx || d == ft_png_single || d == ft_png;
	case ft_text:
		return d == ft_html || d == ft_hva || d == ft_vxl;
	case ft_vqa:
		return d == ft_avi || d == ft_jpeg || d == ft_pcx  || d == ft_png || d == ft_wav_pcm;
	case ft_vxl:
		return d == ft_pcx || d == ft_text || d == ft_xif;
	case ft_wav:
		return d == ft_aud || d == ft_wav_ima_adpcm || d == ft_wav_pcm;
	case ft_xif:
		return d == ft_html || d == ft_text || d == ft_vxl;
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
	string v = "Copy " + fname.get_ftitle() + " failed, error " + n(error);
	if (error & 0x400)
	{
		v += ": ";
		v += error_messages[error & 0x3ff];
	}
	set_msg(v);
}

static void copy_succeeded(const Cfname& fname)
{
	set_msg("Copy " + fname.get_ftitle() + " succeeded");
}

void CXCCMixerView::copy_as(t_file_type ft) const
{
	CWaitCursor wait;
	int error;
	for (t_index_selected::const_iterator i = m_index_selected.begin(); i != m_index_selected.end(); i++)
	{
		const Cfname fname = m_other_pane->get_dir() + m_index.find(get_id(*i))->second.name;
		if (m_index.find(get_id(*i))->second.name.find('\\') != string::npos)
			create_deep_dir(m_other_pane->get_dir(), Cfname(m_index.find(get_id(*i))->second.name).get_path());
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
		case ft_jpeg:
		case ft_pcx:
		case ft_png:
		case ft_tga:
			error = copy_as_pcx(*i, fname, ft);
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
		case ft_pcx_single:
		case ft_png_single:
			error = copy_as_pcx_single(*i, fname, ft);
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
		if (f.cx() != 320 || f.cy() != 200)
			error = 257;
		else if (f.get_c_planes() != 1)
			error = 258;
		else
		{
			Cvirtual_binary s;
			pcx_decode(f.get_image(), s.write_start(320 * 200), *f.get_header());
			t_palet palet;
			memcpy(palet, f.get_palet(), sizeof(t_palet));
			convert_palet_24_to_18(palet);
			error = cps_file_write(s, palet).export(fname);
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
	Ccc_file f(true);
	error = open_f_index(f, i);
	if (!error)
	{
		switch (f.get_file_type(false))
		{
		case ft_map_ts:
			{
				Cmap_ts_ini_reader ir;
				ir.fast(true);
				ir.process(f.get_data(), f.get_size());
				strstream ini;
				Cmap_ts_encoder encoder(ini, true);
				Cmap_ts_encoder::t_header header;
				header.cx = ir.get_map_data().size_right;
				header.cy = ir.get_map_data().size_bottom;
				encoder.header(header);
				encoder.process(f.get_data(), f.get_size());
				ir.write_report(ofstream(fname.get_all().c_str()), fname, encoder);
			}
			break;
		case ft_pkt_ts:
			{
				Cpkt_ts_ini_reader ir;
				ir.process(f.get_data(), f.get_size());
				ir.write_report(ofstream(fname.get_all().c_str()));
			}
			break;
		case ft_xif:
			{
				Cxif_key k;
				error = k.load_key(f.get_data(), f.get_size());
				if (!error)
				{
					char d[64 << 10];
					Cextract_object::report(k, d, "");
					ofstream(fname.get_all().c_str()) << d;
				}
			}
			break;
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
		error = hva_file_write(f.get_data(), f.get_size()).export(fname);
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
		int cx = f.cx();
		int cy = f.cy();
		Cvirtual_binary s(NULL, cx * cy * 3);
		if (f.get_c_planes() == 1)
		{
			byte* t = new byte[cx * cy];
			pcx_decode(f.get_image(), t, *f.get_header());
			convert_image_8_to_24(t, s.data_edit(), cx, cy, *f.get_palet());
			delete[] t;
		}
		else
			pcx_decode(f.get_image(), s.data_edit(), *f.get_header());
		Cvirtual_binary d;
		d.size(encode5(s, d.write_start(cx * cy * 6), s.size(), 5));
		Cvirtual_binary e = encode64(d);
		ofstream g(fname.get_all().c_str());
		g << "[Preview]" << endl
			<< "Size=0,0," << cx << ',' << cy << endl
			<< endl
			<< "[PreviewPack]" << endl;
		const byte* r = e;
		int line_i = 1;
		while (r < e.data_end())
		{
			char line[80];
			int cb_line = min(e.data_end() - r, 70);
			memcpy(line, r, cb_line);
			line[cb_line] = 0;
			r += cb_line;
			g << line_i++ << '=' << line << endl;
		}
		error = g.fail();
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
		error = file32_write(fname, palet, sizeof(t_palet));
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

int CXCCMixerView::copy_as_pcx_single(int i, Cfname fname, t_file_type ft) const
{
	int error = 0;
	fname.set_ext(ft == ft_png_single ? ".png" : ".pcx");
	switch (m_index.find(get_id(i))->second.ft)
	{
	case ft_shp_ts:
		{
			Cshp_ts_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error = f.extract_as_pcx_single(fname, ft == ft_png_single? ft_png : ft_pcx, get_default_palet(), GetMainFrame()->combine_shadows());
				f.close();
			}
			break;
		}
	}
	return error;
}

int CXCCMixerView::copy_as_pcx(int i, Cfname fname, t_file_type ft) const
{
	int error = 0;
	switch (ft)
	{
	case ft_jpeg:
		fname.set_ext(".jpeg");
		break;
	case ft_pcx:
		fname.set_ext(".pcx");
		break;
	case ft_tga:
		fname.set_ext(".tga");
		break;
	default:
		fname.set_ext(".png");
	}	
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
	case ft_dds:
		{
			Cdds_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				Cvirtual_image image = f.vimage();
				image.remove_alpha();
				error = image.save(fname, ft);
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
		cx = f.cx();
		cy = f.cy();
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
				if (f.cx() != cx || f.cy() != cy)
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
		fname.set_title(base_name);
		error = shp_file_write(s, cx, cy, c_images).export(fname);
	}
	delete[] s;
	return error;
}

int CXCCMixerView::copy_as_shp_ts(int i, Cfname fname) const
{
	const bool convert_from_td = GetMainFrame()->convert_from_td();
	const bool convert_from_ra = GetMainFrame()->convert_from_ra();
	const bool convert_shadow = GetMainFrame()->split_shadows();
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
				return em_bad_fname;
			Cpcx_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				memcpy(s_palet, *f.get_palet(), sizeof(t_palet));
				cx = f.cx();
				cy = f.cy();
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
						if (f.cx() != cx || f.cy() != cy)
							error = em_bad_size;
						else if (f.get_c_planes() != 1)
							error = em_bad_depth;
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
		if (GetMainFrame()->fix_shadows() && ~c_images & 1)
		{
			int count = cx * cy * (c_images >> 1);
			for (byte* w = s + count; count--; w++)
			{
				if (*w)
					*w = 1;
			}
		}
		fname.set_title(base_name);
		error = shp_ts_file_write(s, cx, cy, c_images, GetMainFrame()->enable_compression()).export(fname);
	}
	delete[] s;
	return error;
}

int CXCCMixerView::copy_as_text(int i, Cfname fname) const
{
	int error = 0;
	fname.set_ext(".txt");
	switch (m_index.find(get_id(i))->second.ft)
	{
	case ft_st:
		{
			Cst_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				error =  f.extract_as_text(fname);
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
				error =  f.extract_as_text(ofstream(static_cast<string>(fname).c_str()));
				f.close();
			}
			break;
		}
	case ft_xif:
		{
			Cxif_file f;
			error = open_f_index(f, i);
			if (!error)
			{
				Cxif_key key;
				error = f.decode(key);
				if (!error)
					key.dump(ofstream(static_cast<string>(fname).c_str()), true);
				f.close();
			}
			break;
		}
	}
	return error;
}

int CXCCMixerView::copy_as_tmp_ts(int i, Cfname fname) const
{
	return 1;
	int error = 0;
	fname.set_ext(".tmp");
	Cpcx_file f;
	error = open_f_index(f, i);
	if (!error)
	{
		int cx = f.cx();
		int cy = f.cy();
		Cvirtual_binary s, d;
		pcx_decode(f.get_image(), s.write_start(cx * cy), *f.get_header());
		d.size(tmp_ts_file_write(s, d.write_start(256 << 10), cx, cy));
		error = d.size() ? d.export(fname) : 1;
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
				int cx = f.cx();
				int cy = f.cy();
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
						if (f.cx() != cx || f.cy() != cy || f.get_c_planes() != 1)
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
					Cvirtual_binary d;
					d.size(vxl_file_write(s, NULL, d.write_start(1 << 20), cx, cy, c_images));
					error = d.size() ? d.export(fname) : 1;
				}
			}
			break;
		}
	case ft_text:
		{
			Ccc_file_small g;
			error = open_f_index(g, i);
			if (!error)
			{
				Cvirtual_tfile f;
				f.load_data(g.get_vdata());
				Cvirtual_binary d;
				error = vxl_file_write(f, d);
				if (!error)
					error = d.export(fname);
				g.close();
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
					Cvirtual_binary d;
					d.size(vxl_file_write(k, d.write_start(1 << 20)));
					error = d.size() ? d.export(fname) : 1;
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

void CXCCMixerView::OnPopupCopyAsJpeg() 
{
	copy_as(ft_jpeg);
}

void CXCCMixerView::OnUpdatePopupCopyAsJpeg(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(can_copy_as(ft_jpeg));
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

void CXCCMixerView::OnPopupCopyAsPcxSingle() 
{
	copy_as(ft_pcx_single);
}

void CXCCMixerView::OnUpdatePopupCopyAsPcxSingle(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(can_copy_as(ft_pcx_single));
}

void CXCCMixerView::OnPopupCopyAsPngSingle() 
{
	copy_as(ft_png_single);
}

void CXCCMixerView::OnUpdatePopupCopyAsPngSingle(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(can_copy_as(ft_png_single));
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

void CXCCMixerView::OnPopupCopyAsSHP_TS()
{
	copy_as(ft_shp_ts);
}

void CXCCMixerView::OnUpdatePopupCopyAsSHP_TS(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_copy_as(ft_shp_ts));
}


void CXCCMixerView::OnPopupCopyAsTga() 
{
	copy_as(ft_tga);
}

void CXCCMixerView::OnUpdatePopupCopyAsTga(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(can_copy_as(ft_tga));	
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

int big_insert_dir(Cbig_edit& f, const string& dir, const string& name_prefix)
{
	int error = 0;
	WIN32_FIND_DATA fd;
	HANDLE fh = FindFirstFile((dir + '*').c_str(), &fd);
	if (fh !=  INVALID_HANDLE_VALUE)
	{
		do
		{
			string fname = dir + fd.cFileName;
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (*fd.cFileName != '.')
					error = error ? big_insert_dir(f, fname + '/', name_prefix + fd.cFileName + '\\'), error : big_insert_dir(f, fname + '/', name_prefix + fd.cFileName + '\\');
			}
			else
			{
				Cvirtual_binary d;
				if (!d.import(fname))
					error = error ? f.insert(name_prefix + fd.cFileName, d) : f.insert(name_prefix + fd.cFileName, d), error;
			}
		}
		while (FindNextFile(fh, &fd));
		FindClose(fh);
	}
	return error;
}

void CXCCMixerView::OnDropFiles(HDROP hDropInfo) 
{
	CWaitCursor wait;
	int error = 0;
	int c_files = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	char fname[MAX_PATH];
	if (m_mix_f)
	{
		t_file_type ft = m_mix_f->get_file_type();
		close_location(false);
		switch (ft)
		{
		case ft_big:
			{
				Cbig_edit f;
				error = f.open(m_mix_fname);
				if (!error)
				{
					for (int i = 0; i < c_files; i++)
					{
						DragQueryFile(hDropInfo, i, fname, MAX_PATH);
						DWORD file_attributes = GetFileAttributes(fname);
						if (file_attributes == INVALID_FILE_ATTRIBUTES || ~file_attributes & FILE_ATTRIBUTE_DIRECTORY)
						{
							Cvirtual_binary d;
							if (!d.import(fname))
								error = error ? f.insert(Cfname(fname).get_fname(), d) : f.insert(Cfname(fname).get_fname(), d), error;
						}
						else
							error = error ? big_insert_dir(f, string(fname) + '/', Cfname(fname).get_fname() + '\\'), error : big_insert_dir(f, string(fname) + '/', Cfname(fname).get_fname() + '\\');
					}
					error = error ? f.write_index(), error : f.write_index();
					f.close();
				}
				break;
			}
		case ft_mix_rg:
			{
				Cmix_rg_edit f;
				error = f.open(m_mix_fname);
				if (!error)
				{
					for (int i = 0; i < c_files; i++)
					{
						DragQueryFile(hDropInfo, i, fname, MAX_PATH);
						Cvirtual_binary d;
						if (!d.import(fname))
							error = error ? f.insert(Cfname(fname).get_fname(), d) : f.insert(Cfname(fname).get_fname(), d), error;
					}
					error = error ? f.write_index(), error : f.write_index();
					f.close();
				}
				break;
			}
		default:
			Cmix_edit f;
			error = f.open(m_mix_fname);
			if (!error)
			{
				for (int i = 0; i < c_files; i++)
				{
					DragQueryFile(hDropInfo, i, fname, MAX_PATH);
					Cvirtual_binary d;
					if (!d.import(fname))
						error = error ? f.insert(Cfname(fname).get_fname(), d) : f.insert(Cfname(fname).get_fname(), d), error;
				}
				error = error ? f.write_index(), error : f.write_index();
				f.close();
			}
		}		
		open_location_mix(m_mix_fname);
	}
	else
	{
		for (int i = 0; i < c_files; i++)
		{
			DragQueryFile(hDropInfo, i, fname, MAX_PATH);
			error = copy_file(fname, get_dir() + Cfname(fname).get_fname());
		}
		update_list();
	}
	set_msg(error ? "Insert failed" : "Insert done");
	DragFinish(hDropInfo);
}

void CXCCMixerView::OnPopupCompact() 
{
	CWaitCursor wait;	
	int error = 0;
	t_file_type ft = m_mix_f->get_file_type();
	close_location(false);
	switch (ft)
	{
	case ft_big:
		{
			Cbig_edit f;
			error = f.open(m_mix_fname);
			if (!error)
			{
				error = f.compact();
				f.close();
			}
			break;
		}
	case ft_mix_rg:
		{
			Cmix_rg_edit f;
			error = f.open(m_mix_fname);
			if (!error)
			{
				error = f.compact();
				f.close();
			}
			break;
		}
	default:
		Cmix_edit f;
		error = f.open(m_mix_fname);
		if (!error)
		{
			error = f.compact();
			f.close();
		}
	}
	set_msg(error ? "Compact failed" : "Compact done");
	open_location_mix(m_mix_fname);
}

void CXCCMixerView::OnUpdatePopupCompact(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_location.size() == 1);
}

void CXCCMixerView::OnPopupDelete()
{
	if (~GetAsyncKeyState(VK_SHIFT) < 0 && MessageBox("Are you sure you want to delete these files?", NULL, MB_ICONQUESTION | MB_YESNO) != IDYES)
		return;
	CWaitCursor wait;
	int error = 0;
	if (m_mix_f)
	{
		t_file_type ft = m_mix_f->get_file_type();
		close_location(false);
		switch (ft)
		{
		case ft_big:
		{
			Cbig_edit f;
			error = f.open(m_mix_fname);
			if (!error)
			{
				for (t_index_selected::const_iterator i = m_index_selected.begin(); i != m_index_selected.end(); i++)
					f.erase(m_index.find(get_id(*i))->second.name);
				error = f.write_index();
				f.close();
			}
			break;
		}
		case ft_mix_rg:
		{
			Cmix_rg_edit f;
			error = f.open(m_mix_fname);
			if (!error)
			{
				for (t_index_selected::const_iterator i = m_index_selected.begin(); i != m_index_selected.end(); i++)
					f.erase(m_index.find(get_id(*i))->second.name);
				error = f.write_index();
				f.close();
			}
			break;
		}
		default:
			Cmix_edit f;
			error = f.open(m_mix_fname);
			if (!error)
			{
				for (t_index_selected::const_iterator i = m_index_selected.begin(); i != m_index_selected.end(); i++)
					f.erase(get_id(*i));					
				error = f.write_index();
				f.close();
			}
		}
		open_location_mix(m_mix_fname);
	}
	else
	{
		for (t_index_selected::const_iterator i = m_index_selected.begin(); i != m_index_selected.end(); i++)
		{
			string name = m_dir + m_index.find(get_id(*i))->second.name;
			DeleteFile((m_dir + m_index.find(get_id(*i))->second.name).c_str());
		}
	}
	set_msg(error ? "Delete failed" : "Delete done");
	update_list();
}

void CXCCMixerView::OnUpdatePopupDelete(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(can_edit() && can_delete());
}

t_game CXCCMixerView::get_game()
{
	t_game r = GetMainFrame()->get_game();
	return r == -1 ? m_game : r;
}

void CXCCMixerView::OnPopupOpen()
{
	open_item(get_current_id());
}

void CXCCMixerView::OnUpdatePopupOpen(CCmdUI* pCmdUI)
{
	int id = get_current_id();
	if (id != -1)
	{
		switch (m_index.find(id)->second.ft)
		{
		case ft_aud:
		case ft_ogg:
		case ft_voc:
		case ft_wav:
			pCmdUI->Enable(!m_xap.busy() && GetMainFrame()->get_ds());
			return;
		case ft_big:
		case ft_dir:
		case ft_drive:
		case ft_mix:
		case ft_mix_rg:
		case ft_pak:
		case ft_shp_ts:
			pCmdUI->Enable(true);
			return;
		}
	}
	pCmdUI->Enable(false);
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
		m_index.find(get_current_id())->second.ft == ft_map_ts || m_index.find(get_current_id())->second.ft == ft_text &&
		GetApp()->is_fs_available());
}

void CXCCMixerView::OnPopupOpenWithFinalalert() 
{
	Ccc_file f(false);
	if (open_f_index(f, get_current_index()))
	{
	}
	else
	{
		const string fname = xcc_dirs::get_ra2_dir() + m_index.find(get_current_id())->second.name;
		f.extract(fname);
		f.close();
		ShellExecute(m_hWnd, "open", GetApp()->get_fa_exe().c_str(), fname.c_str(), NULL, SW_SHOW);
	}
}

void CXCCMixerView::OnUpdatePopupOpenWithFinalalert(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(get_current_id() != -1 &&
		m_index.find(get_current_id())->second.ft == ft_map_ra2 || m_index.find(get_current_id())->second.ft == ft_text &&
		GetApp()->is_fa_available());
}

void CXCCMixerView::OnPopupExplore() 
{
	ShellExecute(m_hWnd, "open", m_dir.c_str(), NULL, NULL, SW_SHOW);	
}

void CXCCMixerView::OnUpdatePopupExplore(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_mix_f);
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
	int error = 0;
	int id = get_current_id();
	Cfname fname = get_dir() + m_index.find(id)->second.name;
	switch (m_index.find(id)->second.ft)
	{
	case ft_jpeg:
	case ft_pcx:
	case ft_png:
		{
			Ccc_file f(true);
			error = open_f_index(f, get_current_index());
			if (!error)
			{
				Cvirtual_image s, s_palet, d;
				error = s.load(f.get_vdata());
				f.close();
				if (!error)
				{
					CResizeDlg dlg;
					dlg.set_size(s.cx(), s.cy());
					if (IDOK == dlg.DoModal())
					{
						Cvirtual_image s_palet = s;
						int cb_pixel = s.cb_pixel();
						switch (cb_pixel)
						{
						case 1:
						case 3:
							s.increase_color_depth(4);
							break;
						default:
							error = 1;
						}
						if (!error)
						{
							d.load(NULL, dlg.get_cx(), dlg.get_cy(), 4, s.palet());
							if (s.cx() < d.cx())
								resize_image_up(reinterpret_cast<const t_palet32entry*>(s.image()), reinterpret_cast<t_palet32entry*>(d.image_edit()), s.cx(), s.cy(), d.cx(), d.cy());
							else
								resize_image_down(reinterpret_cast<const t_palet32entry*>(s.image()), reinterpret_cast<t_palet32entry*>(d.image_edit()), s.cx(), s.cy(), d.cx(), d.cy());
							d.decrease_color_depth(cb_pixel, s_palet.palet());
							error = d.save(fname, m_index.find(id)->second.ft);
						}
					}
				}								
			}
		}
		break;
	case ft_shp_ts:
		{
			Cshp_ts_file f;
			error = open_f_index(f, get_current_index());
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
					Cvirtual_binary rp;
					if (global_cx_d * global_cy_d * c_images > 1 << 18)
						create_downsample_table(palet, rp.write_start(1 << 18));
					byte* d8 = new byte[global_cx_d * global_cy_d * c_images];
					t_palet32entry* d32 = new t_palet32entry[global_cx_d * global_cy_d];
					byte* image8 = new byte[global_cx * global_cy];
					t_palet32entry* image32 = new t_palet32entry[global_cx * global_cy];
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
						upsample_image(image8, image32, global_cx, global_cy, palet);
						if (global_cx < global_cx_d)
							resize_image_up(image32, d32, global_cx, global_cy, global_cx_d, global_cy_d);
						else
							resize_image_down(image32, d32, global_cx, global_cy, global_cx_d, global_cy_d);
						if (rp.size())
							downsample_image(d32, d8 + global_cx_d * global_cy_d * i, global_cx_d, global_cy_d, rp.data());
						else
							downsample_image(d32, d8 + global_cx_d * global_cy_d * i, global_cx_d, global_cy_d, palet);
					}
					f.close();
					error = shp_ts_file_write(d8, global_cx_d, global_cy_d, c_images).export(fname);
					delete[] image32;
					delete[] image8;
					delete[] d32;
					delete[] d8;
				}
			}
		}
		break;
	}
	set_msg("Resize " + fname.get_ftitle() + (error ? " failed, error " + n(error) : " succeeded"));
	update_list();
}

void CXCCMixerView::OnUpdatePopupResize(CCmdUI* pCmdUI)
{
	int id = get_current_id();
	if (can_accept() && id != -1)
	{
		switch (m_index.find(get_current_id())->second.ft)
		{
		case ft_jpeg:
		case ft_pcx:
		case ft_png:
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

void CXCCMixerView::OnPopupClipboardCopy() 
{
	int error = 0;
	int id = get_current_id();
	switch (m_index.find(id)->second.ft)
	{
	case ft_dds:
		{
			Cdds_file f;
			error = open_f_id(f, id);
			if (!error)
			{
				Cvirtual_image image = f.vimage();
				image.remove_alpha();
				error = image.set_clipboard();
				f.close();
			}
			break;
		}
	case ft_jpeg:
		{
			Cjpeg_file f;
			error = open_f_id(f, id);
			if (!error)
			{
				Cvirtual_image image;
				f.decode(image);
				error = image.set_clipboard();
				f.close();
			}
			break;
		}
	case ft_pcx:
		{
			Cpcx_file f;
			error = open_f_id(f, id);
			if (!error)
			{
				Cvirtual_image image;
				f.decode(image);
				error = image.set_clipboard();
				f.close();
			}
			break;
		}
	case ft_shp_ts:
		{
			Cshp_ts_file f;
			error = open_f_id(f, id);
			if (!error)
			{
				Cvirtual_image image;
				error = f.extract_as_pcx_single(image, get_default_palet(), GetMainFrame()->combine_shadows());
				if (!error)
					error = image.set_clipboard();
				f.close();
			}
			break;
		}
	}
}

void CXCCMixerView::OnUpdatePopupClipboardCopy(CCmdUI* pCmdUI) 
{
	int id = get_current_id();
	pCmdUI->Enable(id != -1 && can_convert(m_index.find(id)->second.ft, ft_clipboard));
}

int CXCCMixerView::get_paste_fname(string& fname, t_file_type ft, const char* filter)
{
	int id = get_current_id();
	bool replace = id != -1 && m_index.find(id)->second.ft == ft;
	CFileDialog dlg(false, NULL, replace ? (m_dir + m_index.find(id)->second.name).c_str() : NULL, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, filter, this);
	if (!replace)
		dlg.m_ofn.lpstrInitialDir = m_dir.c_str();
	if (IDOK == dlg.DoModal())
	{
		fname = dlg.GetPathName();
		return 0;
	}
	return 1;
}

void CXCCMixerView::OnPopupClipboardPasteAsJpeg() 
{
	Cvirtual_image image;
	int error = image.get_clipboard();
	if (!error)
	{
		string fname;
		if (!get_paste_fname(fname, ft_jpeg, "JPEG files (*.jpeg;*.jpg)|*.jpeg;*.jpg|"))
		{
			image.save_as_jpeg(fname);
			update_list();
		}
	}
}

void CXCCMixerView::OnPopupClipboardPasteAsPcx() 
{
	Cvirtual_image image;
	int error = image.get_clipboard();
	if (!error)
	{
		string fname;
		if (!get_paste_fname(fname, ft_pcx, "PCX files (*.pcx)|*.pcx|"))
		{
			image.save_as_pcx(fname);
			update_list();
		}
	}
}

void CXCCMixerView::OnPopupClipboardPasteAsPng() 
{
	Cvirtual_image image;
	int error = image.get_clipboard();
	if (!error)
	{
		string fname;
		if (!get_paste_fname(fname, ft_png, "PNG files (*.png)|*.png|"))
		{
			image.save_as_png(fname);
			update_list();
		}
	}
}

void CXCCMixerView::OnUpdatePopupClipboardPasteAsImage(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(can_accept() && IsClipboardFormatAvailable(CF_DIB));
}

void CXCCMixerView::OnPopupClipboardPasteAsShpTs() 
{
	Cvirtual_image image;
	int error = image.get_clipboard();
	if (!error)
	{
		if (image.cb_pixel() == 3 || GetMainFrame()->use_palet_for_conversion())
		{
			t_palet p;
			memcpy(p, get_default_palet(), sizeof(t_palet));
			convert_palet_18_to_24(p);
			if (image.cb_pixel() == 3)
				image.decrease_color_depth(1, p);
			else
			{
				byte rp[256];
				if (GetMainFrame()->convert_from_td())
					create_rp(image.palet(), p, rp, game_td);
				else if (GetMainFrame()->convert_from_ra())
					create_rp(image.palet(), p, rp, game_ra);
				else
					create_rp(image.palet(), p, rp);
				apply_rp(image.image_edit(), image.cx() * image.cy(), rp);
			}
		}
		string fname;
		if (!get_paste_fname(fname, ft_shp_ts, "SHP files (*.shp)|*.shp|"))
		{
			Cshp_properties_dlg dlg;
			Cshp_ts_file f;
			int split_shadows = GetMainFrame()->split_shadows();
			int id = get_current_id();
			if (id != -1 && !open_f_id(f, id))
			{
				if (f.is_valid())
				{
					int c_images = f.get_c_images();
					if (c_images < 2)
						split_shadows = false;
					dlg.set_size(f.get_cx(), f.get_cy(), c_images >> split_shadows);
				}
				else
					dlg.set_size(image.cx(), image.cy(), 1);
				f.close();
			}
			else
				dlg.set_size(image.cx(), image.cy(), 1);
			if (IDOK == dlg.DoModal())
			{
				int cblocks_x = image.cx() / dlg.get_cx();
				int cblocks_y = image.cy() / dlg.get_cy();
				int c_blocks = dlg.get_c_frames();
				shp_split_frames(image, cblocks_x, cblocks_y);
				if (split_shadows)
				{
					shp_split_shadows(image);
					c_blocks <<= 1;
				}
				shp_ts_file_write(image.image(), dlg.get_cx(), dlg.get_cy(), c_blocks, GetMainFrame()->enable_compression()).export(fname);
				update_list();
			}
		}
	}
}

void CXCCMixerView::OnUpdatePopupClipboardPasteAsVideo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(can_accept() && IsClipboardFormatAvailable(CF_DIB));
}

BOOL CXCCMixerView::OnIdle(LONG lCount)
{
	if (m_reading)
	{
		for (t_index::iterator i = m_index.begin(); i != m_index.end(); i++)
		{
			t_index_entry& e = i->second;
			if (i->second.ft == -1)
			{
				Ccc_file f(false);
				if (f.open(m_dir + e.name))
				{
					e.ft = ft_unknown;
					e.size = -1;
				}
				else
				{
					e.ft = f.get_file_type();
					e.size = f.get_size();
					f.close();
				}
				CListCtrl& lc = GetListCtrl();
				LVFINDINFO lvf;
				lvf.flags = LVFI_PARAM;
				lvf.lParam = i->first;
				lc.Update(lc.FindItem(&lvf, -1));
				m_sort_column = -1;
				return true;
			}
		}
		sort_list(0, false);
		sort_list(1, false);
		autosize_colums();
		m_reading = false;
	}
	return false;
}

string CXCCMixerView::report() const
{
	string page;
	ULARGE_INTEGER available, total, free;
	if (GetDiskFreeSpaceEx(m_dir.c_str(), &available, &total, &free))
		page += tr(td(m_dir) + td(n(*reinterpret_cast<__int64*>(&available))) + td(n(*reinterpret_cast<__int64*>(&total))));
	page += tr(th("Name") + th("Type") + th("Size"));
	CListCtrl& lc = GetListCtrl();
	for (int i = 0; i < lc.GetItemCount(); i++)
	{
		const t_index_entry& e = m_index.find(lc.GetItemData(i))->second;
		page += tr(td(e.name) + td(ft_name[e.ft]) + td(e.size == -1 ? "&nbsp;" : n(e.size), "align=right"));
	}
	return table(page, "border=1 width=100%");
}

void CXCCMixerView::open_item(int id)
{
	const t_index_entry& index = m_index.find(id)->second;
	switch (index.ft)
	{
	case ft_aud:
	case ft_ogg:
	case ft_voc:
	case ft_wav:
		if (!m_xap.busy() && GetMainFrame()->get_ds())
		{
			CWaitCursor wait;
			Ccc_file f(true);
			if (!open_f_id(f, id))
			{
				m_xap.ds(GetMainFrame()->get_ds());
				m_xap.load(f.get_vdata());
				f.close();
				m_xap.play();
			}
		}
		break;
	case ft_dir:
		{
			string name = index.name;
			close_location(false);
			if (name == "..")
			{
				int i = m_dir.rfind('\\');
				if (i != string::npos)
				{
					i = m_dir.rfind('\\', i - 1);
					if (i != string::npos)
						open_location_dir(m_dir.substr(0, i + 1));
				}
			}
			else
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
	case ft_big:
	case ft_mix:
	case ft_mix_rg:
	case ft_pak:
		{
			if (m_mix_f)
				open_location_mix(id);
			else
				open_location_mix(m_dir + index.name);
			break;
		}
	case ft_shp_ts:
		{
			Cshp_ts_file f;
			if (!open_f_id(f, id))
			{
				Cdlg_shp_viewer dlg;
				dlg.write(f.get_vdata(), get_default_palet());
				f.close();
				dlg.DoModal();
			}
			break;
		}
	}
}

void CXCCMixerView::OnEditSelectAll() 
{
	CListCtrl& lc = GetListCtrl();
	for (int index = 0; index < lc.GetItemCount(); index++)
	{
		if (m_index.find(lc.GetItemData(index))->second.ft != ft_dir
			&& m_index.find(lc.GetItemData(index))->second.ft != ft_drive)
			lc.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);
	}
}
