#include "stdafx.h"
#include "MainFrm.h"
#include "XSE_dlg.h"

#include "audio_idx_file.h"
#include "ima_adpcm_wav_decode.h"
#include "mix_file.h"
#include "string_conversion.h"
#include "wav_file.h"
#include "wav_structures.h"
#include "xcc_dirs.h"

static CMainFrame* GetMainFrame()
{
	return static_cast<CMainFrame*>(AfxGetMainWnd());
}

CXSE_dlg::CXSE_dlg(t_game game, CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(CXSE_dlg::IDD, pParent, "XSE_dlg")
{
	//{{AFX_DATA_INIT(CXSE_dlg)
	m_extract_to_edit = _T("");
	//}}AFX_DATA_INIT
	m_ds = GetMainFrame()->get_ds();
	m_game = game;
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
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_WM_DROPFILES()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static int c_colums = 10;
static const char* column_label[] = {"Name", "Value", "Extra value", "Length", "Offset", "Size", "Samplerate", "Flags", "Chunk size", ""};
static int column_alignment[] = {LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_LEFT};

BOOL CXSE_dlg::OnInitDialog()
{
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
	ETSLayoutDialog::OnInitDialog();
	SetRedraw(false);
	for (int i = 0; i < c_colums; i++)
		m_list.InsertColumn(i, column_label[i], column_alignment[i]);

	string audio_mix_fname = xcc_dirs::get_audio_mix(m_game);
	string csf_fname = xcc_dirs::get_csf_fname(m_game);
	string language_fname = xcc_dirs::get_language_mix(m_game);
	int error = m_csf_f.open(xcc_dirs::get_dir(m_game) + csf_fname);
	if (error)
	{
		Cmix_file language;
		error = language.open(language_fname);
		if (!error)
			error = m_csf_f.open(csf_fname, language);
	}
	if (!error)
	{
		for (auto& j : m_csf_f.get_map())
		{
			if (j.second.extra_value.empty())
				continue;
			m_reverse_csf_map[j.second.extra_value] = &j;
		}
	}
	if (m_bag_fname.empty())
		m_bag_fname = xcc_dirs::get_dir(m_game) + "audio.bag";
	if (m_idx_fname.empty())
		m_idx_fname = xcc_dirs::get_dir(m_game) + "audio.idx";
	if (m_bag_f.open_edit(m_bag_fname) || m_idx_f.open_edit(m_idx_fname))
		throw;
	if (m_bag_f.size() && m_idx_f.size())
	{
		Cvirtual_binary s;
		int cb_s = m_idx_f.size();
		error = m_idx_f.read(s.write_start(cb_s), cb_s);
		if (!error)
		{
			Caudio_idx_file g;
			g.load(s);
			read_idx_file(g);
		}
	}
	else
	{
		CWaitCursor wait;
		Cmix_file language;
		error = language.open(language_fname);
		if (!error)
		{
			Cmix_file audio;
			error = audio.open(audio_mix_fname, language);
			if (!error)
			{
				Ccc_file f(true);
				error = f.open("audio.bag", audio);
				if (!error)
				{
					error = m_bag_f.write(f);
					if (!error)
					{
						Caudio_idx_file g;
						error = g.open("audio.idx", audio);
						if (!error)
						{
							read_idx_file(g);
							write_idx_file();
						}
					}
				}
			}
		}
	}
	m_list.auto_size();
	set_extract_to_dir(static_cast<string>(AfxGetApp()->GetProfileString("XSE_dlg", "extract_to_dir", xcc_dirs::get_dir(m_game).c_str())));
	check_selection();
	SetRedraw(true);
	Invalidate();
	return false;
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
	if (auto i = find_ptr2(m_reverse_csf_map, e.extra_value + 'e'))
	{
		e.name = i->first;
		e.value = m_csf_f.get_converted_value(i->first);
	}
	else
	{
		e.name.erase();
		e.value.erase();
	}
	return m_list.InsertItemData(id);
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
	m_compact.EnableWindow(get_bag_size() != m_bag_f.size());
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
	const t_map_entry& e = find_ref(m_map, id);
	int c_channels = e.flags & 1 ? 2 : 1;
	if (e.flags & 2)
	{
		assert(!e.chunk_size);
		int cb_d = sizeof(t_wav_header) + e.size;
		Cvirtual_binary d;
		byte* w = d.write_start(cb_d);
		int c_channels = e.flags & 1 ? 2 : 1;
		int c_samples = e.size / c_channels >> 1;
		w += wav_file_write_header(w, c_samples, e.samplerate, 2, c_channels);
		m_bag_f.seek(e.offset);
		if (!m_bag_f.read(w, e.size))
			xap_play(m_ds, d);
	}
	else 
	{
		assert(e.flags & 8);
		Cvirtual_binary s;
		m_bag_f.seek(e.offset);
		if (!m_bag_f.read(s.write_start(e.size), e.size))
		{
			Cima_adpcm_wav_decode decode;
			decode.load(s.data(), s.size(), c_channels, e.chunk_size);
			int c_samples = decode.c_samples() / c_channels;
			int cb_d = sizeof(t_wav_header) + (c_channels * c_samples << 1);
			Cvirtual_binary d;
			byte* w = d.write_start(cb_d);
			w += wav_file_write_header(w, c_samples, e.samplerate, 2, c_channels);
			memcpy(w, decode.data(), c_channels * c_samples << 1);
			xap_play(m_ds, d);
		}
	}
}

void CXSE_dlg::OnExtract()
{
	if (UpdateData(true))
	{
		CWaitCursor wait;
		set_extract_to_dir(static_cast<string>(m_extract_to_edit));
		string path(m_extract_to_edit);
		AfxGetApp()->WriteProfileString("XSE_dlg", "extract_to_dir", m_extract_to_edit);
		int index = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		while (index != -1)
		{
			int error = 0;
			int id = m_list.GetItemData(index);
			const t_map_entry& e = find_ref(m_map, id);
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
	for (auto& i : m_map)
	{
		const t_map_entry& e = i.second;
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
	for (auto& i : m_map)
		r += i.second.size;
	return r;
}

void CXSE_dlg::OnCompact()
{
	int error = 0;
	int cb_d = get_bag_size();
	byte* d = new byte[cb_d];
	byte* w = d;
	for (auto& i : m_map)
	{
		t_map_entry& e = i.second;
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
	while (m_map.count(id))
		id++;
	return id;
}

void CXSE_dlg::add_file(const string& name)
{
	Cwav_file f;
	if (f.open(name) || !f.is_valid() || f.process())
		return;
	const t_riff_wave_format_chunk& format_chunk = f.get_format_chunk();
	if ((format_chunk.tag != 1 && format_chunk.tag != 0x11)
		|| (format_chunk.c_channels != 1 && format_chunk.c_channels != 2)
		|| format_chunk.cbits_sample != (format_chunk.tag == 1 ? 16 : 4))
		return;
	Cvirtual_binary s(NULL, f.get_data_header().size);
	f.seek(f.get_data_ofs());
	if (f.read(s.data_edit(), s.size()))
		return;
	t_map_entry e;
	e.offset = m_bag_f.size();
	e.size = s.size();
	e.samplerate = format_chunk.samplerate;
	e.flags = 4 | (format_chunk.c_channels == 2);
	if (format_chunk.tag == 1)
	{
		e.flags |= 2;
		e.chunk_size = 0;
	}
	else
	{
		e.flags |= 8;
		e.chunk_size = format_chunk.block_align; // 512 * format_chunk.c_channels;
	}
	e.extra_value = Cfname(name).get_ftitle().substr(0, 15);
	m_bag_f.seek(e.offset);
	if (m_bag_f.write(s))
		return;
	int i;
	t_map::const_iterator j;
	for (j = m_map.begin(); j != m_map.end(); j++)
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

void CXSE_dlg::OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	int id = pDispInfo->item.lParam;
	const t_map_entry& e = find_ref(m_map, id);
	string& buffer = m_list.get_buffer();
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		if (auto i = find_ptr2(m_reverse_csf_map, e.extra_value + 'e'))
			buffer = i->first;
		else
			buffer.erase();
		break;
	case 1:
			;
			if (auto i = find_ptr2(m_reverse_csf_map, e.extra_value + 'e'))
				buffer = m_csf_f.get_converted_value(i->first);
			else
				buffer.erase();
			break;
	case 2:
		buffer = e.extra_value;
		break;
	case 3:
		buffer.erase();
		break;
	case 4:
		buffer = n(e.offset);
		break;
	case 5:
		buffer = n(e.size);
		break;
	case 6:
		buffer = n(e.samplerate);
		break;
	case 7:
		buffer = n(e.flags);
		break;
	case 8:
		buffer = n(e.chunk_size);
		break;
	default:
		buffer.erase();
	}
	pDispInfo->item.pszText = const_cast<char*>(buffer.c_str());
	*pResult = 0;
}

void CXSE_dlg::OnExtractToButton() 
{
    BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = GetSafeHwnd();
	bi.ulFlags = BIF_EDITBOX | BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
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
	return a < b ? -1 : a != b;
}

static int compare_string(string a, string b)
{
	return a < b ? -1 : a != b;
}

int CXSE_dlg::compare(int id_a, int id_b) const
{
	if (m_sort_reverse)
		swap(id_a, id_b);
	const t_map_entry& a = find_ref(m_map, id_a);
	const t_map_entry& b = find_ref(m_map, id_b);
	switch (m_sort_column)
	{
	case 0:
		return compare_string(a.name, b.name);
	case 1:
		return compare_string(a.value, b.value);
	case 2:
		return compare_string(a.extra_value, b.extra_value);
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
	}
	return 0;
}

static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return reinterpret_cast<CXSE_dlg*>(lParamSort)->compare(lParam1, lParam2);
}

void CXSE_dlg::sort_list(int i, bool reverse)
{
	m_sort_column = i;
	m_sort_reverse = reverse;
	m_list.SortItems(Compare, reinterpret_cast<DWORD_PTR>(this));
}

void CXSE_dlg::OnDropFiles(HDROP hDropInfo) 
{
	int c_files = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	char fname[MAX_PATH];
	for (int i = 0; i < c_files; i++)
	{
		DragQueryFile(hDropInfo, i, fname, MAX_PATH);
		add_file(fname);
	}
	DragFinish(hDropInfo);
}

void CXSE_dlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnPlay();
}

void CXSE_dlg::bag_file(const string& v)
{
	m_bag_fname = v;
}

void CXSE_dlg::idx_file(const string& v)
{
	m_idx_fname = v;
}
