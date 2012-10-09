#include "stdafx.h"
#include "edit_triggers_dlg.h"

Cedit_triggers_dlg::Cedit_triggers_dlg(Cxcc_level& level, bool selection_wanted):
	ETSLayoutDialog(Cedit_triggers_dlg::IDD, 0, "edit_triggers_dlg"),
	m_level(level),
	m_trigger_data(level.trigger_data),
	m_selection_wanted(selection_wanted)
{
	//{{AFX_DATA_INIT(Cedit_triggers_dlg)
	//}}AFX_DATA_INIT
}


void Cedit_triggers_dlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cedit_triggers_dlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_EDIT, m_edit_button);
	DDX_Control(pDX, IDC_DELETE, m_delete_button);
	DDX_Control(pDX, IDOK, m_ok_button);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cedit_triggers_dlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(Cedit_triggers_dlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL Cedit_triggers_dlg::OnInitDialog() 
{
	CreateRoot(HORIZONTAL)
		<< item(IDC_LIST, GREEDY)
		<< (pane(VERTICAL, ABSOLUTE_HORZ)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			<< item(IDC_NEW, NORESIZE)
			<< item(IDC_EDIT, NORESIZE)
			<< item(IDC_DELETE, NORESIZE)
			);
	ETSLayoutDialog::OnInitDialog();

	m_list.add_column("Name", 0);
	m_list.add_column("Cause", 1);	
	m_list.add_column("Event", 2);	
	m_list.add_column("Count", 3);	
	m_list.add_column("Side", 4);	
	m_list.add_column("Teamtype", 5);	
	m_list.add_column("Loop", 6);	

	for (auto& i : m_trigger_data)
		add_trigger(i.first);

	m_list.autosize_columns();
	
	return true;
}

const string& Cedit_triggers_dlg::get_selected_name() const
{
	return m_selected_name;
}

void Cedit_triggers_dlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->uNewState & LVIS_FOCUSED)
	{
		m_selected_name = m_list.GetItemText(pNMListView->iItem, 0);
	}
	update_controls();
	*pResult = 0;
}

void Cedit_triggers_dlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_selection_wanted)
		OnOK();
	*pResult = 0;
}

void Cedit_triggers_dlg::OnNew() 
{
	Cedit_trigger_dlg dlg(m_level);
	if (dlg.DoModal() == IDOK)
	{
		string new_name;
		dlg.save(new_name);
		add_trigger(new_name);
		m_list.autosize_columns();
	}
}

void Cedit_triggers_dlg::OnEdit() 
{
	Cedit_trigger_dlg dlg(m_level);
	dlg.load(m_selected_name);
	if (dlg.DoModal() == IDOK)
	{
		string new_name;
		dlg.save(new_name);
		if (m_selected_name != new_name)
		{
			m_trigger_data.erase(m_selected_name);
			m_list.set_item(new_name, get_index(m_selected_name), 0);
			m_selected_name = new_name;
		}
		update_trigger(m_selected_name);
		m_list.autosize_columns();
	}
}

void Cedit_triggers_dlg::OnDelete() 
{
	m_trigger_data.erase(m_selected_name);
	m_list.DeleteItem(get_index(m_selected_name));
	update_controls();
}

void Cedit_triggers_dlg::add_trigger(const string& name)
{
	m_list.add_item(name, m_list.GetItemCount());
	update_trigger(name);
}

void Cedit_triggers_dlg::update_trigger(const string& name)
{
	long i = get_index(name);
	m_list.set_item(name, i, 0);
	const t_trigger_data_entry& d = m_level.trigger_data[name];
	m_list.set_item(cause_code[d.cause], i, 1);
	m_list.set_item(event_code[d.event], i, 2);
	m_list.set_item(n(d.count), i, 3);
	m_list.set_item(d.side != -1 ? side_code[d.side] : "none", i, 4);
	m_list.set_item(d.teamtype, i, 5);
	m_list.set_item(n(d.loop), i, 6);
}

long Cedit_triggers_dlg::get_index(const string& name) const
{
	for (int i = 0; i < m_list.GetItemCount(); i++)
	{
		if (m_list.GetItemText(i, 0) == name.c_str())
			return i;
	}
	return -1;
}

void Cedit_triggers_dlg::update_controls()
{
	long selected_i = m_list.get_focused_item();
	if (m_selection_wanted)
		m_ok_button.EnableWindow(selected_i != -1);
	m_edit_button.EnableWindow(selected_i != -1);
	m_delete_button.EnableWindow(selected_i != -1);
}
