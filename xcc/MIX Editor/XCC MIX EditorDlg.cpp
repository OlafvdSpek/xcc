#include "stdafx.h"
#include "XCC MIX EditorDlg.h"

#include "blowfish.h"
#include "cc_file.h"
#include "file32.h"
#include "fname.h"
#include "id_log.h"
#include "mix_decode.h"
#include "MIXOptions.h"
#include "string_conversion.h"
#include "xcc_dirs.h"
#include "xcc_lmd_file_write.h"

CXCCMIXEditorDlg::CXCCMIXEditorDlg(CWnd* pParent /*=NULL*/):
	ETSLayoutDialog(CXCCMIXEditorDlg::IDD, pParent, "XCCMIXEditorDlg")
{
	//{{AFX_DATA_INIT(CXCCMIXEditorDlg)
	m_edit_status = _T("Author: Olaf van der Spek <OlafvdSpek@GMail.Com>");
	//}}AFX_DATA_INIT
	m_current_id = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_open = false;
	m_key_loaded = false;
}

void CXCCMIXEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCMIXEditorDlg)
	DDX_Control(pDX, IDC_BUTTON_INSERT, m_button_insert);
	DDX_Control(pDX, IDC_BUTTON_OPTIONS, m_button_options);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_button_delete);
	DDX_Control(pDX, IDC_BUTTON_LOAD_KEY, m_button_load_key);
	DDX_Control(pDX, IDC_BUTTON_COMPACT, m_button_compact);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_button_save);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_button_close);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_button_open);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_button_new);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_edit_status);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXCCMIXEditorDlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(CXCCMIXEditorDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_COMPACT, OnButtonCompact)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_KEY, OnButtonLoadKey)
	ON_BN_CLICKED(IDC_BUTTON_XCC_HOME_PAGE, OnButtonXccHomePage)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_OPTIONS, OnButtonOptions)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST, OnDeleteitemList)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST, OnColumnclickList)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int c_colums = 7;
char* column_label[] = {"Name", "Type", "Description", "ID", "Offset", "Size", ""};
int column_alignment[] = {LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_LEFT};

BOOL CXCCMIXEditorDlg::OnInitDialog()
{
	ETSLayoutDialog::OnInitDialog();
	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL, GREEDY)
			<< item(IDC_LIST, GREEDY)
			<< (pane(VERTICAL, ABSOLUTE_HORZ)
				<< item(IDC_BUTTON_NEW, NORESIZE)
				<< item(IDC_BUTTON_OPEN, NORESIZE)
				<< item(IDC_BUTTON_SAVE, NORESIZE)
				<< item(IDC_BUTTON_COMPACT, NORESIZE)
				<< item(IDC_BUTTON_CLOSE, NORESIZE)
				<< item(IDC_BUTTON_LOAD_KEY, NORESIZE)
				<< item(IDC_BUTTON_INSERT, NORESIZE)
				<< item(IDC_BUTTON_DELETE, NORESIZE)
				<< item(IDC_BUTTON_OPTIONS, NORESIZE)
				<< item(IDC_BUTTON_XCC_HOME_PAGE, NORESIZE)
				)
			)
		<< item(IDC_EDIT_STATUS, ABSOLUTE_VERT);
	UpdateLayout();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	for (int i = 0; i < c_colums; i++)
		m_list.InsertColumn(i, column_label[i], column_alignment[i]);
	if (read_key(xcc_dirs::get_main_mix(game_ts)))
		read_key(xcc_dirs::get_main_mix(game_ra2));
	m_list.auto_size();
	update_buttons();
	return true;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXCCMIXEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

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

HCURSOR CXCCMIXEditorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

const char* mix_filter = "MIX files (*.mix)|*.mix|";

void CXCCMIXEditorDlg::OnButtonNew()
{
	CFileDialog dlg(false, "mix", 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, mix_filter, this);
	if (IDOK == dlg.DoModal())
	{
		m_game = game_ts;
		m_encrypted = false;
		m_checksum = false;
		m_fname = dlg.GetPathName();
		m_open = true;
		set_changed(false);
	}
}

void CXCCMIXEditorDlg::OnButtonOpen()
{
	CFileDialog dlg(true, "mix", 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, mix_filter, this);
	if (IDOK == dlg.DoModal())
		set_status("open mix", read_mix(static_cast<string>(dlg.GetPathName())));
}

void CXCCMIXEditorDlg::OnButtonSave()
{
	set_status("save mix", save_mix());
}

void CXCCMIXEditorDlg::OnButtonCompact()
{
	set_status("compact mix", compact_mix());
}

void CXCCMIXEditorDlg::OnButtonClose()
{
	m_open = false;
	m_list.DeleteAllItems();
	m_index.clear();
	update_buttons();
}

void CXCCMIXEditorDlg::OnButtonLoadKey()
{
	CFileDialog dlg(true, "mix", 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, mix_filter, this);
	if (IDOK == dlg.DoModal())
		set_status("read key", read_key(static_cast<string>(dlg.GetPathName())));
}

void CXCCMIXEditorDlg::OnButtonDelete()
{
	int index = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	while (index != -1)
	{
		int id = m_list.GetItemData(index);
		m_list.DeleteItem(index);
		m_index.erase(id);
		index = m_list.GetNextItem(index - 1, LVNI_ALL | LVNI_SELECTED);
	}
	set_changed(true);
}

void CXCCMIXEditorDlg::OnButtonOptions()
{
	CMIXOptions dlg;
	dlg.set(m_game, m_encrypted, m_checksum);
	if (dlg.DoModal() == IDOK)
	{
		dlg.get(m_game, m_encrypted, m_checksum);
		set_changed(true);
	}
}

void CXCCMIXEditorDlg::OnButtonXccHomePage()
{
	ShellExecute(m_hWnd, "open", "http://xccu.sourceforge.net/", NULL, NULL, SW_SHOW);
}

void CXCCMIXEditorDlg::update_buttons()
{
	m_button_new.EnableWindow(m_key_loaded && !m_open);
	m_button_open.EnableWindow(!m_open);
	m_button_save.EnableWindow(m_open && m_changed);
	m_button_compact.EnableWindow(m_open);
	m_button_close.EnableWindow(m_open);
	m_button_insert.EnableWindow(m_open);
	m_button_delete.EnableWindow(false);
	m_button_options.EnableWindow(m_open);
}

int CXCCMIXEditorDlg::read_key(const string& name)
{
	int error = 0;
	Cmix_file f;
	if (f.open(name))
		error = 1;
	else
	{
		if (f.is_encrypted())
		{
			f.seek(4);
			f.read(m_key, cb_mix_key_source);
			m_key_loaded = true;
			update_buttons();
		}
		else
			error = 1;
		f.close();

	}
	return error;
}

void CXCCMIXEditorDlg::add_file(const string& name)
{
	if (!m_open)
		return;
	const string fname = static_cast<Cfname>(name).get_fname();
	int id = Cmix_file::get_id(m_game, fname);
	if (m_index.find(id) != m_index.end())
		m_index.erase(id);
	t_index_entry e;
	Ccc_file f(false);
	if (f.open(name))
		return;
	e.ft = f.get_file_type();
	f.close();
	e.fname = name;
	e.offset = 0;
	e.size = f.get_size();
	m_index[id] = e;
	set_changed(true);
	add_entry(id);
}

void CXCCMIXEditorDlg::add_entry(int id)
{
	auto& i = find_ref(m_index, id);
	int j = m_list.GetItemCount();
	m_list.InsertItem(j, static_cast<Cfname>(i.fname).get_fname().c_str());
	m_list.SetItemData(j, id);
	m_list.SetItemText(j, 1, ft_name[i.ft]);
	m_list.SetItemText(j, 2, mix_database::get_description(m_game, id).c_str());
	m_list.SetItemText(j, 3, nh(8, id).c_str());
	m_list.SetItemText(j, 4, n(i.offset).c_str());
	m_list.SetItemText(j, 5, n(i.size).c_str());
}

int CXCCMIXEditorDlg::read_mix(const string& name)
{
	int error = 0;
	Cmix_file f;
	m_fname = name;
	if (f.open(name))
		error = 1;
	else
	{
		if (f.is_encrypted())
		{
			f.seek(4);
			f.read(m_key, cb_mix_key_source);
			m_key_loaded = true;
		}
		m_encrypted = f.is_encrypted();
		m_game = f.get_game();
		m_checksum = f.has_checksum();
		for (int i = 0; i < f.get_c_files(); i++)
		{
			int id = f.get_id(i);
			t_index_entry e;
			e.ft = f.get_type(id);
			e.fname = mix_database::get_name(m_game, id);
			e.offset = f.get_offset(id);
			e.size = f.get_size(id);
			m_index[id] = e;
		}
		f.close();
		m_open = true;
		set_changed(false);
		update_list();
	}
	return error;
}

static int copy_block(Cfile32& s, int s_p, Cfile32& d, int d_p, int size)
{
	int error = 0;
	int buffer_size = 4 << 20;
	byte* buffer = new byte[buffer_size];
	while (!error && size)
	{
		int cb_buffer = min(buffer_size, size);
		s.seek(s_p);
		if (s.read(buffer, cb_buffer))
			error = 1;
		else
		{
			d.seek(d_p);
			if (d.write(buffer, cb_buffer))
				error = 1;
			else
			{
				s_p += cb_buffer;
				d_p += cb_buffer;
				size -= cb_buffer;
			}
		}
	}
	delete[] buffer;
	return error;
}

static int get_header_size(t_game game, int c_files, bool checksum, bool encrypted)
{
	const int cb_checksum = checksum ? cb_mix_checksum : 0;
	const int cb_index = c_files * sizeof(t_mix_index_entry);
	if (game == game_td)
		return sizeof(t_mix_header) + cb_index;
	else if (encrypted)
		return 4 + cb_mix_key_source + (sizeof(t_mix_header) + cb_index + 7 & ~7) + cb_checksum;
	else
		return 4 + sizeof(t_mix_header) + cb_index + cb_checksum;
}

int CXCCMIXEditorDlg::get_header_size() const
{
	return ::get_header_size(m_game, m_index.size(), m_checksum, m_encrypted);
}

int CXCCMIXEditorDlg::get_max_offset() const
{
	int r = get_header_size();
	for (auto& i : m_index)
		r = max(r, i.second.offset + i.second.size);
	return r;
}

int CXCCMIXEditorDlg::save_mix()
{
	int error = 0;
	Cfile32 f;
	if (f.open(xcc_dirs::find_file(m_fname), GENERIC_READ | GENERIC_WRITE, OPEN_ALWAYS, 0))
		error = 1;
	else
	{
		m_checksum = false;
		if (m_game == game_td)
			m_encrypted = false;
		Cxcc_lmd_file_write g;
		for (auto& i : m_index)
		{
			if (!i.second.fname.empty())
				g.add_fname(static_cast<Cfname>(i.second.fname).get_fname());
		}
		Cvirtual_binary lmd_data = g.write(m_game);
		const int lmd_id = Cmix_file::get_id(m_game, "local mix database.dat");
		t_index_entry e;
		e.fname = "local mix database.dat";
		e.ft = ft_xcc_lmd;
		e.offset = 0;
		e.size = lmd_data.size();
		m_index[lmd_id] = e;
		const int body_start = get_header_size();
		int max_offset = body_start;
		while (!error)
		{
			int id;
			int min_offset = INT_MAX;
			for (auto& i : m_index)
			{
				if (!i.second.offset)
					continue;
				if (i.second.offset < min_offset)
				{
					id = i.first;
					min_offset = i.second.offset;
				}
				if (i.second.offset + i.second.size > max_offset)
					max_offset = i.second.offset + i.second.size;
			}
			if (body_start > min_offset)
			{
				auto& j = find_ref(m_index, id);
				error = copy_block(f, min_offset, f, max_offset, j.size);
				if (!error)
					j.offset = max_offset;
			}
			else
				break;
		}
		if (!error)
		{
			for (auto& i : m_index)
			{
				if (i.second.offset)
					continue;
				if (i.first == lmd_id)
				{
					max_offset = (max_offset - body_start + 0xf & ~0xf) + body_start;
					f.seek(max_offset);
					f.write(lmd_data.data(), lmd_data.size());
					i.second.offset = max_offset;
					max_offset += lmd_data.size();
				}
				else
				{
					Cfile32 g;
					if (g.open(i.second.fname, GENERIC_READ))
					{
						error = 1;
						break;
					}
					error = copy_block(g, 0, f, max_offset, g.size());
					if (!error)
					{
						i.second.offset = max_offset;
						max_offset += g.size();
					}
					g.close();
				}
			}
			if (!error)
			{
				f.seek(max_offset);
				if (f.set_eof())
					error = 1;
			}
		}
		byte* data = new byte[body_start];
		t_mix_header* header;
		if (m_game == game_td)
			header = reinterpret_cast<t_mix_header*>(data);
		else
		{
			*reinterpret_cast<int*>(data) = (m_checksum ? mix_checksum : 0) | (m_encrypted ? mix_encrypted : 0);
			if (m_encrypted)
			{
				memcpy(data + 4, m_key, cb_mix_key_source);
				header = reinterpret_cast<t_mix_header*>(data + 4 + cb_mix_key_source);
			}
			else
				header = reinterpret_cast<t_mix_header*>(data + 4);
		}
		header->c_files = m_index.size();
		header->size = max_offset - body_start;
		t_mix_index_entry* index = reinterpret_cast<t_mix_index_entry*>(reinterpret_cast<byte*>(header) + sizeof(t_mix_header));
		for (auto& i : m_index)
		{
			index->id = i.first;
			index->offset = i.second.offset - body_start;
			index->size = i.second.size;
			index++;
		}
		if (m_encrypted)
		{
			Cblowfish bf;
			std::array<byte, cb_mix_key> key;
			get_blowfish_key(m_key, key);
			bf.set_key(key);
			bf.encipher(header, header, body_start - (4 + cb_mix_key_source));
		}
		f.seek(0);
		if (f.write(data, body_start) && !error)
			error = 1;
		delete[] data;
		f.close();
	}
	set_changed(false);
	update_list();
	return error;
}

int CXCCMIXEditorDlg::compact_mix()
{
	int error = 0;
	error = save_mix();
	if (!error)
	{
		Cfile32 f;
		if (f.open(xcc_dirs::find_file(m_fname), GENERIC_READ | GENERIC_WRITE, OPEN_ALWAYS, 0))
			error = 1;
		else
		{
			bool changed;
			do
			{
				changed = false;
				const int max_offset = get_max_offset();
				map<int, int> ofs_list;
				for (auto& j : m_index)
					ofs_list[j.second.offset] = j.first;
				const int body_start = get_header_size();
				int min_offset = body_start;
				for (auto& i : ofs_list)
				{
					auto& j = find_ref(m_index, i.second);
					if (m_game == game_ts)
						min_offset = (min_offset - body_start + 0xf & ~0xf) + body_start;
					if (j.offset > min_offset)
					{
						error = copy_block(f, j.offset, f, min_offset, j.size);
						if (error)
							break;
						j.offset = min_offset;
						changed = true;
					}
					else if (j.offset < min_offset)
					{
						error = copy_block(f, j.offset, f, max_offset, j.size);
						if (error)
							break;
						j.offset = max_offset;
						changed = true;
						continue;
					}
					min_offset += j.size;
				}
			}
			while (changed && !error);
			f.close();
			if (!error)
				error = save_mix();
		}
	}
	return error;
}

void CXCCMIXEditorDlg::set_changed(bool changed)
{
	m_changed = changed;
	update_buttons();
}

void CXCCMIXEditorDlg::update_list()
{
	m_list.SetRedraw(false);
	m_list.DeleteAllItems();
	for (auto& i : m_index)
		add_entry(i.first);
	m_list.auto_size();
	sort_list(0, false);
	m_list.SetRedraw(true);
}

void CXCCMIXEditorDlg::set_status(const string& msg, bool error)
{
	m_edit_status = (msg + (error ? ": failed" : ": done")).c_str();
	UpdateData(false);
}

void CXCCMIXEditorDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_current_id = pNMListView->uNewState & LVIS_FOCUSED ? m_list.GetItemData(pNMListView->iItem) : 0;
	m_button_delete.EnableWindow(m_current_id);
	*pResult = 0;
}

void CXCCMIXEditorDlg::OnDeleteitemList(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_current_id = pNMListView->uNewState & LVIS_FOCUSED ? m_list.GetItemData(pNMListView->iItem) : 0;
	m_button_delete.EnableWindow(m_current_id);
	*pResult = 0;
}

void CXCCMIXEditorDlg::OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	int column = reinterpret_cast<NM_LISTVIEW*>(pNMHDR)->iSubItem;
	sort_list(column, column == m_sort_column ? !m_sort_reverse : false);
	*pResult = 0;
}

int compare_int(unsigned int a, unsigned int b)
{
	return a < b ? -1 : a != b;
}

int compare_string(string a, string b)
{
	return a < b ? -1 : a != b;
}

int CXCCMIXEditorDlg::compare(int id_a, int id_b) const
{
	if (m_sort_reverse)
		swap(id_a, id_b);
	const t_index_entry& a = find_ref(m_index, id_a);
	const t_index_entry& b = find_ref(m_index, id_b);
	switch (m_sort_column)
	{
	case 0:
		return compare_string(a.fname, b.fname);
	case 1:
		return compare_int(a.ft, b.ft);
	case 3:
		return compare_int(id_a, id_b);
	case 4:
		return compare_int(a.offset, b.offset);
	case 5:
		return compare_int(a.size, b.size);
	}
	return 0;
}

static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return reinterpret_cast<CXCCMIXEditorDlg*>(lParamSort)->compare(lParam1, lParam2);
}

void CXCCMIXEditorDlg::sort_list(int i, bool reverse)
{
	m_sort_column = i;
	m_sort_reverse = reverse;
	m_list.SortItems(Compare, reinterpret_cast<dword>(this));
}

const char* all_filter = "All files (*.*)|*.*|";

void CXCCMIXEditorDlg::OnButtonInsert()
{
	CFileDialog dlg(true, NULL, 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, all_filter, this);
	dlg.m_ofn.lpstrInitialDir = xcc_dirs::get_dir(game_td).c_str();
	if (IDOK == dlg.DoModal())
		add_file(static_cast<string>(dlg.GetPathName()));
}

void CXCCMIXEditorDlg::OnDropFiles(HDROP hDropInfo)
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
