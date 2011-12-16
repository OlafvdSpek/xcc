#include "stdafx.h"
#include "XCC Audio PlayerDlg.h"
#include "XCCAudioPlayerInfoDlg.h"

#include "ima_adpcm_wav_decode.h"
#include "riff_structures.h"

using namespace std;

CXCCAudioPlayerDlg::CXCCAudioPlayerDlg(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(CXCCAudioPlayerDlg::IDD, pParent, "AudioPlayerDlg")
{
	//{{AFX_DATA_INIT(CXCCAudioPlayerDlg)
	m_statusbar = "";
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CXCCAudioPlayerDlg::~CXCCAudioPlayerDlg()
{
}

void CXCCAudioPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCAudioPlayerDlg)
	DDX_Control(pDX, IDEXTRACT_RAW, m_extract_raw_button);
	DDX_Control(pDX, IDEXTRACT, m_extractbutton);
	DDX_Control(pDX, IDPLAY, m_playbutton);
	DDX_Control(pDX, IDSHUFFLE, m_shufflebutton);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_STATUSBAR, m_statusbar);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXCCAudioPlayerDlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(CXCCAudioPlayerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDEXTRACT, OnExtract)
	ON_BN_CLICKED(IDOPENMIX, OnOpenmix)
	ON_BN_CLICKED(IDPLAY, OnPlay)
	ON_BN_CLICKED(IDSTOP, OnStop)
	ON_BN_CLICKED(IDINFO, OnInfo)
	ON_BN_CLICKED(IDC_OpenMovies, OnOpenMovies)
	ON_BN_CLICKED(IDC_OpenSounds, OnOpenSounds)
	ON_BN_CLICKED(IDC_OpenScores, OnOpenScores)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_BN_CLICKED(IDSHUFFLE, OnShuffle)
	ON_BN_CLICKED(IDEXTRACT_RAW, OnExctractRaw)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOPENAUD, OnOpenaud)
	ON_BN_CLICKED(IDOPENVQA, OnOpenvqa)
	ON_BN_CLICKED(IDC_OpenTheme, OnOpenTheme)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnColumnclickList)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST1, OnGetdispinfoList1)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

string time2str(int v)
{
	string s;
	s = nwzl(3, v % 1000);
	v /= 1000;
	if (!v)
		return s;
	s = nwzl(2, v % 60) + "." + s;
	v /= 60;
	if (!v)
		return s;
	s = n(v) + ':' + s;
	return s;
}

BOOL CXCCAudioPlayerDlg::OnInitDialog()
{
	ETSLayoutDialog::OnInitDialog();

	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL, GREEDY)
			<< item(IDC_LIST1, GREEDY)
			<< (pane(VERTICAL, ABSOLUTE_HORZ)
				<< item(IDEXTRACT, NORESIZE)
				<< item(IDEXTRACT_RAW, NORESIZE)
				<< item(IDOPENMIX, NORESIZE)
				<< item(IDPLAY, NORESIZE)
				<< item(IDSHUFFLE, NORESIZE)
				<< item(IDSTOP, NORESIZE)
				<< item(IDC_OpenMovies, NORESIZE)
				<< item(IDC_OpenScores, NORESIZE)
				<< item(IDC_OpenSounds, NORESIZE)
				<< item(IDC_OpenTheme, NORESIZE)
				<< item(IDOPENAUD, NORESIZE)
				<< item(IDOPENVQA, NORESIZE)
				)
			)
		<< item(IDC_STATUSBAR, ABSOLUTE_VERT);
	UpdateLayout();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	if (m_listfont.CreateFont(-11, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New"))
		m_list.SetFont(&m_listfont);

	m_statusbar = "Ready";
	audio_output = video_output = true;
	if (dd.create(m_hWnd))
	{
		video_output = false;
		m_statusbar = "DirectDraw unavailable";
	}
	if (ds.create(m_hWnd))
	{
		audio_output = false;
		m_statusbar = "DirectSound unavailable";
	}
	UpdateData(false);
	m_list.InsertColumn(0, "ID", LVCFMT_LEFT);
	m_list.InsertColumn(1, "Size", LVCFMT_RIGHT);
	m_list.InsertColumn(2, "Length", LVCFMT_RIGHT);
	m_list.InsertColumn(3, "Name", LVCFMT_LEFT);
	m_list.InsertColumn(4, "Description", LVCFMT_LEFT);
	mixf.enable_mix_expansion();
	OpenMix("scores.mix");
	SetTimer(0, 5 * 1000, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CXCCAudioPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for Painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		ETSLayoutDialog::OnPaint();
	}
}

HCURSOR CXCCAudioPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXCCAudioPlayerDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
	OnPlay();
}

const char* all_filter = "All files (*.*)|*.*|";
const char* aud_filter = "AUD files (*.aud)|*.aud|";
const char* mix_filter = "MIX files (*.mix)|*.mix|";
const char* vqa_filter = "VQA files (*.vqa)|*.vqa|";
const char* wav_filter = "WAV files (*.wav)|*.wav|";

void CXCCAudioPlayerDlg::OnExtract()
{
	if (!valid_index() || m_index[current_id].type != ft_aud)
		return;
	CFileDialog dlg(false, "wav", 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, wav_filter, this);

	char s[MAX_PATH];
	strcpy(s, mix_database::get_description(game, current_id).c_str());
	dlg.m_ofn.lpstrFile = s;
	if (IDOK != dlg.DoModal())
		return;
	string fname = dlg.GetPathName();
	m_statusbar = ("Extracting to " + fname).c_str();
	UpdateData(false);

	Caud_file audf;
	audf.open(current_id, mixf);
	m_statusbar = audf.extract_as_wav(fname) ? "Extraction failed" : "Extraction succeeded";
	UpdateData(false);
}

void CXCCAudioPlayerDlg::OnExctractRaw()
{
	if (!valid_index())
		return;
	CFileDialog dlg(false, "", 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, all_filter, this);

	char s[MAX_PATH];
	strcpy(s, mix_database::get_name(game, current_id).c_str());
	dlg.m_ofn.lpstrFile = s;
	if (IDOK != dlg.DoModal())
		return;
	string fname = dlg.GetPathName();
	m_statusbar = ("Extracting to " + fname).c_str();
	UpdateData(false);

	Ccc_file f(false);
	f.open(current_id, mixf);
	m_statusbar = f.extract(fname) ? "Extraction failed" : "Extraction succeeded";
	UpdateData(false);
}

void CXCCAudioPlayerDlg::OnOpenmix()
{
	CFileDialog dlg(true, "mix", 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, mix_filter, this);
	dlg.m_ofn.lpstrInitialDir = xcc_dirs::get_dir(game_td).c_str();
	if (IDOK == dlg.DoModal())
		OpenMix(static_cast<string>(dlg.GetPathName()));
}

void CXCCAudioPlayerDlg::OnOpenaud()
{
	CFileDialog dlg(true, "aud", 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, aud_filter, this);
	if (IDOK != dlg.DoModal())
		return;
	Caud_file f;
	if (f.open(static_cast<string>(dlg.GetPathName())))
		return;
	play_aud(f);
}

void CXCCAudioPlayerDlg::OnOpenvqa()
{
	CFileDialog dlg(true, "vqa", 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, vqa_filter, this);
	dlg.m_ofn.lpstrInitialDir = xcc_dirs::get_dir(game_td).c_str();
	if (IDOK != dlg.DoModal())
		return;
	Cvqa_file f;
	if (f.open(static_cast<string>(dlg.GetPathName())))
		return;
	play_vqa(f);
}

int CXCCAudioPlayerDlg::OpenMix(const string &fname)
{
	m_shufflebutton.EnableWindow(false);
	m_c_files = 0;
	m_shuffle = false;
	mixf.close();
	m_list.SetRedraw(false);
	m_list.DeleteAllItems();
	valid_index();
	mix_database::load();
	if (mixf.open(fname))
	{
		m_statusbar = "Open failed";
		UpdateData(false);
		return 1;
	}
	m_c_files = mixf.get_c_files();
	game = mixf.get_game();
	m_index.clear();
	for (int i = 0; i < m_c_files; i++)
	{
		int id = mixf.get_id(i);
		t_file_type ft = mixf.get_type(id);
		if (ft != ft_aud && ft != ft_vqa && ft != ft_wav && ft != ft_wsa || m_index.find(id) != m_index.end())
			continue;
		t_index_entry& e = m_index[id];
		e.name = mix_database::get_name(game, id);
		e.type = ft;
		e.length = 0;
		e.size = mixf.get_size(id);
		e.description = mix_database::get_description(game, id);
		int index = m_list.InsertItem(m_list.GetItemCount(), LPSTR_TEXTCALLBACK);
		m_list.SetItemData(index, id);
		string s = ft_name[ft];
		switch (ft)
		{
		case ft_aud:
			{
				Caud_file f;
				f.open(id, mixf);
				e.length = f.get_c_samples() * 1000ll / f.get_samplerate();
				break;
			}
		case ft_vqa:
			{
				Cvqa_file f;
				f.open(id, mixf);
				e.length = f.get_c_frames() * 1000ll / 15;
				break;
			}
		case ft_wav:
			{
				Cwav_file f;
				f.open(id, mixf);
				f.process();
				const t_riff_wave_format_chunk& format_chunk = f.get_format_chunk();
				if (format_chunk.tag == 0x11 && format_chunk.cbits_sample == 4)
					e.length = f.get_fact_chunk().c_samples * 1000ll / format_chunk.samplerate;
				break;
			}
		}
	}
	m_list.auto_size();
	sort_list(4, false);
	m_list.SetRedraw(true);
	m_list.Invalidate();
	if (has_scores())
		m_shufflebutton.EnableWindow(true);
	UpdateData(false);
	return 0;
}

void CXCCAudioPlayerDlg::OnPlay()
{
	if (!valid_index())
		return;
	int id = current_id;
	switch (m_index[current_id].type)
	{
	case ft_aud:
		if (play_aud(id))
			m_statusbar = "Play AUD failed";
		else
			m_statusbar = "Ready";
		break;
	case ft_vqa:
		if (play_vqa(id))
			m_statusbar = "Play VQA failed";
		else
			m_statusbar = "Ready";
		break;
	case ft_wav:
		if (play_wav(id))
			m_statusbar = "Play wav failed";
		else
			m_statusbar = "Ready";
		break;
	}
	UpdateData(false);
}


void CXCCAudioPlayerDlg::OnShuffle()
{
	m_shuffle = true;
}

void CXCCAudioPlayerDlg::OnStop()
{
	if (!dsb.is_available())
		return;
	dsb.stop();
	m_shuffle = false;
}

void CXCCAudioPlayerDlg::OnInfo()
{
	CXCCAudioPlayerInfoDlg dlg;
	dlg.DoModal();
}

int CXCCAudioPlayerDlg::play_aud(int id)
{
	Caud_file f;
	return f.open(id, mixf) ? 1 : play_aud(f);
}

int CXCCAudioPlayerDlg::play_aud(Caud_file& audf)
{
	if (!audio_output)
		return 1;
	int cb_sample = audf.get_cb_sample();
	if (dsb.is_available())
		dsb.destroy();
	if (dsb.create(ds, cb_sample * audf.get_c_samples(), 1, audf.get_samplerate(), cb_sample << 3, DSBCAPS_GLOBALFOCUS))
		return 1;
	int cs_remaining = audf.get_c_samples();
	int writeofs = 0;
	decode.init();
	int chunk_i = 0;
	bool playing = false;
	while (cs_remaining)
	{
		m_statusbar = n(cs_remaining / audf.get_samplerate()).c_str();
		UpdateData(false);
		const t_aud_chunk_header& header = *audf.get_chunk_header(chunk_i);
		int cs_audio = header.size_out / cb_sample;
		const byte* audio_in = audf.get_chunk_data(chunk_i++);
		cs_remaining -= cs_audio;
		void* p1;
		DWORD s1;
		if (dsb.lock(writeofs, cb_sample * cs_audio, &p1, &s1, 0, 0))
			return 1;
		if (cb_sample == 2)
			decode.decode_chunk(audio_in, reinterpret_cast<short*>(p1), cs_audio);
		else if (header.size_in < header.size_out)
			aud_decode_ws_chunk(audio_in, reinterpret_cast<char*>(p1), header.size_in, header.size_out);
		else
			memcpy(p1, audio_in, cs_audio);
		writeofs += cb_sample * cs_audio;
		if (dsb.unlock(p1, s1, 0, 0))
			return 1;
		if (!playing)
		{
			if (dsb.play(0))
				return 1;
			playing = true;
		}
	}
	return 0;
}

int CXCCAudioPlayerDlg::play_vqa(int id)
{
	Cvqa_file f;
	return f.open(id, mixf) ? 1 : play_vqa(f);
}

int CXCCAudioPlayerDlg::play_vqa(Cvqa_file& f)
{
	if (!audio_output || !video_output)
		return 1;
	Cvqa_play vqa_play(dd.get_p(), ds.get_p());
	if (int result = vqa_play.create(f))
		AfxMessageBox(("Error initializing DD or DS, error code is " + n(result)).c_str(), MB_ICONEXCLAMATION);
	else
	{
		while (vqa_play.run())
		{
			MSG msg;
			while (PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE))
				AfxGetApp()->PumpMessage();

			int count = 0;
			while (AfxGetApp()->OnIdle(count++));
		}
	}
	vqa_play.destroy();
	return 0;
}

int CXCCAudioPlayerDlg::play_wav(int id)
{
	Cwav_file f;
	return f.open(id, mixf) ? 1 : play_wav(f);
}

int CXCCAudioPlayerDlg::play_wav(Cwav_file& f)
{
	int error = 0;
	if (!audio_output)
		return 1;
	if (f.process())
		return 1;
	const t_riff_wave_format_chunk& format_chunk = f.get_format_chunk();
	const t_riff_wave_fact_chunk& fact_chunk = f.get_fact_chunk();
	int c_channels = format_chunk.c_channels;
	int cb_sample = format_chunk.cbits_sample >> (format_chunk.tag == 1 ? 3 : 1);
	if (dsb.is_available())
		dsb.destroy();
	if (dsb.create(ds, c_channels * cb_sample * fact_chunk.c_samples, c_channels, format_chunk.samplerate, cb_sample << 3, DSBCAPS_GLOBALFOCUS))
		error = 1;
	else
	{
		int cb_s = f.get_data_header().size;
		byte* s = new byte[cb_s];
		const byte* r = s;
		f.seek(f.get_data_ofs());
		f.read(s, cb_s);
		int cs_remaining = fact_chunk.c_samples;
		int writeofs = 0;
		int chunk_i = 0;
		bool playing = false;
		void* p1;
		DWORD s1;
		if (dsb.lock(writeofs, cb_sample * cs_remaining * c_channels, &p1, &s1, 0, 0))
			error = 1;
		else
		{
			Cima_adpcm_wav_decode decode;
			decode.load(s, cb_s, c_channels, 512 * c_channels);
			memcpy(reinterpret_cast<short*>(p1), decode.data(), c_channels * cs_remaining << 1);
			if (dsb.unlock(p1, s1, 0, 0))
				error = 1;
			else if (dsb.play(0))
				error = 1;
		}
		delete[] s;
	}
	return error;
}

bool CXCCAudioPlayerDlg::valid_index()
{
	int index = m_list.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
	current_id = index == -1 ? -1 : m_list.GetItemData(index);
	bool can_extract = false, can_extract_raw = false, can_play = false;
	if (index != -1)
	{
		can_extract_raw = true;
		switch (m_index[current_id].type)
		{
		case ft_aud:
			can_extract = can_play = true;
			break;
		case ft_vqa:
		case ft_wav:
			can_play = true;
			break;
		}
	}
	m_extractbutton.EnableWindow(can_extract);
	m_extract_raw_button.EnableWindow(can_extract_raw);
	m_playbutton.EnableWindow(can_play);
	return index != -1;
}

void CXCCAudioPlayerDlg::OnOpenMovies()
{
	if (OpenMix("movies.mix") || OpenMix("movies01.mix"))
		OpenMix("movies02.mix");
}

void CXCCAudioPlayerDlg::OnOpenScores()
{
	OpenMix("scores.mix");
}

void CXCCAudioPlayerDlg::OnOpenSounds()
{
	OpenMix("sounds.mix");
}

void CXCCAudioPlayerDlg::OnOpenTheme()
{
	OpenMix("theme.mix");
}

void CXCCAudioPlayerDlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	valid_index();
	*pResult = 0;
}

bool CXCCAudioPlayerDlg::has_scores()
{
	BOOST_FOREACH(auto& i, m_index)
	{
		if (is_score(i.first))
			return true;
	}
	return false;
}

bool CXCCAudioPlayerDlg::is_score(int id)
{
	switch (m_index[id].type)
	{
	case ft_aud:
	case ft_wav:
		return mixf.get_size(id) > 128 << 10;
	}
	return false;
}

void CXCCAudioPlayerDlg::shuffle_aud()
{
	if (!has_scores())
		return;
	while (1)
	{
		t_index::const_iterator j = boost::next(m_index.begin(), rand() % m_index.size());
		if (!is_score(j->first))
			continue;
		int id = j->first;
		switch (m_index[id].type)
		{
		case ft_aud:
			play_aud(id);
			break;
		case ft_wav:
			play_wav(id);
			break;
		}
		break;
	}
}

void CXCCAudioPlayerDlg::OnTimer(UINT nIDEvent)
{
	if (dsb.is_available())
	{
		DWORD status;
		dsb.get_p()->GetStatus(&status);
		if (~status & DSBSTATUS_PLAYING)
			dsb.destroy();
	}
	else if (m_shuffle)
		shuffle_aud();
	ETSLayoutDialog::OnTimer(nIDEvent);
}

void CXCCAudioPlayerDlg::OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	int column = reinterpret_cast<NM_LISTVIEW*>(pNMHDR)->iSubItem;
	sort_list(column, column == m_sort_column ? !m_sort_reverse : false);
	*pResult = 0;
}

void CXCCAudioPlayerDlg::OnGetdispinfoList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	int id = pDispInfo->item.lParam;
	string& buffer = m_list.get_buffer();
	const t_index_entry&  e = m_index.find(id)->second;
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		buffer = nh(8, id);
		break;
	case 1:
		buffer = n(e.size);
		break;
	case 2:
		buffer = time2str(e.length);
		break;
	case 3:
		buffer = e.name;
		break;
	case 4:
		buffer = e.description;
		break;
	}
	pDispInfo->item.pszText = const_cast<char*>(buffer.c_str());
	*pResult = 0;
}

int compare_int(unsigned int a, unsigned int b)
{
	return a < b ? -1 : a != b;
}

int compare_string(const string& a, const string& b)
{
	return a < b ? -1 : a != b;
}

int CXCCAudioPlayerDlg::compare(int id_a, int id_b) const
{
	if (m_sort_reverse)
		swap(id_a, id_b);
	const t_index_entry& a = m_index.find(id_a)->second;
	const t_index_entry& b = m_index.find(id_b)->second;
	switch (m_sort_column)
	{
	case 0:
		return compare_int(id_a, id_b);
	case 1:
		return compare_int(a.size, b.size);
	case 2:
		return compare_int(a.length, b.length);
	case 3:
		return compare_string(a.name, b.name);
	case 4:
		return compare_string(a.description, b.description);
	}
	return 0;
}

static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return reinterpret_cast<CXCCAudioPlayerDlg*>(lParamSort)->compare(lParam1, lParam2);
}

void CXCCAudioPlayerDlg::sort_list(int i, bool reverse)
{
	m_sort_column = i;
	m_sort_reverse = reverse;
	m_list.SortItems(Compare, reinterpret_cast<DWORD>(this));
}

