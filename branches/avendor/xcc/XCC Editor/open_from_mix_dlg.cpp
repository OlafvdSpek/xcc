// open_from_mix_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "xcc editor.h"
#include "open_from_mix_dlg.h"

#include "xcc_log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Copen_from_mix_dlg dialog


Copen_from_mix_dlg::Copen_from_mix_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Copen_from_mix_dlg::IDD, pParent),
	mix(Cxcc_mixs::get_general_mix())
{
	//{{AFX_DATA_INIT(Copen_from_mix_dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

Copen_from_mix_dlg::~Copen_from_mix_dlg()
{
}


void Copen_from_mix_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Copen_from_mix_dlg)
	DDX_Control(pDX, IDOK, m_ok_button);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Copen_from_mix_dlg, CDialog)
	//{{AFX_MSG_MAP(Copen_from_mix_dlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Copen_from_mix_dlg message handlers

BOOL Copen_from_mix_dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_list.SetRedraw(false);
	if (m_listfont.CreateFont(-11, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New"))
	m_list.SetFont(&m_listfont);
	ListView_SetExtendedListViewStyle(m_list.m_hWnd, ListView_GetExtendedListViewStyle(m_list.m_hWnd) | LVS_EX_FULLROWSELECT);	

	add_column("ID", 0, 80);
	add_column("Name", 1, 100);
	add_column("Description", 2, 240);
	add_column("Theater", 3, 240);

	c_files = mix.get_c_files();
	mix_database::load();
	{
		CWaitCursor wait;
		Ccc_file bin_f(false), ini_f(false);
		Cxcc_level level;
		for (long i = 0; i < c_files; i++)
		{
			dword id = mix.get_id(i);
			if (mix.get_size(id) != 8192)
				continue;
			Cfname name = mix_database::get_name(game_td, id);
			if (name.get_fname().length() != 11 || name.get_ftitle().substr(0, 2) != "sc" || name.get_fext() != ".bin")
				continue;
			bin_f.open(name, mix);
			name.set_ext(".ini");
			ini_f.open(name, mix);
			if (bin_f.is_open() && ini_f.is_open())
			{
				const long cb_ini = ini_f.get_size();
				byte* ini_d = new byte[cb_ini];
				ini_f.read(ini_d, cb_ini);
				xcc_log::write_line("loading " + name.get_ftitle());
				if (!level.load(0, ini_d, cb_ini))
				{
					name.set_ext("");
					t_index_info info;
					info.description = level.basic_data.name;
					if (info.description.empty())
						info.description = mix_database::get_description(game_td, id);
					if (info.description.empty())
						info.description = level.basic_data.brief;
					info.theater = level.map_data.theater;
					index[name] = info;
				}
				delete[] ini_d;
			}
			if (ini_f.is_open())
				ini_f.close();
			if (bin_f.is_open())
				bin_f.close();
		}
	}
	{
		long list_i = 0;
		for (t_index::const_iterator i = index.begin(); i != index.end(); i++)
		{
			const string& name = i->first;
			add_item(nh(8, Cmix_file::get_id(game_td, name)), list_i, 0);		
			add_item(name, list_i, 1);
			add_item(i->second.description, list_i, 2);
			add_item(theater_code[i->second.theater], list_i, 3);
			list_i++;
		}
	}
	{
		for (long i = 0; i < 10; i++)
			m_list.SetColumnWidth(i, LVSCW_AUTOSIZE);
	}
	m_list.SetRedraw(true);
	m_list.Invalidate();
	return TRUE;  // return TRUE unless you set the focus to a control
}

void Copen_from_mix_dlg::add_column(const string& text, dword index, dword size, dword format)
{
	LV_COLUMN column_data;
	column_data.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	column_data.fmt = format;
	column_data.cx = size;
	char s[256];
	strcpy(s, text.c_str()); 
	column_data.pszText = s;
	column_data.iSubItem = index;
	m_list.InsertColumn(index, &column_data);
}

void Copen_from_mix_dlg::add_item(const string& text, dword index, dword subindex)
{
	LV_ITEM item_data;
	item_data.mask = LVIF_TEXT | (subindex ? 0 : LVIF_PARAM);
	item_data.iItem = index;
	item_data.iSubItem = subindex;
	char s[256];
	strcpy(s, text.c_str()); 
	item_data.pszText = s;
	item_data.lParam = index;
	if (!subindex)
		m_list.InsertItem(&item_data);
	else
		m_list.SetItem(&item_data);
}

void Copen_from_mix_dlg::get_selected_f(word*& bin_d, byte*& ini_d, dword& cb_ini)
{
	Ccc_file bin_f(false), ini_f(false);
	ini_f.open(selected_fname + ".ini", mix);
	bin_f.open(selected_fname + ".bin", mix);
	cb_ini = ini_f.get_size();
	ini_d = new byte[cb_ini];
	bin_d = new word[4096];
	ini_f.read(ini_d, cb_ini);
	bin_f.read(bin_d, 8192);
	bin_f.close();
	ini_f.close();
}

void Copen_from_mix_dlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_ok_button.EnableWindow(m_list.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED) != -1);	
	*pResult = 0;
}

void Copen_from_mix_dlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnOK();
	*pResult = 0;
}

void Copen_from_mix_dlg::OnOK() 
{
	LV_ITEM item_data;
	item_data.mask = LVIF_TEXT;
	item_data.iItem = m_list.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
	item_data.iSubItem = 1;
	char s[256];
	item_data.pszText = s;
	m_list.GetItem(&item_data);
	selected_fname = s;
	CDialog::OnOK();
}
