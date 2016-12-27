#include "stdafx.h"
#include "open_from_mix_dlg.h"

#include "xcc_log.h"

Copen_from_mix_dlg::Copen_from_mix_dlg(CWnd* pParent /*=NULL*/):
	ETSLayoutDialog(Copen_from_mix_dlg::IDD, pParent, "open_from_mix_dlg"),
	mix(Cxcc_mixs::general())
{
	//{{AFX_DATA_INIT(Copen_from_mix_dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void Copen_from_mix_dlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Copen_from_mix_dlg)
	DDX_Control(pDX, IDOK, m_ok_button);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Copen_from_mix_dlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(Copen_from_mix_dlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL Copen_from_mix_dlg::OnInitDialog() 
{
	CreateRoot(HORIZONTAL)
		<< item(IDC_LIST1, GREEDY)
		<< (pane(VERTICAL, ABSOLUTE_HORZ)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			);
	ETSLayoutDialog::OnInitDialog();
	m_list.SetRedraw(false);
	m_list.set_fixed_width_font();

	m_list.add_column("ID", 0, 80);
	m_list.add_column("Name", 1, 100);
	m_list.add_column("Description", 2, 240);
	m_list.add_column("Theater", 3, 240);

	mix_database::load();
	CWaitCursor wait;
	for (int i = 0; i < mix.get_c_files(); i++)
	{
		int id = mix.get_id(i);
		if (mix.get_size(id) != 8192)
			continue;
		Cfname name = mix_database::get_name(game_td, id);
		if (name.get_fname().length() != 11 || name.get_ftitle().substr(0, 2) != "sc" || name.get_fext() != ".bin")
			continue;
		Ccc_file bin_f(false), ini_f(true);
		if (bin_f.open(name, mix))
			continue;
		name.set_ext(".ini");
		if (ini_f.open(name, mix))
			continue;
		xcc_log::write_line("loading " + name.get_ftitle());
		Cxcc_level level;
		if (level.load(Cvirtual_binary(), ini_f.vdata()))
			continue;
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
	{
		int list_i = 0;
		for (auto& i : index)
		{
			const string& name = i.first;
			m_list.add_item(nh(8, Cmix_file::get_id(game_td, name)), list_i);
			m_list.set_item(name, list_i, 1);
			m_list.set_item(i.second.description, list_i, 2);
			m_list.set_item(theater_code[i.second.theater], list_i, 3);
			list_i++;
		}
	}
	m_list.autosize_columns();
	m_list.SetRedraw(true);
	m_list.Invalidate();
	return TRUE;  // return TRUE unless you set the focus to a control
}

void Copen_from_mix_dlg::get_selected_f(Cvirtual_binary& bin_d, Cvirtual_binary& ini_d, string& name)
{
	bin_d = mix.get_vdata(selected_fname + ".bin");
	ini_d = mix.get_vdata(selected_fname + ".ini");
	name = selected_fname;
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
	selected_fname = m_list.GetItemText(m_list.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED), 1);
	ETSLayoutDialog::OnOK();
}
