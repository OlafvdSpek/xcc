// XSE_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MainFrm.h"
#include "xcc mixer.h"
#include "XSE_dlg.h"

#include <assert.h>
#include "audio_idx_file.h"
#include "ima_adpcm_wav_decode.h"
#include "mix_file.h"
#include "string_conversion.h"
#include "wav_file.h"
#include "wav_structures.h"
#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXSE_dlg dialog


static CMainFrame* GetMainFrame()
{
	return static_cast<CMainFrame*>(AfxGetMainWnd());
}

CXSE_dlg::CXSE_dlg(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(CXSE_dlg::IDD, pParent, "XSE_dlg")
{
	//{{AFX_DATA_INIT(CXSE_dlg)
	m_extract_to_edit = _T("");
	//}}AFX_DATA_INIT
	m_buffer_w = 0;
	m_ds = GetMainFrame()->get_ds();
	m_xap.ds(m_ds);
}


void CXSE_dlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXSE_dlg)
	DDX_Control(pDX, IDC_COMPACT, m_compact);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_PLAY, m_play);
	DDX_Control(pDX, IDC_EXTRACT, m_extract);
	DDX_Control(pDX, IDC_DELETE, m_delete);
	DDX_Text(pDX, IDC_EXTRACT_TO_EDIT, m_extract_to_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXSE_dlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(CXSE_dlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_BN_CLICKED(IDC_EXTRACT, OnExtract)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_COMPACT, OnCompact)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST, OnGetdispinfoList)
	ON_BN_CLICKED(IDC_EXTRACT_TO_BUTTON, OnExtractToButton)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST, OnColumnclickList)
	ON_WM_DESTROY()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXSE_dlg message handlers

static int c_colums = 9;
static char* column_label[] = {"Name", "Value", "Extra value", "Length", "Offset", "Size", "Samplerate", "Flags", "Chunk size"};
static int column_alignment[] = {LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT};

BOOL CXSE_dlg::OnInitDialog()
{
	ETSLayoutDialog::OnInitDialog();
	CreateRoot(VERTICAL)
		<< item(IDC_LIST, GREEDY)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< item(IDC_EXTRACT_TO_STATIC, NORESIZE)
			<< item(IDC_EXTRACT_TO_EDIT, GREEDY)
			<< item(IDC_EXTRACT_TO_BUTTON, NORESIZE)
			)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< itemGrowing(HORIZONTAL)
			<< item(IDC_PLAY, NORESIZE)
			<< item(IDC_EXTRACT, NORESIZE)
			<< item(IDC_DELETE, NORESIZE)
			<< item(IDC_COMPACT, NORESIZE)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			);
	UpdateLayout();
	SetRedraw(false);
	ListView_SetExtendedListViewStyle(m_list.m_hWnd, ListView_GetExtendedListViewStyle(m_list.m_hWnd) | LVS_EX_FULLROWSELECT);
	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM;
	for (int i = 0; i < c_colums; i++)
	{
		lvc.iSubItem = i;
		lvc.pszText = column_label[i];
		lvc.fmt = column_alignment[i];
		m_list.InsertColumn(i, &lvc);
	}

	int error = m_csf_f.open(xcc_dirs::get_ra2_dir() + "ra2.csf");
	if (error)
	{
		Cmix_file language;
		error = language.open(xcc_dirs::get_ra2_dir() + "language.mix");
		if (!error)
		{
			error = m_csf_f.open("ra2.csf", language);
			language.close();
		}
	}
	if (!error)
	{
		for (Ccsf_file::t_map::const_iterator j = m_csf_f.get_map().begin(); j != m_csf_f.get_map().end(); j++)
		{
			if (j->second.extra_value.empty())
				continue;
			m_reverse_csf_map[j->second.extra_value] = j;
		}
	}
	if (m_bag_f.open_edit(xcc_dirs::get_ra2_dir() + "audio.bag")
		|| m_idx_f.open_edit(xcc_dirs::get_ra2_dir() + "audio.idx"))
		throw;
	if (m_bag_f.get_size() && m_idx_f.get_size())
	{
		int cb_s = m_idx_f.get_size();
		byte* s = new byte[cb_s];
		error = m_idx_f.read(s, cb_s);
		if (!error)
		{
			Caudio_idx_file g;
			g.load(s, cb_s);
			read_idx_file(g);
		}
		delete[] s;
	}
	else
	{
		CWaitCursor wait;
		Cmix_file language;
		error = language.open(xcc_dirs::get_ra2_dir() + "language.mix");
		if (!error)
		{
			Cmix_file audio;
			error = audio.open("audio.mix", language);
			if (!error)
			{
				Ccc_file f(true);
				error = f.open("audio.bag", audio);
				if (!error)
				{
					error = m_bag_f.write(f.get_data(), f.get_size());
					f.close();
					if (!error)
					{
						Caudio_idx_file g;
						error = g.open("audio.idx", audio);
						if (!error)
						{
							read_idx_file(g);
							g.close();
							if (!error)
								write_idx_file();
						}
					}
				}
				audio.close();
			}
			language.close();
		}
	}
	if (!error)
	{
		for (int j = 0; j < c_colums; j++)
			m_list.SetColumnWidth(j, LVSCW_AUTOSIZE);
	}
	set_extract_to_dir(static_cast<string>(AfxGetApp()->GetProfileString("XSE_dlg", "extract_to_dir", xcc_dirs::get_ra2_dir().c_str())));
	check_selection();
	SetRedraw(true);
	Invalidate();
	return false;
}

void CXSE_dlg::OnDestroy() 
{
	ETSLayoutDialog::OnDestroy();	
	m_idx_f.close();
	m_csf_f.close();
	m_bag_f.close();
}

void CXSE_dlg::OnOK()
{
	write_idx_file();
	ETSLayoutDialog::OnOK();
}

void CXSE_dlg::read_idx_file(const Caudio_idx_file& f)
{
	for (int i = 0; i < f.c_sounds(); i++)
	{
		const t_audio_idx_entry& s  = f.sound_entry(i);
		t_map_entry& e = m_map[i];
		e.offset = s.offset;
		e.size = s.size;
		e.samplerate = s.samplerate;
		e.flags = s.flags;
		e.chunk_size = s.chunk_size;
		e.extra_value = s.fname;
		insert(i);
	}
}

int CXSE_dlg::insert(int id)
{
	t_map_entry& e = m_map[id];
	t_reverse_csf_map::const_iterator i = m_reverse_csf_map.find(e.extra_value + 'e');
	if (i == m_reverse_csf_map.end())
	{
		e.name.erase();
		e.value.erase();
	}
	else
	{
		e.name = i->second->first;
		e.value = m_csf_f.get_converted_value(i->second->first);
	}
	int index = m_list.InsertItem(m_list.GetItemCount(), LPSTR_TEXTCALLBACK);
	m_list.SetItemData(index, id);
	return index;
}

int CXSE_dlg::get_current_index()
{
	return m_list.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
}

void CXSE_dlg::check_selection()
{
	int index = get_current_index();
	m_play.EnableWindow(index != -1 && m_ds);
	m_extract.EnableWindow(index != -1);
	m_delete.EnableWindow(index != -1);
	m_compact.EnableWindow(get_bag_size() != m_bag_f.get_size());
}

void CXSE_dlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->uNewState & LVIS_FOCUSED)
		check_selection();
	*pResult = 0;
}

void CXSE_dlg::OnPlay() 
{
	int index = m_list.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
	if (index == -1)
		return;

	int id = m_list.GetItemData(index);
	const t_map_entry& e = m_map.find(id)->second;
	int c_channels = e.flags & 1 ? 2 : 1;
	if (e.flags & 2)
	{
		assert(!e.chunk_size);
		int cb_d = sizeof(t_wav_header) + e.size;
		byte* d = new byte[cb_d];
		byte* w = d;
		int c_channels = e.flags & 1 ? 2 : 1;
		int c_samples = e.size / c_channels >> 1;
		w += wav_file_write_header(w, c_samples, e.samplerate, 2, c_channels);
		m_bag_f.seek(e.offset);
		if (!m_bag_f.read(w, e.size) && !m_xap.load(d, cb_d))
			m_xap.play();
		delete[] d;
	}
	else 
	{
		assert(e.flags & 8);
		int cb_s = e.size;
		byte* s = new byte[cb_s];
		m_bag_f.seek(e.offset);
		if (!m_bag_f.read(s, e.size))
		{
			Cima_adpcm_wav_decode decode;
			decode.load(s, cb_s, c_channels, e.chunk_size);
			int c_samples = decode.c_samples() / c_channels;
			int cb_d = sizeof(t_wav_header) + (c_channels * c_samples << 1);
			byte* d = new byte[cb_d];
			byte* w = d;
			w += wav_file_write_header(w, c_samples, e.samplerate, 2, c_channels);
			memcpy(w, decode.data(), c_channels * c_samples << 1);
			if (!m_xap.load(d, cb_d))
				m_xap.play();			
			delete[] d;
		}
		delete[] s;
	}
}

void CXSE_dlg::OnExtract()
{
	if (UpdateData(true))
	{
		CWaitCursor wait;
		set_extract_to_dir(static_cast<string>(m_extract_to_edit));
		string path = m_extract_to_edit;
		AfxGetApp()->WriteProfileString("XSE_dlg", "extract_to_dir", m_extract_to_edit);
		int index = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		while (index != -1)
		{
			int error = 0;
			int id = m_list.GetItemData(index);
			const t_map_entry& e = m_map.find(id)->second;
			int c_channels = e.flags & 1 ? 2 : 1;
			if (e.flags & 2)
			{
				assert(!e.chunk_size);
				int cb_d = sizeof(t_wav_header) + e.size;
				byte* d = new byte[cb_d];
				byte* w = d;
				int c_channels = e.flags & 1 ? 2 : 1;
				int c_samples = e.size / c_channels >> 1;
				w += wav_file_write_header(w, c_samples, e.samplerate, 2, c_channels);
				m_bag_f.seek(e.offset);
				if (!m_bag_f.read(w, e.size))
					error = file32_write(path + e.extra_value + ".wav", d, cb_d);
				delete[] d;
			}
			else 
			{
				assert(e.flags & 8);
				int cb_s = e.size;
				byte* s = new byte[cb_s];
				m_bag_f.seek(e.offset);
				if (!m_bag_f.read(s, e.size))
				{
					Cima_adpcm_wav_decode decode;
					decode.load(s, cb_s, c_channels, e.chunk_size);
					int c_samples = decode.c_samples() / c_channels;
					int cb_d = sizeof(t_wav_header) + (c_channels * c_samples << 1);
					byte* d = new byte[cb_d];
					byte* w = d;
					w += wav_file_write_header(w, c_samples, e.samplerate, 2, c_channels);
					memcpy(w, decode.data(), c_channels * c_samples << 1);
					error = file32_write(path + e.extra_value + ".wav", d, cb_d);
					delete[] d;
				}
				delete[] s;
			}
			if (error)
				MessageBox("Error writing file.", NULL, MB_ICONERROR);
			index = m_list.GetNextItem(index, LVNI_ALL | LVNI_SELECTED);
		}
	}
}

void CXSE_dlg::OnDelete()
{
	while (1)
	{
		int index = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if (index == -1)
			break;
		int id = m_list.GetItemData(index);
		m_map.erase(id);
		m_list.DeleteItem(index);
	}
	check_selection();
}

void CXSE_dlg::write_idx_file()
{
	int cb_d = audio_idx_file_get_write_size(m_map.size());
	byte* d = new byte[cb_d];
	byte* w = d;
	w += audio_idx_file_write_header(w, m_map.size());
	for (t_map::const_iterator i = m_map.begin(); i != m_map.end(); i++)
	{
		const t_map_entry& e = i->second;
		w += audio_idx_file_write_entry(w, e.extra_value, e.offset, e.size, e.samplerate, e.flags, e.chunk_size);
	}
	assert(w - d == cb_d);
	m_idx_f.seek(0);
	m_idx_f.write(d, cb_d);
	m_idx_f.set_eof();
	delete[] d;
}

int CXSE_dlg::get_bag_size() const
{
	int r = 0;
	for (t_map::const_iterator i = m_map.begin(); i != m_map.end(); i++)
		r += i->second.size;
	return r;
}

void CXSE_dlg::OnCompact()
{
	int error = 0;
	int cb_d = get_bag_size();
	byte* d = new byte[cb_d];
	byte* w = d;
	for (t_map::iterator i = m_map.begin(); i != m_map.end(); i++)
	{
		t_map_entry& e = i->second;
		m_bag_f.seek(e.offset);
		if (error = m_bag_f.read(w, e.size))
			break;
		e.offset = w - d;
		w += e.size;
	}
	if (!error)
	{
		m_bag_f.seek(0);
		error = m_bag_f.write(d, cb_d);
		if (!error)
			error = m_bag_f.set_eof();
	}
	delete[] d;
	write_idx_file();
	check_selection();
}

int CXSE_dlg::get_free_id()
{
	int id = 0;
	while (m_map.find(id) != m_map.end())
		id++;
	return id;
}

void CXSE_dlg::add_file(const string& name)
{
	Cwav_file f;
	if (!f.open(name))
	{
		if (f.is_valid() && !f.process())
		{
			const t_riff_wave_format_chunk& format_chunk = f.get_format_chunk();
			if ((format_chunk.tag == 1 || format_chunk.tag == 0x11)
				&& (format_chunk.c_channels == 1 || format_chunk.c_channels == 2)
				&& format_chunk.cbits_sample == (format_chunk.tag == 1 ? 16 : 4))
			{
				int cb_s = f.get_data_header().size;
				byte* s = new byte[cb_s];
				f.seek(f.get_data_ofs());
				if (!f.read(s, cb_s))
				{
					t_map_entry e;
					e.offset = m_bag_f.get_size();
					e.size = cb_s;
					e.samplerate = format_chunk.samplerate;
					e.flags = 4 | format_chunk.c_channels == 2;
					if (format_chunk.tag == 1)
					{
						e.flags |= 2;
						e.chunk_size = 0;
					}
					else
					{
						e.flags |= 8;
						e.chunk_size = 512 * format_chunk.c_channels;
					}
					e.extra_value = static_cast<Cfname>(name).get_ftitle();
					m_bag_f.seek(e.offset);
					if (!m_bag_f.write(s, cb_s))
					{
						int i;
						for (t_map::const_iterator j = m_map.begin(); j != m_map.end(); j++)
						{
							if (e.extra_value == j->second.extra_value)
							{
								i = j->first;
								break;
							}
						}
						if (j != m_map.end())
						{
							LVFINDINFO lvf;
							lvf.flags = LVFI_PARAM;
							lvf.lParam = j->first;
							m_list.DeleteItem(m_list.FindItem(&lvf, -1));
						}
						else
							i = get_free_id();
						m_map[i] = e;
						m_list.EnsureVisible(insert(i), false);
					}
				}
				delete[] s;
			}
		}
		f.close();
	}
}

void CXSE_dlg::OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	int id = m_list.GetItemData(pDispInfo->item.iItem);
	const t_map_entry& e = m_map.find(id)->second;
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		{
			t_reverse_csf_map::const_iterator i = m_reverse_csf_map.find(e.extra_value + 'e');
			if (i == m_reverse_csf_map.end())
				m_buffer[m_buffer_w].erase();
			else
				m_buffer[m_buffer_w] = i->second->first;
			break;
		}
	case 1:
		{
			t_reverse_csf_map::const_iterator i = m_reverse_csf_map.find(e.extra_value + 'e');
			if (i == m_reverse_csf_map.end())
				m_buffer[m_buffer_w].erase();
			else
				m_buffer[m_buffer_w] = m_csf_f.get_converted_value(i->second->first);
			break;
		}
	case 2:
		m_buffer[m_buffer_w] = e.extra_value;
		break;
	case 3:
		m_buffer[m_buffer_w].erase();
		break;
	case 4:
		m_buffer[m_buffer_w] = n(e.offset);
		break;
	case 5:
		m_buffer[m_buffer_w] = n(e.size);
		break;
	case 6:
		m_buffer[m_buffer_w] = n(e.samplerate);
		break;
	case 7:
		m_buffer[m_buffer_w] = n(e.flags);
		break;
	case 8:
		m_buffer[m_buffer_w] = n(e.chunk_size);
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

void CXSE_dlg::OnExtractToButton() 
{
    BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = GetSafeHwnd();
	bi.ulFlags = BIF_EDITBOX | BIF_RETURNONLYFSDIRS ; 
	ITEMIDLIST* idl = SHBrowseForFolder(&bi);
	if (idl)
	{
		char b[MAX_PATH];
		SHGetPathFromIDList(idl, b);
		set_extract_to_dir(b);
		LPMALLOC lpm;
		if (SHGetMalloc(&lpm) == NOERROR)
			lpm->Free(idl);
	}
}

void CXSE_dlg::set_extract_to_dir(const string& v)
{
	Cfname fname = v;
	fname.make_path();
	m_extract_to_edit = fname.get_path().c_str();
	UpdateData(false);
}

void CXSE_dlg::OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int column = reinterpret_cast<NM_LISTVIEW*>(pNMHDR)->iSubItem;
	sort_list(column, column == m_sort_column ? !m_sort_reverse : false);
	*pResult = 0;
}

static int compare_int(unsigned int a, unsigned int b)
{
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}

static int compare_string(string a, string b)
{
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}

int CXSE_dlg::compare(int id_a, int id_b) const
{
	if (m_sort_reverse)
		swap(id_a, id_b);
	const t_map_entry& a = m_map.find(id_a)->second;
	const t_map_entry& b = m_map.find(id_b)->second;
	switch (m_sort_column)
	{
	case 0:
		return compare_string(a.name, b.name);
	case 1:
		return compare_string(a.extra_value, b.extra_value);
	case 2:
		return compare_string(a.value, b.value);
	case 4:
		return compare_int(a.offset, b.offset);
	case 5:
		return compare_int(a.size, b.size);
	case 6:
		return compare_int(a.samplerate, b.samplerate);
	case 7:
		return compare_int(a.flags, b.flags);
	case 8:
		return compare_int(a.chunk_size, b.chunk_size);
	default:
		return 0;
	}
}

static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return reinterpret_cast<CXSE_dlg*>(lParamSort)->compare(lParam1, lParam2);
}

void CXSE_dlg::sort_list(int i, bool reverse)
{
	m_sort_column = i;
	m_sort_reverse = reverse;
	m_list.SortItems(Compare, reinterpret_cast<dword>(this));
}
